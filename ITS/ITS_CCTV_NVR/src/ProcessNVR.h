/*
 * ProcessNVR.h
 *
 *  Created on: 17 Jun, 2014
 *      Author: cuonglm
 *  Edit on: Dec, 2015
 *  	Author: binhngt
 */

#ifndef PROCESSNVR_H_
#define PROCESSNVR_H_

#include <string>
#include <vector>
#include "soapnvrService.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include "commondef.h"
#include"LogFile.h"
#include "DBInterface.h"
#include <sys/statvfs.h>
#include <dirent.h>
#include <sys/stat.h>
#include "ManagerRecorder.h"
#include "Configuration.h"

class ProcessNVR
{
public:
	ProcessNVR();
	~ProcessNVR();
	void start();
	static unsigned long checkFreeDiskSpace(std::string directory);
	static int getItemOfDir(std::string dir, std::vector<std::string> &files);
	static unsigned long getDateCreatFolder(std::string path);
	void AutoRecord(char *p_videostreamid, char *p_videostreamurl, int p_recordmode, int p_duration);
	void DeleteFile(vector<std::string> l_file);

protected:

	static void* doWorkDB(void* pThis);
	pthread_t mThreadDB;

	static void* monitorHDD(void* pThis);
	pthread_t mThreadMonitor;
};

#endif /* PROCESSNVR_H_ */
