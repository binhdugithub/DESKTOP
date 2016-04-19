/*
 * filehandler.h
 *
 *  Created on: Nov 28, 2012
 *      Author: hungnv
 */

#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#ifdef __cplusplus
#define BEGIN_C_DECLARE extern "C" {
#define END_C_DECLARE }
#else
#define BEGIN_C_DECLARE
#define END_C_DECLARE
#endif

#ifndef INT64_C
#define INT64_C(val) (val ## LL)
#endif

#ifndef UINT64_C
#define UINT64_C(val) (val ## ULL)
#endif

BEGIN_C_DECLARE
#include <libavformat/avformat.h>
END_C_DECLARE




class FileHandler
{
protected:
	AVFormatContext* mCtx;
	AVPacket*        mCurrentPacket;
	AVPacket         mPacket;
	unsigned char*   mSPS;
	int              mSPSLen;
	unsigned char*   mPPS;
	int              mPPSLen;
	double           mFPS;

public:
	FileHandler();
	virtual ~FileHandler();

	bool OpenFile(const char* fileName);

	unsigned char* GetSPS(void) { return mSPS; }
	int            GetSPSLen(void) { return mSPSLen; }

	unsigned char* GetPPS(void) { return mPPS; }
	int            GetPPSLen(void) { return mPPSLen; }

	AVPacket* ReadFrame(void);
	bool SeekTo(int64_t pts);
	int seekToFrame(int64_t framenumber);

	int64_t GetDuration();

	bool IsVideoStream(int stream_id);
	bool IsAudioStream(int stream_id);
	int getCodec();

	double getFPS() {return mFPS; }

};

#endif /* FILEHANDLER_H_ */
