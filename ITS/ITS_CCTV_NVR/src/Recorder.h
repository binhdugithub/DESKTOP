/*
 * Recorder.h
 *
 *  Created on: Dec 2, 2015
 *      Author: root
 */

#ifndef SRC_RECORDER_H_
#define SRC_RECORDER_H_

#include <string.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <time.h>
#include <signal.h>
#include <sys/stat.h>
#include "commondef.h"
#include <sys/statvfs.h>
#include "LogFile.h"
#include "DBInterface.h"
#include <fstream>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include "Configuration.h"



#ifdef __cplusplus
extern "C"
{
#endif
#include <libavformat/avformat.h>
#include <libavutil/time.h>
#ifdef __cplusplus
}
#endif


#include "Camera.h"
#include "LogFile.h"
#include "commondef.h"


class Recorder
{
public:

	AVFormatContext* 	m_AVInput;
	AVFormatContext*	m_AVOutput;
	AVStream* 			m_InputStream;
	AVStream* 			m_OutputStream;

	struct tm 			m_TimeStart;
	std::string 		m_StartTimeRecording;
	std::string 		m_LengTimeFile;
	std::string			m_SizeFile;
	std::string 		m_RecordFile;
	std::string 		m_RecordPath;

	std::thread* 		m_HMainThread;
	bool volatile 		m_IsRunningFlag;
	int volatile  		m_Status;

	Camera 				*m_Camera;

public:
	Recorder();
	Recorder(std::string, std::string, std::string, int, int, int);
	virtual ~Recorder();

	void StartRecord();
	static void MainThread(void *p_param);
	bool InitInput();
	bool InitOutput(std::string p_file, AVStream*);
	void CloseCamera();
	void CreatFolderFile();
	void GetFileInfo();


protected:
	void CloseFile();

};

#endif /* SRC_RECORDER_H_ */
