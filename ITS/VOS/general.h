/*
 * general.h
 *
 *  Created on: Nov 7, 2012
 *      Author: ngoc
 */
#ifndef __LIB_MKV_PUBLISHER_GENERAL_H__
#define __LIB_MKV_PUBLISHER_GENERAL_H__

#define STREAMS_MAX 128

#include <linux/types.h>
#include <inttypes.h>

enum TypeOfCodec{
	TYPE_CODEC_VIDEO,
	TYPE_CODEC_AUDIO,
	TYPE_CODEC_SUBTITLE
};

typedef struct _strm_info
{
	int codec_id;
	enum TypeOfCodec codec_type;
	int width;
	int height;
	int fps_num;
	int fps_den;
	int sample_rate;
	int channels;
	int bits_per_sample;

}strm_info;

typedef struct _info
{
	int64_t duration;
	int streams;
	strm_info st_info[STREAMS_MAX];

}info;

#endif//__LIB_MKV_PUBLISHER_GENERAL_H__
