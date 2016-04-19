//============================================================================
// Name        : ITS_CCTV_NVR_RECORDER.cpp
// Author      : cuonglm
// Version     :
// Copyright   : Your copyright notice
//============================================================================


#include <iostream>
#include "ProcessNVR.h"
#include <pthread.h>
#include <unistd.h>
#include "commondef.h"
#include "LogFile.h"

#ifdef __cplusplus
extern "C"
{
#endif
#include <libavformat/avformat.h>
#include <libavutil/time.h>
#ifdef __cplusplus
}
#endif

using namespace std;


int main()
{
	//init for record camera
	avformat_network_init();
	av_register_all();

	initMutexCommond();
	InitLogger(true);

    std::cout<<"********************************************Start ITS_CCTV_NVR***********************************************"<<std::endl;
	LOG_INFO("********************************************Start ITS_CCTV_NVR***********************************************");
	ProcessNVR* processNVR = new ProcessNVR();
	processNVR->start();
	//DBWoker::getSingleton()->insertData("AxisPQ164", "AxisPQ164_2014_7_11_17_0_0");
	LOG_INFO("********************************************Exit ITS_CCTV_NVR************************************************");
	delete processNVR;
	processNVR = NULL;
	destroyMutexCommond();
	return 0;
}






