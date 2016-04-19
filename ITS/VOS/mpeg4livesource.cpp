/*
 * mpeg4livesource.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: xyz
 */

#include "mpeg4livesource.h"
#include "DummySink.h"
#include "ElcRTSPClient.h"
#include "LogFile.h"

EventTriggerId Mpeg4LiveSource::eventTriggerId = 0;
unsigned Mpeg4LiveSource::referenceCount = 0;

Mpeg4LiveSource* Mpeg4LiveSource::createNew(UsageEnvironment& env, const string& url)
{
	//cout<<"createNew Mpeg4LiveSource"<<endl;
    return new Mpeg4LiveSource(env, url);
}

Mpeg4LiveSource::Mpeg4LiveSource(UsageEnvironment& env, const string& url):FramedSource(env)
{
	LOG_INFO ("Mpeg4LiveSource::Mpeg4LiveSource constructor -add=" << this);
	lastDeliver = elc::GetTickCount();

    if(referenceCount == 0)
    {
    	//TODO: ...
    }
    ++referenceCount;
    mUrl = url;
    //LOG_INFO ("Mpeg4LiveSource::Mpeg4LiveSource create new videoeffect");
   // videoEffect = new ImageOverlayText();

    if(eventTriggerId == 0)
    {
    	//LOG_INFO ("Mpeg4LiveSource::Mpeg4LiveSource EventriggerID=0");
        eventTriggerId = envir().taskScheduler().createEventTrigger(deliverFrame0);
    }
    //LOG_INFO ("Mpeg4LiveSource::Mpeg4LiveSource get overlay");
    ov = SourceManager::getSingletonPtr()->findOverlay(mUrl);
    //LOG_INFO ("Mpeg4LiveSource::Mpeg4LiveSource setup params");
    param = VideoEncoderParam();
    param.width = ov->imgWidth;
    param.height = ov->imgHeight;
    param.gop = 5;
    param.bitrate = 500;
    encoder = new FFMpegVideoEncoder();
    encoder->openVideoEncoder(param);
    convertCtx = sws_getContext(param.width, param.height, PIX_FMT_RGB24,
    		param.width, param.height, PIX_FMT_YUV420P, SWS_FAST_BILINEAR, NULL, NULL, NULL);

    encodeData = new uint8_t[1024*1024];
    encodeSize = 0;


    image = NULL;
    LOG_INFO ("Mpeg4LiveSource::Mpeg4LiveSource create successfully");
    //mThread = new std::thread(startEncodeVideo, this);
}


Mpeg4LiveSource::~Mpeg4LiveSource(void)
{
    --referenceCount;
    encoder->closeVideoEncoder();
    envir().taskScheduler().deleteEventTrigger(eventTriggerId);
    eventTriggerId = 0;
}

static char makercode[]="001";
#define MAKER_CODE_LEN 0

void Mpeg4LiveSource::startEncodeVideo(void* userParam)
{
	cout<<"Begin encoding thread"<<endl;
	LOG_INFO("Mpeg4LiveSource::startEncodeVideo");
	Mpeg4LiveSource* pThis = (Mpeg4LiveSource*)userParam;
	pThis->encodeNewFrame();
}

void Mpeg4LiveSource::encodeNewFrame()
{/*
	image = ov->getImage();
	if(!image)
	{	usleep(100);
		return;
	}

	uint32_t timeStamp = elc::GetTickCount();
	encoder->encodeVideoFrame(image->bits(), timeStamp, encodeData, encodeSize);
	//uint32_t endTime = elc::GetTickCount(); // use to calculate time execution
	if(encodeSize <= 0)
		return;
	Mpeg4Package* package0 = new Mpeg4Package();
	package0->data = new uint8_t[encodeSize];
	memcpy(package0->data, encodeData, encodeSize);
	package0->len = encodeSize;

	///dataLocker.lock();
	mp4Que.push(package0);
	//dataLocker.unlock();

	delete image; image = NULL;

	return;*/
//	buffLen = 1400; //byte
//	int mcount = 0;
//	if(decode_size <= buffLen)
//	{
//		//data = new uint8_t[buffLen];
//		Mpeg4Package package = Mpeg4Package();
//		package.data = new uint8_t[buffLen];
//		memcpy(package.data , dst, buffLen);
//		package.len = buffLen;
//		mp4Que.push(package);
//		//delete [] package;
//		//package = nullptr;
//	}
//	else
//	{
//		while(mcount < decode_size)
//		{
//			Mpeg4Package package = Mpeg4Package();
//			if(decode_size - mcount > buffLen)
//			{
//				package.data = new uint8_t[buffLen];
//				memcpy(package.data , dst, buffLen);
//				package.len = buffLen;
//			}
//			else
//			{
//				package.data = new uint8_t[decode_size - mcount + MAKER_CODE_LEN];
//				if (MAKER_CODE_LEN)
//					memcpy(package.data, makercode, MAKER_CODE_LEN);
//				memcpy(package.data + MAKER_CODE_LEN , dst, decode_size - mcount);
//				package.len = decode_size - mcount + MAKER_CODE_LEN;
//			}
//
//			mp4Que.push(package);
//			mcount += buffLen;
//			//delete [] package;
//			//package = nullptr;
//		}
//	}
//	//delete [] dst;
//	//dst = nullptr;
////	if(!mp4Que.empty())
////		mp4QueHistory = mp4Que;
////	else if(!mp4QueHistory.empty())
////		mp4Que = mp4QueHistory;
	//return;
}

