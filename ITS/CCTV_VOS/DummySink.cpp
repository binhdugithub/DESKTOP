#include "DummySink.h"
#include <iostream>
#include <string>
#include "imageoverlaytext.h"
#include "ElcRTSPClient.h"

using namespace std;

#define DUMMY_SINK_RECEIVE_BUFFER_SIZE 300000

void (*DummySink::mOndata)(VideoFrame*, void*) = NULL;

DummySink* DummySink::createNew(UsageEnvironment& env, MediaSubsession& subsession, void (*onData)(VideoFrame*, void* usr), void* usrParam, char const* streamId)
{
  return new DummySink(env, subsession, onData, usrParam, streamId);
}

DummySink::DummySink(UsageEnvironment& env, MediaSubsession& subsession, void (*onData)(VideoFrame*, void* usr), void* usrParam, char const* streamId)
  : MediaSink(env),
    fSubsession(subsession)
{
	std::cout << __FILE__ << ":" << __FUNCTION__ << std::endl;
  fStreamId = strDup(streamId);
  fReceiveBuffer = new u_int8_t[DUMMY_SINK_RECEIVE_BUFFER_SIZE];
  mVideoCodec = -1;
  mVideoHeight = mVideoWidth = 0;
  mOndata = onData;
  userParams = usrParam;
  buff=new unsigned char[1024*1024];
  startReceivedTime = 0;
  isStartThread = false;
  videoDecoder = NULL;
}

DummySink::~DummySink()
{
	std::cout << __FILE__ << ":" << __FUNCTION__ << std::endl;
	LOG_INFO("DummySink::~DummySink() Deconstructor");
	delete[] fReceiveBuffer;
	delete[] fStreamId;
	delete[] buff;
	if(isStartThread)
	{
		isStartThread = false;
		//sleep(8);
//		if(mThread != NULL)
//		{
//			mThread->join();
//			delete mThread;
//			mThread = NULL;
//		}
	}
}


bool DummySink::openVideoDecoder()
{
	std::cout << __FILE__ << ":" << __FUNCTION__ << std::endl;
	DecoderOptions params;
	params.callback_func = onVideoDataDecoded;
	params.user_data = this;
	params.codec_type = mVideoCodec;
	params.width = mVideoWidth;
	params.height = mVideoHeight;

	videoDecoder = new FFMpegVideoDecoder();
	videoDecoder->Init(&params);

	LOG_INFO("DummySink::openVideoDecoder Ok -codec="<<videoDecoder->codec()<<" -width="<<videoDecoder->width()<<" -height="<<videoDecoder->height());
	//cout<<"open video decoder successfully with video codec = "<<videoDecoder->codec()<<
	//		" Frame width = "<<videoDecoder->width()<<" Frame height = "<<videoDecoder->height()<<endl;
	return true;
}

bool DummySink::closeVideoDecoder()
{
	std::cout << __FILE__ << ":" << __FUNCTION__ << std::endl;
	if(videoDecoder)
	{
		delete videoDecoder;
		videoDecoder = NULL;
	}
	return true;
}

void DummySink::afterGettingFrame(void* clientData, unsigned frameSize, unsigned numTruncatedBytes,
				  struct timeval presentationTime, unsigned durationInMicroseconds)
{

    DummySink* sink = (DummySink*)clientData;
    sink->afterGettingFrame(frameSize, numTruncatedBytes, presentationTime, durationInMicroseconds);
}

// use to print in debug mode
#define DEBUG_PRINT_EACH_RECEIVED_FRAME 0

