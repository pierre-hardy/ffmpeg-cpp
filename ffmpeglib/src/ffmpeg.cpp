#include "cmdutils.hpp"
#include "ffmpeg_filter.hpp"

static int decode_interrupt_cb(void *p);
static int compare_int64(const void *a, const void *b);
static void log_callback_null(void *ptr, int level, const char *fmt, va_list vl);
static int get_buffer(AVCodecContext *s, AVFrame *frame, int flags);
static enum AVPixelFormat get_format_static(AVCodecContext *s, const enum AVPixelFormat *pix_fmts);
static void ffmpeg_cleanup_static(void *p, int ret);


#include <ffmpeg.hpp>

static int decode_interrupt_cb(void *p)
{
	ffmpeg *ctx = (ffmpeg *)p;
    return ctx->received_nb_signals > ctx->transcode_init_done;
}

static int compare_int64(const void *a, const void *b)
{
    int64_t va = *(int64_t *)a, vb = *(int64_t *)b;
    return va < vb ? -1 : va > vb ? +1 : 0;
}
static void log_callback_null(void *ptr, int level, const char *fmt, va_list vl)
{
}


static int get_buffer(AVCodecContext *s, AVFrame *frame, int flags)
{
    InputStream *ist = (InputStream *)s->opaque;

    if (ist->hwaccel_get_buffer && frame->format == ist->hwaccel_pix_fmt)
        return ist->hwaccel_get_buffer(s, frame, flags);

    return avcodec_default_get_buffer2(s, frame, flags);
}

static enum AVPixelFormat get_format_static(AVCodecContext *s, const enum AVPixelFormat *pix_fmts)
{
    InputStream *ist = (InputStream *)s->opaque;
    return ((ffmpeg *)ist->ffmpeg)->get_format(s, pix_fmts);
}

static void ffmpeg_cleanup_static(void *p, int ret)
{
	ffmpeg *a = (ffmpeg *)p;
	a->ffmpeg_cleanup(ret);
}

int guess_input_channel_layout(void *fp, InputStream *ist)
{
	ffmpeg * p = (ffmpeg *)fp;
	return p->guess_input_channel_layout(ist);
}

void term_init(void *fp)
{
	ffmpeg * p = (ffmpeg *)fp;
	p->term_init();
}

void term_exit(void *fp)
{
	ffmpeg * p = (ffmpeg *)fp;
	p->term_exit();
}

void remove_avoptions(void *fp, AVDictionary **a, AVDictionary *b)
{
	ffmpeg * p = (ffmpeg *)fp;
	p->remove_avoptions(a, b);
}

void assert_avoptions(void *fp, AVDictionary *m)
{
	ffmpeg * p = (ffmpeg *)fp;
	p->assert_avoptions(m);
}


ffmpeg *alloc_ffmpeg()
{
	ffmpeg *p = new ffmpeg();
	return p;
}

int ffmpeg_main(ffmpeg *p, int argc, char **argv)
{
	return p->ffmpeg_main(argc, argv);
}

void free_ffmpeg(ffmpeg *p)
{
	delete p;
}

const struct AVRational AVRational_tempXCVBN ={1, AV_TIME_BASE};