void Mpeg4LiveSource::deliverFrame0(void* clientData)
{
    ((Mpeg4LiveSource*)clientData)->deliverFrame();
}

void Mpeg4LiveSource::doGetNextFrame()
{
	//cout<<"ov add: "<<ov<<endl;
//	unsigned long delta = elc::GetTickCount() - lastDeliver;
//	//LOG_INFO ("Mpeg4LiveSource " << this << " deliver at timestamp= " << elc::GetTickCount() << ", delta=" << delta);
//	lastDeliver = elc::GetTickCount();
	Mpeg4Package* mpk = NULL;// new Mpeg4Package();

//	for(;;)
//	{
//		//dataLocker.lock();
//		if(!mp4Que.empty())
//		{
//			mpk = mp4Que.front();
//			mp4Que.pop();
//			//dataLocker.unlock();
//			usleep(1000);
//			break;
//		}
//		else
//		{
//			unsigned long startenc = elc::GetTickCount();
//			encodeNewFrame();
//			LOG_INFO ("Mpeg4LiveSource " << this << " encode duration = " << elc::GetTickCount() - startenc);
//		}
//	}

	while(1)
	{
		mpk = ov->getEncodeData();
		if(mpk) break;
		usleep(10*1000);
	}

	if(!isCurrentlyAwaitingData())
		return;


	//usleep(1000*1);

	gettimeofday(&currentTime,NULL);
	fPresentationTime = currentTime;

	if(mpk->len > 0 && mpk->len < fMaxSize)
	{
		fFrameSize = mpk->len;
		memmove(fTo, mpk->data, fFrameSize);
	}
	else
	{
		fTo = NULL;
		fFrameSize = 0;
		cout<<"No Frame, Handling closure"<<endl;
		handleClosure(this);
	}

	mpk->release();
	delete mpk;
	mpk = NULL;
	//cout<<"deleve frame ..."<<endl;
	FramedSource::afterGetting(this);

}

void Mpeg4LiveSource::closeSource()
{
	LOG_INFO("Mpeg4LiveSource::close close mpeg4livesource");
	handleClosure(this);
}


void Mpeg4LiveSource::deliverFrame()
{
	if(!isCurrentlyAwaitingData())
		return;

	//Mpeg4Package mpk;
//	static Mpeg4Package mpkHis;
//	if(!mp4Que.empty())
//	{
//		Mpeg4Package mpk = mp4Que.front();
//		mp4Que.pop();
//		mpkHis.data = new uint8_t[mpk.len];
//		memcpy(mpkHis.data, mpk.data, mpk.len);
//		mpkHis.len = mpk.len;
//	}
//	else
//	{
//		mpk.data = new uint8_t[mpkHis.len];
//		memcpy(mpk.data, mpkHis.data, mpkHis.len);
//		mpk.len = mpkHis.len;
//	}
	//if(mp4Que.size() == 1)
		//fPictureEndMarker = true;

//
//	Mpeg4Package* mpk = mp4Que.front();
//	mp4Que.pop();
//	if(mpk.len > fMaxSize)
//	{
//		fFrameSize = fMaxSize;
//		fNumTruncatedBytes = mpk.len - fMaxSize;
//	}
//	else
//	{
//		fFrameSize = mpk.len;
//	}
//	fPresentationTime = currentTime;
//
//	cout<<"Delivery Frame: packet len=" << mpk.len << ", size of que "<<mp4Que.size()<<endl;
//
//	memmove(fTo, mpk.data, fFrameSize);
//	mpk.release();
//	//fPictureEndMarker = true;
//	//delete mpk.data;
//	//delete mpk;
//
//	FramedSource::afterGetting(this);

}
