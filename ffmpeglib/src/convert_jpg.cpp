
extern "C" {

#include "config.h"
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

#if HAVE_ISATTY
#if HAVE_IO_H
#include <io.h>
#endif
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#endif

#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libswresample/swresample.h"
#include "libavutil/opt.h"
#include "libavutil/channel_layout.h"
#include "libavutil/parseutils.h"
#include "libavutil/samplefmt.h"
#include "libavutil/fifo.h"
#include "libavutil/intreadwrite.h"
#include "libavutil/dict.h"
#include "libavutil/mathematics.h"
#include "libavutil/pixdesc.h"
#include "libavutil/avstring.h"
#include "libavutil/libm.h"
#include "libavutil/imgutils.h"
#include "libavutil/timestamp.h"
#include "libavutil/bprint.h"
#include "libavutil/time.h"
#include "libavutil/threadmessage.h"
#include "libavformat/os_support.h"
#include "libavcodec/avcodec.h"

#include "libavformat/ffm.h" // not public API

# include "libavfilter/avcodec.h"
# include "libavfilter/avfilter.h"
# include "libavfilter/buffersrc.h"
# include "libavfilter/buffersink.h"

#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>

#include <sys/select.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <termios.h>

#include <time.h>

//#include "ffmpeglib.h"
#include <cmdutils-cpp.h>

#include "libavutil/avassert.h"

} //extern "C"
#include <iostream>
#include <vector>
#include <exception>
#include <sstream>
#include <string>

using namespace std;

