/*
 * @file DummySink.h
 * @brief data processing from rtsp client
 * @author LongNV
 * @date 2014/7/10
 */

#ifndef DUMMY_SINK_H
#define DUMMY_SINK_H

#include "mycommon.h"
#include "FFMpegVideoDecoder.h"
#include "h264parser.h"
#include "vostype.h"

class DummySink: public MediaSink
{
public:
  static DummySink* createNew(UsageEnvironment& env,
			      MediaSubsession& subsession,
			      void (*)(VideoFrame*, void*), void* usrParam, char const* streamId = NULL);
  static void (*mOndata)(VideoFrame* vf, void* usr);
  uint32_t getLastDataTime() {return startReceivedTime;}
protected:
  // called only by createNew()
  DummySink(UsageEnvironment& env, MediaSubsession& subsession, void (*)(VideoFrame*, void*), void* usrParam, char const* streamId);

  virtual ~DummySink();

  static void afterGettingFrame(void* clientData, unsigned frameSize,
                                unsigned numTruncatedBytes,
				struct timeval presentationTime,
                                unsigned durationInMicroseconds);
  void afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
			 struct timeval presentationTime, unsigned durationInMicroseconds);

  // redefined virtual functions:
  virtual Boolean continuePlaying();

  // init video decoder
  bool openVideoDecoder();

  // close video decoder
  bool closeVideoDecoder();

  // on data decoded
  static void onVideoDataDecoded(const unsigned char* samples, unsigned int length,
		  unsigned long timestamp, void* user_data, unsigned long reserved1, unsigned long reserved2);

  // get frame widthxheight from sps
  void getSDPBinary(char* textInfor, SPropRecord* sps, SPropRecord* pps);

 // static void detecConnectionLost(void* userData);
 // void doDetecConnectionLost();



private:
  u_int8_t* fReceiveBuffer;
  MediaSubsession& fSubsession;
  char* fStreamId;
  FFMpegVideoDecoder* videoDecoder;
  int mVideoCodec;
  int mVideoHeight;
  int mVideoWidth;
  void* userParams;
  unsigned char* buff;
  std::thread* mThread;
  //std::unique_ptr<std::thread> mThread;
 // std::shared_ptr<std::thread> mThread;
  std::recursive_mutex threadLocker;
  uint32_t startReceivedTime;
  bool isStartThread;

};

#endif
