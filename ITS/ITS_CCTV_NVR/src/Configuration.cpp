/*
 * Configuration.cpp
 *
 *  Created on: Dec 3, 2015
 *      Author: root
 */

#include "Configuration.h"



Configuration* Configuration::m_instance = NULL;
Configuration::Configuration()
{
	// TODO Auto-generated constructor stub
	LoadConfig();

}

Configuration::~Configuration()
{
	// TODO Auto-generated destructor stub
}

Configuration* Configuration::GetSingleton()
{
	if(m_instance == NULL)
	{
		m_instance = new Configuration();
	}

	return m_instance;
}

int Configuration::getDurationConfig()
{
	return durationFile;
}

int Configuration::getPortListen()
{
	return portListentSoap;
}

std::string Configuration::getFilePath()
{
	return pathFile;
}


int Configuration::getModeNVR()
{
	return modeNVR;
}

int Configuration::getTryConnect()
{
	return tryconnect;
}

double Configuration::getCapacity()
{
	return dataCapacity;
}

std::string Configuration::getDirectory()
{
	return directory;
}

int Configuration::getMinCapacity()
{
	return minCapacity;
}

std::string Configuration::getIpServerDB()
{
	return ipserverDB;
}

int Configuration::getPortDB()
{
	return portDB;
}
std::string Configuration::getUser()
{
	return user;
}
std::string Configuration::getPass()
{
	return pass;
}

std::string Configuration::getschema()
{
	return schema;
}


void Configuration::LoadConfig()
{
	// open xml file
	ElcXmlFile xml("/opt/nvr/etc/confignvr.xml", ElcXmlFile::READ);
	ElcXmlFileNode* root = xml.getRoot();
	ElcXmlFileNode* cctv = xml.getNode(root, "cctv");
	ElcXmlFileNode* nvr = xml.getNode(cctv, "nvr");
	std::string value;

	// load general config
	ElcXmlFileNode* general = xml.getNode(nvr, "general");
	value = general->getAttribute("mode");
	modeNVR = atoi(value.c_str());

	value = general->getAttribute("tryconnect");
	tryconnect = atoi(value.c_str());
	delete general;

	// load network config
	ElcXmlFileNode* network = xml.getNode(nvr, "network");
	value  = network->getAttribute("soap_port");
	portListentSoap = atoi(value.c_str());
	delete network;

    //load storage config
	ElcXmlFileNode* storage = xml.getNode(nvr, "storage");
	value  = storage->getAttribute("duration");
	durationFile = atoi(value.c_str());

	value = storage->getAttribute("video_path");
	pathFile = value;

	value = storage->getAttribute("directory_path");
	directory = value;

	value = storage->getAttribute("min_capacity");
	minCapacity = atoi(value.c_str());

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


