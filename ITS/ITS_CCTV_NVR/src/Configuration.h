/*
 * Configuration.h
 *
 *  Created on: Dec 3, 2015
 *      Author: root
 */

#ifndef SRC_CONFIGURATION_H_
#define SRC_CONFIGURATION_H_
#include <iostream>
#include <string.h>
#include <yo_xml.h>


using namespace std;
using namespace elc;

class Configuration
{
public:
	static Configuration* m_instance;
	int durationFile;
	std::string pathFile;
	std::string directory;
	int portListentSoap;
	int modeNVR;
	int tryconnect;
	int minCapacity;
	std::string ipserverDB;
	int portDB;
	std::string user;
	std::string pass;
	std::string schema;
	double dataCapacity;
public:
	Configuration();
	virtual ~Configuration();
	static Configuration* GetSingleton();

	void LoadConfig();
	int getDurationConfig();
	int getPortListen();
	std::string getFilePath();
	int getModeNVR();
	int getTryConnect();
	double getCapacity();
	int getMinCapacity();
	std::string getDirectory();
	std::string getIpServerDB();
	int getPortDB();
	std::string getUser();
	std::string getPass();
	std::string getschema();

};

#endif /* SRC_CONFIGURATION_H_ */
