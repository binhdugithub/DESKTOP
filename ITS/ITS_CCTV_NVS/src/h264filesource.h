/*
 * H264FileSource.h
 *
 *  Created on: Jul 17, 2014
 *      Author: cuonglm
 */

#ifndef X264LIVESOURCE_H_
#define X264LIVESOURCE_H_

#include <liveMedia.hh>
#include <string>
#include <queue>
#include <vector>
#include "filehandler.h"
#include "commondef.h"


#ifdef __cplusplus
extern "C"
{
#endif
#include <libavformat/avformat.h>
#ifdef __cplusplus
}
#endif /*__cplusplus*/

class H264FileSource : public FramedSource
{
public:
    static H264FileSource* createNew(UsageEnvironment& env, std::vector<std::string> listFile, std::string ts, std::string te, std::string speed);


protected:
    H264FileSource(UsageEnvironment& env, std::vector<std::string> listFile, std::string ts, std::string te, std::string speed);
    virtual ~H264FileSource(void);
private:
    virtual void doGetNextFrame();
    static void deliverFrame0(void* clientData);
	static void* triggerEvent(void* pThis);
    void deliverFrame();
    void init();
    void fragment();
    static double get_microsecond();
    int getPosStart();
    int getPosStop();
    int getSpeed();
    unsigned char* mRTPDataToSend;
    AVPacket* mCurrentPacket;
    FileHandler* mFileReader;
    unsigned mTimeLastReceive;
    double mDurationCheck;
    unsigned mTimeStartReceive;
    double mTimeStartTransmit;
    double mTimeLastTransmit;
    double mFPS;
    std::string mAddr;
	EventTriggerId eventTriggerId;
    int count;
    int fileNumber;

    //std::vector<FileHandler*> mFileHandlerList;
    //std::vector<FileHandler*>::iterator mFileHandlerItorator;
    std::vector<std::string> mListFile;
    //std::vector<std::string>::iterator mListFileItorator;
    std::vector<std::string> splitvt;

    std::queue<AVPacket*> dataQueue;
    timeval currentTime;
    std::string filePath;
    std::string timeStart, timeStop, mSpeed;
    double speed;
    double timeCheck;
    int numFrameLast;
    int durationStart, durationStop, frameNumber;
    Boolean isEndFile;
    Boolean isExit;
    pthread_t mThread;
};

#endif /* H264FileSource */
