/*
 * filesource.h
 *
 *  Created on: 7 Aug, 2014
 *      Author: cuonglm
 */

#ifndef FILESOURCE_H_
#define FILESOURCE_H_

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
class FileSource
{

public:
	FileSource();
	~FileSource();
    static unsigned get_microsecond();
    static int getPosStart();
    static int getPosStop();
    static int getSpeed();
protected:

    std::vector<FileHandler*> mFileHandlerList;
    std::vector<FileHandler*>::iterator mFileHandlerItorator;
    std::vector<std::string> mListFile;
    std::vector<std::string>::iterator mListFileItorator;
    std::vector<std::string> splitvt;
    AVPacket* mCurrentPacket;
    FileHandler* mFileReader;
    unsigned mTimeLastReceive;
    unsigned mTimeCurrentReceive;
    unsigned mTimeStartReceive;
    unsigned mTimeStartTransmit;
    unsigned mTimeLastTransmit;
    double mFPS;

    std::queue<AVPacket*> dataQueue;
    timeval currentTime;
    std::string filePath;
    std::string timeStart, timeStop, mSpeed;
    double speed;
    double timeCheck;
    int durationStart, durationStop, frameNumber;
    Boolean isEndFile;
    Boolean isExit;
};



#endif /* FILESOURCE_H_ */
