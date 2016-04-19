/*
 * Configuration.h
 *
 *  Created on: Dec 12, 2015
 *      Author: root
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <iostream>
#include <string>
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"


#define FILE_CONFIG "/opt/FunnyStories/config.xml"

using namespace std;
class Configuration
{
public:
	virtual ~Configuration();
private:
	Configuration();
	static Configuration *SingleTon;

public:
	static Configuration* GetSingleTon();
	void LoadConfig();

public:
	std::string sv_ip;
	std::string sv_port;
	std::string sv_root;

	std::string db_host;
	std::string db_user;
	std::string db_pass;
	std::string db_database;
};



#endif /* CONFIGURATION_H_ */
