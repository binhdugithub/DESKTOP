/*
 * commondef.cpp
 *
 *  Created on: 8 Jul, 2014
 *      Author: cuonglm
 */
#include <string>
#include <yo_xml.h>
#include "commondef.h"
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>


using namespace elc;

std::string textLog;
//Boolean isExit = false;


//rtsp server
void setPortRTSPServer(int port) {
	portListentRTSP = port;
}

int getPortRTSPServer() {
	return portListentRTSP;
}

void setPassRTSPServer(std::string pass) {
	passRTSP = pass;

}

std::string getPassRTSPServer() {
	return passRTSP;
}

void setUserRTSPServer(std::string user) {
	userRTSP = user;
}

std::string getUserRTSPServer()
{
	return userRTSP;
}

//storage
void setStoragePath(std::string path) {
	storagePath = path;
}
std::string getStoragePath() {
	return storagePath;
}


//DB
std::string getIpServerDB()
{
	return ipserverDB;
}
int getPortDB()
{
	return portDB;
}
std::string getUser()
{
	return user;
}
std::string getPass()
{
	return pass;
}

std::string getschema()
{
	return schema;
}


void initConfig()
{
	// open xml file
	ElcXmlFile xml("/opt/nvs/etc/confignvr.xml", ElcXmlFile::READ);
	ElcXmlFileNode* root = xml.getRoot();
	ElcXmlFileNode* cctv = xml.getNode(root, "cctv");
	ElcXmlFileNode* nvr = xml.getNode(cctv, "nvrstreaming");
	std::string value;

	// load rtsp config
	ElcXmlFileNode* rtsp = xml.getNode(nvr, "rtsp");
	value = rtsp->getAttribute("server_port");
	setPortRTSPServer(atoi(value.c_str()));
	value = rtsp->getAttribute("user");
	setUserRTSPServer(value);
	value = rtsp->getAttribute("pass");
	setPassRTSPServer(value);
	delete rtsp;

	// load storage config
	ElcXmlFileNode* storage = xml.getNode(nvr, "storage");
	value  = storage->getAttribute("storage_path");
	setStoragePath(value);
	delete storage;

	//load database config
	ElcXmlFileNode* database = xml.getNode(nvr, "database");
	value  = database->getAttribute("ipserver");
	ipserverDB = value;
	value = database->getAttribute("port");
	portDB = atoi(value.c_str());
	value = database->getAttribute("user");
	user = value;
	value = database->getAttribute("password");
	pass = value;
	value = database->getAttribute("schema");
	schema = value;
	delete database;

	delete nvr;
	delete cctv;
	delete root;
}

std::string int2string(int number) {
	std::ostringstream ssb;
	ssb << number;
	return ssb.str();
}

std::string getAddrPoint(void* mThis) {
	std::size_t address = reinterpret_cast<std::size_t>(mThis);
	return int2string(address);
}



std::vector<std::string> split(char* s, const char* delim) {
    std::vector<std::string> elems;
    char* pch = strtok (s,delim);
      while (pch != NULL)
      {
    	elems.push_back(std::string(pch));
        pch = strtok (NULL, delim);
      }
    return elems;
}

int getdir (std::string dir, vector<std::string> &files)
{
	DIR *dp;
	struct dirent *dirp;
	if((dp = opendir(dir.c_str())) == NULL) {
		LOG_ERROR("Error "<<int2string(errno)<<" opening "<<dir);
		return errno;
	}

	while ((dirp = readdir(dp)) != NULL) {
		if(dirp->d_name[0] != '.' && dirp->d_name[0] != '..' && dirp->d_name[strlen(dirp->d_name)-1] != '~')
			files.push_back(std::string(dirp->d_name));
	}
	closedir(dp);
	return 0;
}

