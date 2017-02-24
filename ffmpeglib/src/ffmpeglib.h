#ifndef SRC_FFMPEGLIB_H_
#define SRC_FFMPEGLIB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

int ffmpeg_convert(const char *arg);
/*
 *
 * 视频转图片接口
 * 参数：
 * filename：视频源地址，ffmpeg支持的协议有效
 *   out_path：生成图片文件保存的路径
 *   outfilename：生成图片文件的名字，不能使用printf的字符串格式
 *   intral：截取图片的间隔时间，毫秒为单位
 *   scal：缩放比例，100表示一比一
 *   callback：每次成功生成图片时调用的回调函数，回调的参数为图片文件的全路径，回调中可以对文件进行操作
 *
 * 返回：
 *   成功返回0，否则返回负数
 */
int ffmpeg_convert_jpg(const char *filename, const char *out_path, const char *outfilename, int64_t intral, int scal, int (*callback)(void *));


#ifdef __cplusplus
}
#endif

#endif /* SRC_FFMPEGLIB_H_ */
