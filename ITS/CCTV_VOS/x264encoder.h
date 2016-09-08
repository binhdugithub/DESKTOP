/*
 * x264encoder.h
 *
 *  Created on: Jul 17, 2014
 *      Author: xyz
 */

#ifndef X264ENCODER_H_
#define X264ENCODER_H_

#ifdef __cplusplus
#define __STDINT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
#include <iostream>
#include <QtGui/qimage.h>
#include <queue>
#include <stdint.h>
#include "mycommon.h"

extern "C" {
#include <x264.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
}

typedef struct ElcX264Params
{
	int witdth;		// frame width
	int height; 	// frame height
	int fps; 		// fps
	int bframe; 	// number of bframe
	int loglevel; 	// log level: (-1) no log, (0) log erro, (1) log wanning, (2) log info
	int bitrate;    // max bitrate
	int buffersize; // max buffer size, not excedd 240000, (by x264 default)
	ElcX264Params() : witdth(0), height(0), fps(30), bframe(0),
			loglevel(2), bitrate(90000), buffersize(240000){}

} ElcX264Params;


class X264Encoder
{
public:
	X264Encoder(void);
    ~X264Encoder(void);

public:
    bool initVideoEncoder(ElcX264Params& params);
    void closeVideoDecoder();
    void encodeFrame(QImage* image);
    bool isNalsAvailableInOutputQueue();
    x264_nal_t getNalUnit();
private:
    // Use this context to convert your BGR Image to YUV image
    // since x264 do not support RGB input
    SwsContext* convertContext;
    std::queue<x264_nal_t> outputQueue;
    x264_param_t parameters;
    x264_picture_t picture_in,picture_out;
    x264_t* encoder;
};

#endif /* X264ENCODER_H_ */
