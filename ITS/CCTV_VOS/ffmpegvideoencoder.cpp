/*
 * ffmpegvideoencoder.cpp
 *
 *  Created on: Jul 22, 2014
 *      Author: xyz
 */

#include "ffmpegvideoencoder.h"
#include <QtGui/qimage.h>

FFMpegVideoEncoder::FFMpegVideoEncoder()
{
	// TODO Auto-generated constructor stub

}

FFMpegVideoEncoder::~FFMpegVideoEncoder()
{
	// TODO Auto-generated destructor stub
}

bool FFMpegVideoEncoder::openVideoEncoder(const VideoEncoderParam& param)
{
	encodeParam = param;
	AVCodecID codecID;
	switch(param.codec)
	{
		case CodecType::H264:
			codecID = AV_CODEC_ID_H264;
			break;
		case CodecType::MPEG4:
			codecID = AV_CODEC_ID_MPEG4;
			break;
		default:
			codecID = AV_CODEC_ID_MPEG4;
			break;

	}
	codec = avcodec_find_encoder(codecID);
	codecCtx = avcodec_alloc_context3(codec);
	codecCtx->gop_size = param.gop;
	codecCtx->max_b_frames = param.bframe;
	codecCtx->width = param.width;
	codecCtx->height = param.height;

	codecCtx->time_base.num = param.fpsDen;
	codecCtx->time_base.den = param.fpsNum;
	codecCtx->pix_fmt = param.colorSpace;
	codecCtx->rc_max_rate = codecCtx->rc_min_rate = codecCtx->bit_rate = param.bitrate * 100;
	codecCtx->rc_buffer_size = 0;
	codecCtx->rc_initial_buffer_occupancy = -1;
	codecCtx->delay = 0;
	codecCtx->qcompress = 0.0;
	codecCtx->max_qdiff = 3;
	codecCtx->qmin = 25;
	codecCtx->qmax = 35;
	codecCtx->bit_rate_tolerance = 0;
	codecCtx->flags |= CODEC_FLAG_LOOP_FILTER;
	codecCtx->flags2 |= CODEC_FLAG2_FAST;

	int error = avcodec_open2(codecCtx, codec, NULL);
	if (error < 0)
	{
		//std::cout << "Open video encoder failed" << std::endl;
		LOG_ERROR("Open H.264 video encoder failed");
	}

	pic = av_frame_alloc();
	pic->width = param.width;
	pic->height = param.height;
	pic->format = param.colorSpace;
	avpicture_alloc((AVPicture*)pic, AV_PIX_FMT_YUV420P, pic->width, pic->height);
	convertCtx = sws_getContext(param.width, param.height, AV_PIX_FMT_RGB24,
	    		param.width, param.height, AV_PIX_FMT_YUV420P, SWS_FAST_BILINEAR, NULL, NULL, NULL);

	return true;
}

bool FFMpegVideoEncoder::closeVideoEncoder()
{
	// TODO : free all ....
	return true;
}

int FFMpegVideoEncoder::encodeVideoFrame(unsigned char* rawData,  unsigned long timestap, unsigned char* encodeData, unsigned long& sizeOut)
{
	//std::cout << __FILE__ << ":" << __FUNCTION__ << std::endl;

	//return 0;
	int ret = 0;
	sizeOut = 0;


	// =========== case rawData is RGB24 ==============
	// raw data is rgb24, need to convert to YUV420 before putting to encoder

	uint8_t* inData[4] = {rawData, 0, 0, 0}; // RGB24 have one plane
	int inLinesize[4] = {3*codecCtx->width, 0, 0, 0};  // RGB stride
	sws_scale(convertCtx, inData, inLinesize, 0, codecCtx->height, pic->data, pic->linesize);

	av_init_packet(&pkt);
	pkt.data = NULL;// mBuffer;
	pkt.size = 0;// mBufferSize;
	pic->pts = timestap;
	ret = avcodec_encode_video2(codecCtx, &pkt, pic, &encodeSize);
	if (encodeSize > 0)
	{
		memcpy(encodeData, pkt.data, pkt.size);
		sizeOut = pkt.size;
	}
	av_free_packet(&pkt);
	return encodeSize;
}

