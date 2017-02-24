

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

#include "ffmpeg.h"

#include "libavutil/avassert.h"

int testfuc(const char *filename, const char *out_path, const char *outfilename, int64_t intral, int scal)
{
 		av_register_all();
 		return 0;
}
