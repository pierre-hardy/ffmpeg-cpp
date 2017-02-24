//============================================================================
// Name        : ffmpeg.cpp
// Author      : ganhui
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <exception>
#include <sstream>
#include <string>
#include "ffmpeglib.h"

using namespace std;

extern "C" int ffmpeg_main(int argc, char **argv);
extern "C" int testfuction();

class ffmpeg;
class ffmpeg_opt;
class cmdutils;
ffmpeg *alloc_ffmpeg();
int ffmpeg_main(ffmpeg *p, int argc, char **argv);
void free_ffmpeg(ffmpeg *p);

#if !defined(FFMPEG_LIB)
extern "C" int main(int argc, char **argv) {
	int ret = -1;
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
//	return ffmpeg_main(argc, argv);
	ffmpeg *p = NULL;

	ffmpeg_convert_jpg("./out.mp4", "./", "image", 8000, 50);
	for(int i=0; i<1; i++) {
//		ret = ffmpeg_convert("-i ./20170125_151253.mp4 	-y	-r 0.1 -f image2 image-%3d.jpeg");
	}

	return ret;
}
#endif

extern "C" int ffmpeg_convert(const char *arg)
{
	int ret = -1;
	string str(arg);
    string buf; // Have a buffer string
    stringstream ss(str); // Insert the string into a stream

    vector<string> tokens; // Create vector to hold our words

	while (ss >> buf)
	    tokens.push_back(buf);
	char *args[1000] = {"ffmpeg"};
	for(int i=0; i<tokens.size() && tokens.size() < 1000; i++)
		args[i+1] = tokens[i].c_str();
	ffmpeg *p = alloc_ffmpeg();
	try {
		ret = ffmpeg_main(p, tokens.size()+1, args);
	}
	catch(exception e2) {
		cout << "catch err!!!"<< e2.what() << endl;
	}
	catch(...) {
		cout << "catch err!!!" << endl;
	}
	free_ffmpeg(p);
	return ret;
}



