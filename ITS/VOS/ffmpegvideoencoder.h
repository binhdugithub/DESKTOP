/*
 * ffmpegvideoencoder.h
 *
 *  Created on: Jul 22, 2014
 *      Author: xyz
 */

#ifndef FFMPEGVIDEOENCODER_H_
#define FFMPEGVIDEOENCODER_H_

extern "C" {
#include <libavutil/avutil.h>
#include <libavutil/avstring.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libswscale/swscale.h>
}

#include "mycommon.h"


enum CodecType {H264, MPEG4 /*...*/};

typedef struct VideoEncoderParam
{
	int width;
	int height;
	int bitrate;
	int bframe;
	int gop;
	int fpsDen;
	int fpsNum;
	CodecType codec;
	AVPixelFormat colorSpace;
	// default param
	VideoEncoderParam() : codec(CodecType::MPEG4), width(1024), height(768),
			bitrate(1024),bframe(0), gop(10), fpsDen(1), fpsNum(30), colorSpace(PIX_FMT_YUV420P) {}

} VideoEncoderParam;

class FFMpegVideoEncoder
{
public:
	FFMpegVideoEncoder();
	virtual ~FFMpegVideoEncoder();
	bool openVideoEncoder(const VideoEncoderParam& param);
	bool closeVideoEncoder();
	int encodeVideoFrame(unsigned char* rawData,  unsigned long timestamp, unsigned char* encodeData, unsigned long& sizeOut);
	//void getVideoEncode(unsigned char* encodeData, unsigned long& len, unsigned long& timestamp);
private:
	VideoEncoderParam encodeParam;
	AVPacket pkt;
	AVCodec* codec;
	AVCodecContext* codecCtx;
	AVFrame* pic;
	int encodeSize;
	SwsContext* convertCtx;
	//void (*monEncodeData)(unsigned char* rawData, unsigned long len, unsigned long timestamp); //just in case
};

#endif /* FFMPEGVIDEOENCODER_H_ */
