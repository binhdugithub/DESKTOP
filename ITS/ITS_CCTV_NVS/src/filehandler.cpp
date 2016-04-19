/*
 * filehandler.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: hungnv
 */

#include "filehandler.h"
#include <iostream>

FileHandler::FileHandler()
	: mCtx(NULL)
	, mCurrentPacket(NULL)
	, mSPS(NULL)
	, mSPSLen(0)
	, mPPS(NULL)
	, mPPSLen(0)
{

}

FileHandler::~FileHandler()
{
	if(mCtx)
	{
		avformat_close_input(&mCtx);
	}

	if(mSPS)
	{
		delete[] mSPS;
		mSPS = NULL;
	}

	if(mPPS)
	{
		delete[] mPPS;
		mPPS = NULL;
	}
}

bool FileHandler::OpenFile(const char* fileName)
{
	int err;
	AVInputFormat* input = av_find_input_format("mp4");
	if(!input)
		return false;

	err = avformat_open_input(&mCtx, fileName, 0, 0);   //input
	if(err < 0)
		return false;

	err = avformat_find_stream_info(mCtx, NULL);
	if(err < 0)
	{
		avformat_close_input(&mCtx);
		return false;
	}

	av_read_play(mCtx);
	//*
	//CuongLM: get FPS of file
    //*
	AVStream *st = *(mCtx->streams);
	mFPS = (double)st->avg_frame_rate.num / (double)st->avg_frame_rate.den;
	std::cout<<"mFPS    "<<mFPS<<std::endl;

	for(unsigned int i = 0; i < mCtx->nb_streams; i++)
	{
		//std::cout <<"mCtx->streams[i]->codec->codec_type =" << mCtx->streams[i]->codec->codec_type << " AVMEDIA_TYPE_VIDEO= " << AVMEDIA_TYPE_VIDEO << std::endl;
		if(mCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{

			std::cout << "mCtx->streams[i]->codec->extradata size =" << mCtx->streams[i]->codec->extradata_size << std::endl;
			std::cout << "mCtx->streams[i]->codec->extradata =" << (void*)mCtx->streams[i]->codec->extradata << std::endl;

			if(mCtx->streams[i]->codec->flags & CODEC_FLAG_GLOBAL_HEADER)
			{
				std::cout << "Have global header" << std::endl;
			}

			if(mCtx->streams[i]->codec->flags2 & CODEC_FLAG_GLOBAL_HEADER)
			{
				std::cout << "Have global header2" << std::endl;
			}
			if(mCtx->streams[i]->codec->extradata)
			{
				mSPSLen = mCtx->streams[i]->codec->extradata[6];
				mSPSLen <<= 8;
				mSPSLen |= mCtx->streams[i]->codec->extradata[7];

				std::cout << "Got SPS len = " << mSPSLen << std::endl;
				mSPS = new unsigned char[mSPSLen];
				memcpy(mSPS, mCtx->streams[i]->codec->extradata + 8, mSPSLen);

				mPPSLen = mCtx->streams[i]->codec->extradata[mSPSLen + 8 + 1];
				mPPSLen <<= 8;
				mPPSLen |= mCtx->streams[i]->codec->extradata[mSPSLen + 8 + 2];

				std::cout << "Got PPS len = " << mPPSLen << std::endl;
				mPPS = new unsigned char[mPPSLen];
				memcpy(mPPS, mCtx->streams[i]->codec->extradata + mSPSLen + 8 + 3, mPPSLen);
			}
		}
	}

	return true;
}

AVPacket* FileHandler::ReadFrame()
{
	int ret;

	if(!mCtx)
		return NULL;

	if(mCurrentPacket)
	{
		av_free_packet(mCurrentPacket);
		mCurrentPacket = NULL;
	}

	ret = av_read_frame(mCtx, &mPacket);
	if(ret < 0)
		return NULL;

	mCurrentPacket = &mPacket;
	return mCurrentPacket;
}

bool FileHandler::SeekTo(int64_t pts)
{
	if(!mCtx)
		return false;
	int64_t pos = pts > 0 ? pts : -pts;
	if(mCurrentPacket)
	{
		av_free_packet(mCurrentPacket);
		mCurrentPacket = NULL;
	}
	return (av_seek_frame(mCtx, -1, pos, AVSEEK_FLAG_BACKWARD) == 0);

}


int FileHandler::seekToFrame(int64_t fn)
{
	if(!mCtx)
		return false;
	int64_t fr = fn >0 ? fn : -fn;
	if(mCurrentPacket)
	{
		av_free_packet(mCurrentPacket);
		mCurrentPacket = NULL;
	}
	return avformat_seek_file(mCtx, -1, 0, fr, fr, AVSEEK_FLAG_FRAME);
}
int64_t FileHandler::GetDuration()
{
	if(!mCtx)
		return 0;

	return mCtx->duration;
}

bool FileHandler::IsVideoStream(int stream_id)
{
	return (mCtx->streams[stream_id]->codec->codec_type == AVMEDIA_TYPE_VIDEO);
}

int FileHandler::getCodec()
{
   return (mCtx->streams[0]->codec->codec_id);
}

bool FileHandler::IsAudioStream(int stream_id)
{
	return (mCtx->streams[stream_id]->codec->codec_type == AVMEDIA_TYPE_AUDIO);
}