static int MyWriteJPEG(AVFrame* pFrame, int width, int height, int iIndex, const char *path, const char *name, long long time, int (*callback)(void *))
{
    // 输出文件路径
    char out_file[1024] = {0};
    bool succ = false;
    strcpy(out_file, path);
    sprintf(out_file+strlen(path), "%s-%d-%lld.jpg", name, iIndex, time);

    // 分配AVFormatContext对象
    AVFormatContext* pFormatCtx = NULL;

    try {
		pFormatCtx  = avformat_alloc_context();

		// 设置输出文件格式
		pFormatCtx->oformat = av_guess_format("mjpeg", NULL, NULL);
		// 创建并初始化一个和该url相关的AVIOContext
		if( avio_open(&pFormatCtx->pb, out_file, AVIO_FLAG_READ_WRITE) < 0) {
			printf("Couldn't open output file.");
			throw exception();
		}

		// 构建一个新stream
		AVStream* pAVStream = avformat_new_stream(pFormatCtx, 0);
		if( pAVStream == NULL ) {
			throw exception();
		}

		// 设置该stream的信息
		AVCodecContext* pCodecCtx = pAVStream->codec;

		pCodecCtx->codec_id = pFormatCtx->oformat->video_codec;
		pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
		pCodecCtx->pix_fmt = PIX_FMT_YUVJ420P;
		pCodecCtx->width = width;
		pCodecCtx->height = height;
		pCodecCtx->time_base.num = 1;
		pCodecCtx->time_base.den = 25;
		pCodecCtx->flags |= CODEC_FLAG_QSCALE;
        pCodecCtx->global_quality = FF_QP2LAMBDA * 1;

		// Begin Output some information
		av_dump_format(pFormatCtx, 0, out_file, 1);
		// End Output some information

		// 查找解码器
		AVCodec* pCodec = avcodec_find_encoder(pCodecCtx->codec_id);
		if( !pCodec ) {
			printf("Codec not found.");
			throw exception();
		}
		// 设置pCodecCtx的解码器为pCodec
		if( avcodec_open2(pCodecCtx, pCodec, NULL) < 0 ) {
			printf("Could not open codec.");
			throw exception();
		}

		//Write Header
		avformat_write_header(pFormatCtx, NULL);

		int y_size = pCodecCtx->width * pCodecCtx->height;

		//Encode
		// 给AVPacket分配足够大的空间
		AVPacket pkt;
		av_new_packet(&pkt, y_size * 3);

		//
		int got_picture = 0;
		int ret = avcodec_encode_video2(pCodecCtx, &pkt, pFrame, &got_picture);
		if( ret < 0 ) {
			printf("Encode Error.\n");
			throw exception();
		}
		if( got_picture == 1 ) {
			//pkt.stream_index = pAVStream->index;
			ret = av_write_frame(pFormatCtx, &pkt);
		}

		av_free_packet(&pkt);

		//Write Trailer
		av_write_trailer(pFormatCtx);

		//printf("Encode Successful.\n");

		if( pAVStream ) {
			avcodec_close(pAVStream->codec);
		}
		succ = true;
    }
    catch(...) {

    }
    if(succ && callback) {
    	callback(out_file);
    }
    if(pFormatCtx) {
		if(pFormatCtx->pb)
			avio_close(pFormatCtx->pb);
		avformat_free_context(pFormatCtx);
    }

    return 0;
}
extern "C" int ffmpeg_convert_jpg(const char *filename, const char *out_path, const char *outfilename, int64_t intral, int scal, int (*callback)(void *))
{
    int videoStream = -1;
    AVCodecContext *pCodecCtx = NULL;
    AVFormatContext *pFormatCtx = NULL;
    AVCodec *pCodec = NULL;
    AVFrame *pFrame = NULL;
    struct SwsContext *pSwsCtx = NULL;
    AVFrame *nDst_picture ;
    bool alloc_pic = false;
    AVPacket packet;
    int frameFinished;
    int PictureSize;

    try {
		//注册编解码器
		av_register_all();
		// 初始化网络模块
		avformat_network_init();
		av_log_set_level(AV_LOG_PANIC);
		// 分配AVFormatContext
		pFormatCtx = avformat_alloc_context();

		//打开视频文件
		if( avformat_open_input(&pFormatCtx, filename, NULL, NULL) != 0 ) {
			printf ("av open input file failed!\n");
			throw exception();
		}

		//获取流信息
		if( avformat_find_stream_info(pFormatCtx, NULL) < 0 ) {
			printf ("av find stream info failed!\n");
			throw std::exception();
		}
		//获取视频流
		for( int i = 0; i < pFormatCtx->nb_streams; i++ ) {
			if ( pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO ) {
				videoStream = i;
				break;
			}
		}
		if( videoStream == -1 ) {
			printf ("find video stream failed!\n");
			throw std::exception();
		}

		// 寻找解码器
		pCodecCtx = pFormatCtx->streams[videoStream]->codec;
		pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
		if( pCodec == NULL ) {
			printf ("avcode find decoder failed!\n");
			throw std::exception();
		}

		//打开解码器
		if( avcodec_open2(pCodecCtx, pCodec, NULL) < 0 ) {
			printf ("avcode open failed!\n");
			throw std::exception();
		}

		//为每帧图像分配内存
		pFrame = avcodec_alloc_frame();

		// 确定图片尺寸
		PictureSize = avpicture_get_size(PIX_FMT_YUVJ420P, pCodecCtx->width, pCodecCtx->height);

	    nDst_picture = avcodec_alloc_frame();
	    if (!nDst_picture){
	        printf("nDst_picture avcodec_alloc_frame failed\n");
	        throw std::exception();
	    }
	    if(avpicture_alloc((AVPicture *)nDst_picture, PIX_FMT_YUVJ420P, pCodecCtx->width*scal/100, pCodecCtx->height*scal/100)<0){
	        printf("dst_picture avpicture_alloc failed\n");
	        throw std::exception();
	    }
	    alloc_pic = true;
		//设置图像转换上下文
		pSwsCtx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
			pCodecCtx->width*scal/100, pCodecCtx->height*scal/100, PIX_FMT_YUVJ420P,
			SWS_BICUBIC, NULL, NULL, NULL);

		int i = 0;
		int64_t oldpts = -(intral*1000);
		int64_t nextdecodepts = oldpts + intral*1000;
		int64_t oldkeypts = 0;
		int64_t goptime = 0; // key frame interval
		bool decodekey = false;
		while( av_read_frame(pFormatCtx, &packet) >= 0 ) {
			if( packet.stream_index == videoStream ) {
				bool decodePic = false;
				frameFinished = 0;
				int gop = pCodecCtx->gop_size;
				int64_t pts = av_rescale_q(packet.pts, pFormatCtx->streams[videoStream]->time_base, AV_TIME_BASE_Q);
				if(packet.flags & AV_PKT_FLAG_KEY) {
					// reset the goptime
					if(pts - oldkeypts >= goptime)
						goptime = pts - oldkeypts;

					int64_t nextkeydecodepts = nextdecodepts - goptime;
					avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
					if(pts > nextdecodepts) {
//						avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
						decodekey = true;
						decodePic = true;
						printf("decode ----key frame timestamp %d,    %d                   %d\n", (int)pts, (int)frameFinished, (int)nextdecodepts);
					}
					else {
						decodekey = false;
//						printf("discard unused key frame\n");
					}
					oldkeypts = pts;
				}
				else //if(decodekey)
				{
					avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
					printf("decode ----non key frame %d \n", frameFinished);
				}

				if( frameFinished && decodePic ) {
					if(pts - oldpts >= intral*1000) {
						int ret = 0;
						ret = sws_scale(pSwsCtx, pFrame->data, pFrame->linesize, 0, pCodecCtx->height, nDst_picture->data, nDst_picture->linesize);
						if(ret > 0) {
							MyWriteJPEG(nDst_picture, pCodecCtx->width*scal/100, pCodecCtx->height*scal/100, i ++, out_path, outfilename, pts/1000, callback);
//							MyWriteJPEG(pFrame, pCodecCtx->width, pCodecCtx->height, i ++, out_path, outfilename);
						}
						else
							MyWriteJPEG(pFrame, pCodecCtx->width, pCodecCtx->height, i ++, out_path, outfilename, pts/1000, callback);
						oldpts = pts;
						nextdecodepts = oldpts + intral*1000;
						decodekey = false;
					}
				}
			}
			av_free_packet(&packet);
		}
    }
    catch(...) {

    }

    if(pSwsCtx) sws_freeContext(pSwsCtx);

    if(pFrame) av_free(pFrame);
    if(alloc_pic) {
    	avpicture_free((AVPicture *)(nDst_picture));
    }
    if(nDst_picture) avcodec_free_frame(&nDst_picture);
    if(pCodecCtx) avcodec_close(pCodecCtx);
    if(pFormatCtx) avformat_close_input(&pFormatCtx);

    return 0;
}
