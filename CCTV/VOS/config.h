/*
 * config.h
 *
 *  Created on: Aug 27, 2014
 *      Author: xyz
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <yo_xml.h>
#include "mycommon.h"

class Config
{
public:
	static string dbName;
	static string dbHost;
	static string dbPwd;
	static string dbUser;
	static int svrport;
	static bool isDebug;
	static bool isRetry;
	static bool isMulticast;
	static string multicastIp;
	static int multicastPort;
	static unsigned short rtpPortNum;
	static unsigned short rtcpPortNum;
	static unsigned char ttl;
	static string streamingDestinationIp;
	static int keepOverlayInforActivated; // time (in second) to keep overlay information activated if received no infor from multicast ...
	static bool readConfig(const string& fileName);
};

#endif /* CONFIG_H_ */