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

	//database
	static std::string m_dbhost;
	static std::string m_dbuser;
	static std::string m_dbpass;
	static std::string m_dbname;

	static int svrport;
	static bool isDebug;
	static bool isRetry;


	//binhngt
	//restful
	static std::string m_restport;
	static std::string m_restroot;

	//video encode
	static int m_bitrate;
	static int m_gop;


	//overlay
	static int blackheight;
	static int capacity;
	static int keepOverlayInforActivated; // time (in second) to keep overlay information activated if received no infor from multicast ...
	static bool readConfig(const string& fileName);
};

#endif /* CONFIG_H_ */
