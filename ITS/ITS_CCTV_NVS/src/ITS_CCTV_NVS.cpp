//============================================================================
// Name        : ITS_CCTV_NVR_STREAMING.cpp
// Author      : cuonglm
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "elcrtspserver.h"
#include "LogFile.h"
#include "commondef.h"

#ifdef __cplusplus
extern "C"
{
#endif
#include <libavformat/avformat.h>
#ifdef __cplusplus
}
#endif /*__cplusplus*/

using namespace std;

 UsageEnvironment* env;
 TaskScheduler* scheduler;

int main()
{
    //init lib
	initConfig();
	InitLogger(true);
    av_register_all();
    OutPacketBuffer::maxSize = 500000;

    std::cout<<"===================== START NVR_STREAMING ====================="<<std::endl;
	LOG_INFO("===================== START NVR_STREAMING =====================");
    scheduler = BasicTaskScheduler::createNew(2000);
	env = BasicUsageEnvironment::createNew(*scheduler);
	UserAuthenticationDatabase* authDB = NULL;

	std::string user = getUserRTSPServer();
	std::string pass = getPassRTSPServer();
	int portRTSP = getPortRTSPServer();
	if(user != "" && pass != "")
	{
		authDB = new UserAuthenticationDatabase();
		authDB->addUserRecord(user.c_str(), pass.c_str());
		std::cout <<"User:" << user.c_str() << " Pass:" << pass.c_str() << std::endl;
		LOG_INFO("User:" << user.c_str() << " Pass:" << pass.c_str());
	}

	ELCRTSPServer* myRTSP = ELCRTSPServer::createNew(*env,portRTSP, authDB);
	if(myRTSP == NULL)
	{
		std::cout<<"error, exit"<<std::endl;
		LOG_ERROR("init RTSP Server error, exit program");
		exit(1);
	}


	env->taskScheduler().doEventLoop();
	LOG_INFO("===================== EXIT NVR_STREAMING =====================");
	return 0;
}
