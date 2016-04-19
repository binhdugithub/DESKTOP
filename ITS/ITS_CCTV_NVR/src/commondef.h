/*
 * commondef.h
 *
 *  Created on: 7 Jul, 2014
 *      Author: cuonglm
 */

#ifndef COMMONDEF_H_
#define COMMONDEF_H_

#include <queue>
#include <deque>
#include <pthread.h>
#include <string>
#include <fstream>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/statvfs.h>
#include <time.h>
#include <signal.h>
#include <sys/stat.h>
#include <iostream>
#include "LogFile.h"

using namespace std;

#define TIMEOUT_RTSP   15   //second
#define NUMBER_OF_FILE_2_DELETE 10

extern bool isExit;
extern std::string textLog;
static std::deque<std::string> dbQueue;
static pthread_mutex_t myMutex;

//for config


enum CAMSTATUS
{
	STOPRECORD 	= 0,
	RECORDING  	= 1,
	RETRYRECORD = 2,
};

std::string GetDeltaTime(struct tm ts);
std::string GetSizeOfRecoredFile(std::string p_path);

void insertFirstDBQueue(std::string query);
void pushDBQueue(std::string query);
std::string getDBQueue();
int getSizeDBQueue();

int getSizeQueue();


void initMutexCommond();
void destroyMutexCommond();

#endif /* COMMONDEF_H_ */
