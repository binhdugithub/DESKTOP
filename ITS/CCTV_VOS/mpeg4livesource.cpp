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
//    param = VideoEncoderParam();
//    param.width = ov->imgWidth;
//    param.height = ov->imgHeight;
//    param.gop = 5;
//    param.bitrate = 500;
//    encoder = new FFMpegVideoEncoder();
//    encoder->openVideoEncoder(param);
//    convertCtx = sws_getContext(param.width, param.height, AV_PIX_FMT_RGB24,
//    		param.width, param.height, AV_PIX_FMT_YUV420P, SWS_FAST_BILINEAR, NULL, NULL, NULL);
//
//    encodeData = new uint8_t[1024*1024];
//    encodeSize = 0;
//
//
//    image = NULL;
    LOG_INFO ("Mpeg4LiveSource::Mpeg4LiveSource create successfully");
    //mThread = new std::thread(startEncodeVideo, this);
}


Mpeg4LiveSource::~Mpeg4LiveSource(void)
{
    --referenceCount;
//    encoder->closeVideoEncoder();
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
{
}

void Mpeg4LiveSource::deliverFrame0(void* clientData)
{
    ((Mpeg4LiveSource*)clientData)->deliverFrame();
}

void Mpeg4LiveSource::doGetNextFrame()
{
	Mpeg4Package* mpk = NULL;// new Mpeg4Package();

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
}
