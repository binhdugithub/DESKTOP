/*
 * mpeg4livesource.h
 *
 *  Created on: Jul 21, 2014
 *      Author: xyz
 */

#ifndef MPEG4LIVESOURCE_H_
#define MPEG4LIVESOURCE_H_

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}
#include <liveMedia/liveMedia.hh>
#include <QtGui/qimage.h>
#include "mycommon.h"
#include "imageoverlaytext.h" // just for test
#include "ffmpegvideoencoder.h"
#include "vostype.h"

class Mpeg4LiveSource : public FramedSource
{
public:
    static Mpeg4LiveSource* createNew(UsageEnvironment& env, const string& url);
    static EventTriggerId eventTriggerId;
    virtual Boolean isMPEG4VideoStreamFramer() const
    {
    	return 1;
    }
    void closeSource();
protected:
    Mpeg4LiveSource(UsageEnvironment& env, const string& url);
    virtual ~Mpeg4LiveSource(void);
    static void startEncodeVideo(void* userParam);

private:
    virtual void doGetNextFrame();
    static void deliverFrame0(void* clientData);
    void deliverFrame();
    void encodeNewFrame();
    static unsigned referenceCount;
    timeval currentTime;
    QImage* image;
    string mUrl;
    ImageOverlayText* videoEffect;
    std::queue<Mpeg4Package*> mp4Que;
    std::queue<Mpeg4Package> mp4QueHistory;
    int buffLen;
    FFMpegVideoEncoder* encoder;
    VideoEncoderParam param;
    SwsContext* convertCtx; // convert rgb to yuv context
    std::thread* mThread;
    std::recursive_mutex dataLocker;
    uint8_t* encodeData; // data after encode
    unsigned long encodeSize;
    ImageOverlayText* ov; //overlay

    // for debug
    unsigned long lastDeliver;
};


#endif /* MPEG4LIVESOURCE_H_ */
