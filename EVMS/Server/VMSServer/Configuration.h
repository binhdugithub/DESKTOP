#pragma once

#include <ostream>
#include <string>
#include "tinystr.h"
#include "tinyxml.h"


#define FILE_CONFIG "config.txt"

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

	std::string st_screenshot;
	std::string st_http_screenshot;
	std::string st_text;

	std::string st_imageresource;
};

