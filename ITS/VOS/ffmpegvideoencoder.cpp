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
			codecID = CODEC_ID_H264;
			break;
		case CodecType::MPEG4:
			codecID = CODEC_ID_MPEG4;
			break;
		default:
			codecID = CODEC_ID_MPEG4;
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
	codecCtx->bit_rate = param.bitrate * 1000;
	codecCtx->bit_rate_tolerance = codecCtx->bit_rate + codecCtx->bit_rate /100;
	codecCtx->delay = 0;
	//codecCtx->coder_type = 0;
	//codecCtx->me_cmp |= 1;
	//codecCtx->me_method = ME_HEX;
	//codecCtx->me_subpel_quality = 0;
	//codecCtx->me_range = 16;
	//codecCtx->scenechange_threshold = 40;
	//codecCtx->i_quant_factor = 0.71;
	//codecCtx->b_frame_strategy = 1;
	//codecCtx->qcompress = 0.5;
	//codecCtx->qmin = 2;
	//codecCtx->qmax = 31;
	//codecCtx->max_qdiff = 4;
	//codecCtx->refs = 3;
	//codecCtx->trellis = 1;
	//codecCtx->chromaoffset = 0;
	//codecCtx->thread_count = 1;

	int error = avcodec_open2(codecCtx, codec, NULL);
	if (error < 0)
	{
		std::cout << "Open video encoder failed" << std::endl;
	}
	pic = av_frame_alloc();
	pic->width = param.width;
	pic->height = param.height;
	pic->format = param.colorSpace;
	avpicture_alloc((AVPicture*)pic, AV_PIX_FMT_YUV420P, pic->width, pic->height);
	convertCtx = sws_getContext(param.width, param.height, PIX_FMT_RGB24,
	    		param.width, param.height, PIX_FMT_YUV420P, SWS_FAST_BILINEAR, NULL, NULL, NULL);

	return true;
}

bool FFMpegVideoEncoder::closeVideoEncoder()
{
	// TODO : free all ....
	return true;
}

int FFMpegVideoEncoder::encodeVideoFrame(unsigned char* rawData,  unsigned long timestap, unsigned char* encodeData, unsigned long& sizeOut)
{
	int ret = 0;
	sizeOut = 0;
	// ============== case rawData is YUV =============
//	if (encodeParam.colorSpace == PIX_FMT_YUV420P)
//	{
//		pic->data[0] = rawData;
//		pic->data[1] = pic->data[0] + codecCtx->width*codecCtx->height;
//		pic->data[2] = pic->data[1] + ((codecCtx->width*codecCtx->height) >> 2);
//		pic->linesize[0] = codecCtx->width;
//		pic->linesize[2] = pic->linesize[1] = codecCtx->width >> 1;
//		//pic->colorspace
//	}

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

