

#include "cmdutils.hpp"
#include "ffmpeg_filter.hpp"

static int open_input_file_static(OptionsContext *o, const char *filename);
static int open_output_file_static(OptionsContext *o, const char *filename);
static int opt_preset_static(void *optctx, const char *opt, const char *arg);
static int opt_filter_complex_static(void *optctx, const char *opt, const char *arg);
static int opt_old2new_static(void *optctx, const char *opt, const char *arg);
static int opt_data_codec_static(void *optctx, const char *opt, const char *arg);
static int opt_audio_codec_static(void *optctx, const char *opt, const char *arg);
static int opt_video_channel_static(void *optctx, const char *opt, const char *arg);
static int opt_video_standard_static(void *optctx, const char *opt, const char *arg);
static int opt_video_filters_static(void *optctx, const char *opt, const char *arg);
static int opt_audio_qscale_static(void *optctx, const char *opt, const char *arg);
static int opt_qscale_static(void *optctx, const char *opt, const char *arg);
static int opt_profile_static(void *optctx, const char *opt, const char *arg);
static int opt_bitrate_static(void *optctx, const char *opt, const char *arg);
static int opt_map_channel_static(void *optctx, const char *opt, const char *arg);
static int opt_subtitle_codec_static(void *optctx, const char *opt, const char *arg);
static int opt_audio_filters_static(void *optctx, const char *opt, const char *arg);
static int opt_channel_layout_static(void *optctx, const char *opt, const char *arg);
static int opt_audio_frames_static(void *optctx, const char *opt, const char *arg);
static int opt_streamid_static(void *optctx, const char *opt, const char *arg);
static int opt_vstats_file_static(void *optctx, const char *opt, const char *arg);
static int opt_vstats_static(void *optctx, const char *opt, const char *arg);
static int opt_timecode_static(void *optctx, const char *opt, const char *arg);
static int opt_sameq_static(void *optctx, const char *opt, const char *arg);
static int opt_video_codec_static(void *optctx, const char *opt, const char *arg);
static int opt_video_frames_static(void *optctx, const char *opt, const char *arg);
static int opt_attach_static(void *optctx, const char *opt, const char *arg);
static int opt_filter_complex_script_static(void *optctx, const char *opt, const char *arg);
static int opt_vsync_static(void *optctx, const char *opt, const char *arg);
static int opt_target_static(void *optctx, const char *opt, const char *arg);
static int opt_progress_static(void *optctx, const char *opt, const char *arg);
static int opt_data_frames_static(void *optctx, const char *opt, const char *arg);
static int opt_recording_timestamp_static(void *optctx, const char *opt, const char *arg);
static int opt_map_static(void *optctx, const char *opt, const char *arg);
static int opt_timelimit_static(void *optctx, const char *opt, const char *arg);
static int show_help_static(void *optctx, const char *opt, const char *arg);
static int opt_loglevel_static(void *optctx, const char *opt, const char *arg);


#include "ffmpeg_opt.hpp"


static int open_input_file_static(OptionsContext *o, const char *filename)
{
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->open_input_file(o, filename);
}
static int open_output_file_static(OptionsContext *o, const char *filename)
{
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->open_output_file(o, filename);
}

static int opt_preset_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_preset(optctx, opt, arg);
}
static int opt_filter_complex_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_filter_complex(optctx, opt, arg);
}
static int opt_old2new_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_old2new(optctx, opt, arg);
}
static int opt_data_codec_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_data_codec(optctx, opt, arg);
}
static int opt_audio_codec_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_audio_codec(optctx, opt, arg);
}
static int opt_video_channel_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_video_channel(optctx, opt, arg);
}

static int opt_video_standard_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_video_standard(optctx, opt, arg);
}
static int opt_video_filters_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_video_filters(optctx, opt, arg);
}

static int opt_audio_qscale_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_audio_qscale(optctx, opt, arg);
}


static int opt_qscale_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_qscale(optctx, opt, arg);
}


static int opt_profile_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_profile(optctx, opt, arg);
}


static int opt_bitrate_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_bitrate(optctx, opt, arg);
}

static int opt_map_channel_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_map_channel(optctx, opt, arg);
}

static int opt_subtitle_codec_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_subtitle_codec(optctx, opt, arg);
}

static int opt_audio_filters_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_audio_filters(optctx, opt, arg);
}

static int opt_channel_layout_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_channel_layout(optctx, opt, arg);
}

static int opt_audio_frames_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_audio_frames(optctx, opt, arg);
}

static int opt_streamid_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_streamid(optctx, opt, arg);
}

static int opt_vstats_file_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_vstats_file(optctx, opt, arg);
}

static int opt_vstats_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_vstats(optctx, opt, arg);
}

static int opt_timecode_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_timecode(optctx, opt, arg);
}

static int opt_sameq_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_sameq(optctx, opt, arg);
}

static int opt_video_codec_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_video_codec(optctx, opt, arg);
}

static int opt_video_frames_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_video_frames(optctx, opt, arg);
}

static int opt_attach_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_attach(optctx, opt, arg);
}

static int opt_filter_complex_script_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_filter_complex_script(optctx, opt, arg);
}

static int opt_vsync_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_vsync(optctx, opt, arg);
}

static int opt_target_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_target(optctx, opt, arg);
}

static int opt_progress_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_progress(optctx, opt, arg);
}

static int opt_data_frames_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_data_frames(optctx, opt, arg);
}

static int opt_recording_timestamp_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_recording_timestamp(optctx, opt, arg);
}


static int opt_map_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->opt_map(optctx, opt, arg);
}

static int opt_timelimit_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->cmdutils_p->opt_timelimit(optctx, opt, arg);
}

static int show_help_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->cmdutils_p->show_help(optctx, opt, arg);
}
static int opt_loglevel_static(void *optctx, const char *opt, const char *arg)
{
	OptionsContext *o = (OptionsContext *)optctx;
	ffmpeg_opt *p = (ffmpeg_opt *)o->ffmpeg_opt;
	return p->cmdutils_p->opt_loglevel(optctx, opt, arg);
}

void show_usage(void)
{
    av_log(NULL, AV_LOG_INFO, "Hyper fast Audio and Video encoder\n");
    av_log(NULL, AV_LOG_INFO, "usage: %s [options] [[infile options] -i infile]... {[outfile options] outfile}...\n", "ffmpeg");
    av_log(NULL, AV_LOG_INFO, "\n");
}

void show_help_default(void *p, const char *opt, const char *arg)
{
	ffmpeg_opt * pf = (ffmpeg_opt *)p;
	pf->show_help_default(opt, arg);
}

int ffmpeg_parse_options(void *p, int argc, char **argv)
{
	ffmpeg_opt * pf = (ffmpeg_opt *)p;
	return pf->ffmpeg_parse_options(argc, argv);

}

const OptionDef *get_options(void *p)
{
	ffmpeg_opt * pf = (ffmpeg_opt *)p;
	return pf->options;
}

ffmpeg_opt *alloc_ffmpeg_opt()
{
	ffmpeg_opt *p = new ffmpeg_opt();
	return p;
}

void free_ffmpeg_opt(ffmpeg_opt *p)
{
	delete p;
}

void set_opts_ffmpeg_opt(ffmpeg_opt *p,	ffmpeg *ffmp, cmdutils *cmdutils_p, ffmpeg_data *ffmpeg_data_p, ffmpeg_filter *filter)
{
	p->cmdutils_p = cmdutils_p;
	p->ffmpeg_data_p = ffmpeg_data_p;
	p->ffmpeg_filter_p = filter;
	p->ffmpeg_p = ffmp;
}


