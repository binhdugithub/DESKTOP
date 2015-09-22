#include "stdafx.h"
#include "Configuration.h"


Configuration* Configuration::SingleTon = NULL;

Configuration::Configuration()
{

}


Configuration::~Configuration()
{

}

Configuration* Configuration::GetSingleTon()
{
	if (SingleTon == NULL)
	{
		SingleTon = new Configuration();
		SingleTon->LoadConfig();
	}
	
	return SingleTon;
}


void Configuration::LoadConfig()
{
	//TiXmlDocument doc(FILE_CONFIG);
	TiXmlDocument doc("config.xml");

	if (!doc.LoadFile())
	{
		doc.Clear();
		return;
	}

	TiXmlElement *eRoot = doc.RootElement(); 
	TiXmlElement *eSetting = eRoot->FirstChildElement("setting");

	TiXmlElement *eDatabase = eSetting->FirstChildElement("database");
	TiXmlElement *eNetwork = eSetting->FirstChildElement("network");
	TiXmlElement *eStorage = eSetting->FirstChildElement("storage");

	db_host = std::string(eDatabase->Attribute("database_host"));
	db_database = std::string(eDatabase->Attribute("database_name"));
	db_user = std::string(eDatabase->Attribute("database_user"));
	db_pass = std::string(eDatabase->Attribute("database_pass"));
	
	sv_ip = std::string(eNetwork->Attribute("server_ip"));
	sv_port = std::string(eNetwork->Attribute("server_port"));
	sv_root = std::string(eNetwork->Attribute("server_root"));

	st_screenshot = std::string(eStorage->Attribute("screenshot"));
	st_http_screenshot = std::string(eStorage->Attribute("http_screenshot"));
	st_text = std::string(eStorage->Attribute("text"));
	st_imageresource = std::string(eStorage->Attribute("imageresource"));
	doc.Clear();
	return;
	
}