void DummySink::afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
				  struct timeval presentationTime, unsigned durationInMicroseconds)
{
  // init video decoder for the first time
  if(mVideoCodec == -1)
  {
	  if(fStreamId != NULL)
	  {
		  // TODO check if fSubsession.fmtp_spropparametersets() == NULL, goto openvideocodec and decode rtp pakage
		 double fps = (double)fSubsession.videoFPS();
		 if(fps > 0)
		 {
			 ImageOverlayText* ov = (ImageOverlayText*)userParams;
			 ov->encodeFps = fps;
		 }

		  SPropRecord *sps, *pps;
		  sps = (SPropRecord*)malloc(sizeof(SPropRecord));//new SPropRecord();
		  pps = (SPropRecord*)malloc(sizeof(SPropRecord));//+new SPropRecord();
		  std::string sprop = fSubsession.fmtp_spropparametersets();
		  if (sprop.length() > 0)
		  {
			  getSDPBinary((char*)fSubsession.fmtp_spropparametersets(), sps, pps);
			  cout << "______________Frame Size = " << mVideoWidth << "x" << mVideoHeight << "___________" << endl;
			  if (strcmp(fSubsession.codecName(), "H264") == 0)
				  mVideoCodec = 28; // codec stands for H264 AV_CODEC_ID_H264, AV_CODEC_ID_MPEG4 = 13
			  else
				  mVideoCodec = 100; // handle in case can not found video codec
		  }
		  openVideoDecoder();
		  if (sprop.length() > 0)
		  {
			  videoDecoder->Decode(sps->sPropBytes, sps->sPropLength, 0);
			  videoDecoder->Decode(pps->sPropBytes, pps->sPropLength, 0);
		  }

	  }
  }
  else // video decoder had been opened and ready for decode data
  {
	  //unsigned char* buff = (const unsigned char*)fReceiveBuffer;
	  //unsigned char* buff = /*(unsigned char*)malloc[frameSize+4];//*/new unsigned char[frameSize+4];
	  buff[0] = buff[1] = buff[2] = 0;
	  buff[3] = 1;
	  memcpy(buff+4, fReceiveBuffer, frameSize);
	  unsigned int len = (unsigned int)frameSize + 4;
	  unsigned long timeStamp = (unsigned long)(1000000*presentationTime.tv_sec +  presentationTime.tv_usec);
	 // std::cout << "DummySink: AfterGetFrame timstamp:" << timeStamp << std::endl;
	  videoDecoder->Decode(buff, len,timeStamp);

  }

  threadLocker.lock();
  startReceivedTime = elc::GetTickCount();
  threadLocker.unlock();

  if(!isStartThread)
  {
	  isStartThread = true;
  }
  // Then continue, to request the next frame of data:
  continuePlaying();
}


Boolean DummySink::continuePlaying() 
{

	if (fSource == NULL) return False;
    // Request the next frame of data from our input source.  "afterGettingFrame()" will get called later, when it arrives:
    fSource->getNextFrame(fReceiveBuffer, DUMMY_SINK_RECEIVE_BUFFER_SIZE, afterGettingFrame, this, onSourceClosure, this);
    return True;
}

void DummySink::onVideoDataDecoded(const unsigned char* samples, unsigned int length,
		  unsigned long timestamp, void* user_data, unsigned long reserved1, unsigned long reserved2)
{
	//cout<<"Data decoded!"<<endl;
	DummySink* pThis = (DummySink*)user_data;
	VideoFrame* vf = new VideoFrame();
	vf->data = (unsigned char*)samples;
	vf->width = pThis->mVideoWidth;
	vf->height = length / (pThis->mVideoWidth * 3);
	vf->time_stamp = timestamp;
	mOndata(vf, pThis->userParams);

}

void DummySink::getSDPBinary(char* textInfor, SPropRecord* sps, SPropRecord* pps)
{
	LOG_INFO("DummySink::getSDPBinary -dsptextinfo="<<textInfor);
	unsigned int result;
	SPropRecord* msps_pps = parseSPropParameterSets(textInfor, result);

	// add 4byte to sps, pps
//	size_t spsLen = msps->sPropLength + 4;
//	size_t ppsLen = mpps->sPropLength + 4;
	size_t spsLen = msps_pps[0].sPropLength + 4;
	size_t ppsLen = msps_pps[1].sPropLength + 4;
	//sps->sPropBytes = new unsigned char(((spsLen + 15) >> 4) << 4);
	//pps->sPropBytes = new unsigned char(((ppsLen + 15) >> 4) << 4);
	sps->sPropBytes = (unsigned char*)malloc(spsLen);//new unsigned char(spsLen);
	pps->sPropBytes = (unsigned char*)malloc(ppsLen);//new unsigned char(ppsLen);

	sps->sPropBytes[0] = sps->sPropBytes[1] = sps->sPropBytes[2] = pps->sPropBytes[0] = pps->sPropBytes[1] = pps->sPropBytes[2] = 0;
	sps->sPropBytes[3] = pps->sPropBytes[3] = 1;

	memcpy(sps->sPropBytes + 4, msps_pps[0].sPropBytes, msps_pps[0].sPropLength);
	memcpy(pps->sPropBytes + 4, msps_pps[1].sPropBytes, msps_pps[1].sPropLength);

	sps->sPropLength = spsLen;
	pps->sPropLength = ppsLen;

	h264_common_info info;
	if(h264_parse_sps(&info, msps_pps[0].sPropBytes, msps_pps[0].sPropLength) == 0)
	{
		mVideoWidth = info.width;
		mVideoHeight = info.height;
	}
}

