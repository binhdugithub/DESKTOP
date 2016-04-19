/*
 * mpeg4filesource.h
 *
 *  Created on: 7 Aug, 2014
 *      Author: cuonglm
 */

#ifndef MPEG4FILESOURCE_H_
#define MPEG4FILESOURCE_H_

#include <liveMedia.hh>
#include <string>
#include <queue>
#include <vector>
#include "filehandler.h"


#ifdef __cplusplus
extern "C"
{
#endif
#include <libavformat/avformat.h>
#ifdef __cplusplus
}
#endif /*__cplusplus*/

class Mpeg4FileSource : public FramedSource
{
public:
    static Mpeg4FileSource* createNew(UsageEnvironment& env, std::vector<std::string> listFile, std::string ts, std::string te, std::string speed);
    //void closeStream();
    EventTriggerId eventTriggerId;
	static void* triggerEvent(void* pThis);
protected:
    Mpeg4FileSource(UsageEnvironment& env, std::vector<std::string> listFile, std::string ts, std::string te, std::string speed);
    virtual ~Mpeg4FileSource(void);
private:
    virtual void doGetNextFrame();
    static void deliverFrame0(void* clientData);
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
    double mDurationCheck;
    double mTimeStartTransmit;
    double mTimeLastTransmit;
    double mFPS;
    std::string mAddr;

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
    int durationStart, durationStop, frameNumber;
    int numFrameLast;
    Boolean isEndFile;
    Boolean isExit;
    pthread_t mThread;
};


#endif /* MPEG4FILESOURCE_H_ */
