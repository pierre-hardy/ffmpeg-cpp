/*
 * ffmpeg_data.hpp
 *
 *  Created on: 2017年1月20日
 *      Author: gh
 */

#ifndef FFMPEG_DATA_HPP_
#define FFMPEG_DATA_HPP_
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

#include "libavformat/ffm.h" // not public API

# include "libavfilter/avcodec.h"
# include "libavfilter/avfilter.h"
# include "libavfilter/buffersrc.h"
# include "libavfilter/buffersink.h"

#if HAVE_SYS_RESOURCE_H
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>
#elif HAVE_GETPROCESSTIMES
#include <windows.h>
#endif
#if HAVE_GETPROCESSMEMORYINFO
#include <windows.h>
#include <psapi.h>
#endif

#if HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#if HAVE_TERMIOS_H
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <termios.h>
#elif HAVE_KBHIT
#include <conio.h>
#endif

#if HAVE_PTHREADS
#include <pthread.h>
#endif

#include <time.h>

#include "ffmpeg.h"
#include <cmdutils-cpp.h>

#include "libavutil/avassert.h"

} //extern "C"


class ffmpeg_data
{
public:
	int asdfjlasdfjlafj;
	InputStream **input_streams = NULL;
	int        nb_input_streams = 0;
	InputFile   **input_files   = NULL;
	int        nb_input_files   = 0;

	OutputStream **output_streams = NULL;
	int         nb_output_streams = 0;
	OutputFile   **output_files   = NULL;
	int         nb_output_files   = 0;

	FilterGraph **filtergraphs = NULL;
	int        nb_filtergraphs = 0;

	char *vstats_filename = NULL;

	float audio_drift_threshold = 0.1;
	float dts_delta_threshold   = 10;
	float dts_error_threshold   = 3600*30;

	int audio_volume      = 256;
	int audio_sync_method = 0;
	int video_sync_method = VSYNC_AUTO;
	int do_deinterlace    = 0;
	int do_benchmark      = 0;
	int do_benchmark_all  = 0;
	int do_hex_dump       = 0;
	int do_pkt_dump       = 0;
	int copy_ts           = 0;
	int copy_tb           = -1;
	int debug_ts          = 0;
	int exit_on_error     = 0;
	int print_stats       = -1;
	int qp_hist           = 0;
	int stdin_interaction = 1;
	int frame_bits_per_raw_sample = 0;
	float max_error_rate  = 2.0/3;
	AVIOContext *progress_avio = NULL;

	AVIOInterruptCB int_cb = { NULL, NULL };


	const HWAccel hwaccels[10] = {
	#if HAVE_VDPAU_X11
	    { "vdpau", vdpau_init, HWACCEL_VDPAU, AV_PIX_FMT_VDPAU },
	#endif
	#if HAVE_DXVA2_LIB
	    { "dxva2", dxva2_init, HWACCEL_DXVA2, AV_PIX_FMT_DXVA2_VLD },
	#endif
	#if CONFIG_VDA
	    { "vda",   vda_init,   HWACCEL_VDA,   AV_PIX_FMT_VDA },
	#endif
	    { 0 },
	};


};
#define asdfjlasdfjlafj ffmpeg_data_p->asdfjlasdfjlafj
#define input_streams     (ffmpeg_data_p->input_streams)
#define nb_input_streams  (ffmpeg_data_p->nb_input_streams)
#define input_files       ffmpeg_data_p->input_files
#define nb_input_files    ffmpeg_data_p->nb_input_files

#define output_streams    ffmpeg_data_p->output_streams
#define nb_output_streams ffmpeg_data_p->nb_output_streams
#define output_files      ffmpeg_data_p->output_files
#define nb_output_files   ffmpeg_data_p->nb_output_files

#define filtergraphs      ffmpeg_data_p->filtergraphs
#define nb_filtergraphs   ffmpeg_data_p->nb_filtergraphs

#define vstats_filename   ffmpeg_data_p->vstats_filename

#define audio_drift_threshold ffmpeg_data_p->audio_drift_threshold
#define dts_delta_threshold   ffmpeg_data_p->dts_delta_threshold
#define dts_error_threshold   ffmpeg_data_p->dts_error_threshold

#define audio_volume      ffmpeg_data_p->audio_volume
#define audio_sync_method ffmpeg_data_p->audio_sync_method
#define video_sync_method  ffmpeg_data_p->video_sync_method
#define do_deinterlace    ffmpeg_data_p->do_deinterlace
#define do_benchmark      ffmpeg_data_p->do_benchmark
#define do_benchmark_all  ffmpeg_data_p->do_benchmark_all
#define do_hex_dump       ffmpeg_data_p->do_hex_dump
#define do_pkt_dump       ffmpeg_data_p->do_pkt_dump
#define copy_ts           ffmpeg_data_p->copy_ts
#define copy_tb           ffmpeg_data_p->copy_tb
#define debug_ts          ffmpeg_data_p->debug_ts
#define exit_on_error     ffmpeg_data_p->exit_on_error
#define print_stats       ffmpeg_data_p->print_stats
#define qp_hist           ffmpeg_data_p->qp_hist
#define stdin_interaction ffmpeg_data_p->stdin_interaction
#define frame_bits_per_raw_sample ffmpeg_data_p->frame_bits_per_raw_sample
#define max_error_rate    ffmpeg_data_p->max_error_rate
#define progress_avio     ffmpeg_data_p->progress_avio

#define int_cb            ffmpeg_data_p->int_cb



#endif /* FFMPEG_DATA_HPP_ */
