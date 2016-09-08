/*
 * config.cpp
 *
 *  Created on: Aug 27, 2014
 *      Author: xyz
 */

#include "config.h"

using namespace elc;

bool Config::isDebug = false;
bool Config::isRetry = false;


std::string Config::m_dbhost = "";
std::string Config::m_dbuser = "";
std::string Config::m_dbpass = "";
std::string Config::m_dbname = "";

std::string Config::m_restport = "";
std::string Config::m_restroot = "";

int Config::svrport = 0;
int Config::keepOverlayInforActivated = 60;
int Config::blackheight = 0;
int Config::capacity = 100;


int Config::m_gop = 0;
int Config::m_bitrate = 0;

bool Config::readConfig(const string& fileName)
{
	ElcXmlFile xml(fileName, ElcXmlFile::READ);
	ElcXmlFileNode* root = xml.getRoot();
	ElcXmlFileNode* cctv = xml.getNode(root, "cctv");
	ElcXmlFileNode* vos = xml.getNode(cctv, "vos");

	ElcXmlFileNode* general = xml.getNode(vos, "general");
	ElcXmlFileNode* network = xml.getNode(vos, "network");
	ElcXmlFileNode* database = xml.getNode(vos, "database");
	ElcXmlFileNode* videoquality = xml.getNode(vos, "videoquality");
	ElcXmlFileNode* overlay = xml.getNode(vos, "overlay");

	if(!root || !cctv || !vos || !database || !network || !general || !overlay)
		return false;
	m_dbhost = database->getAttribute("host");
	m_dbname = database->getAttribute("dbname");
	m_dbuser = database->getAttribute("user");
	m_dbpass = database->getAttribute("pass");

	m_restport = network->getAttribute("rest_port");
	m_restroot = network->getAttribute("rest_root");
	svrport = elc::toInt(network->getAttribute("soap_port"));

	isDebug = general->getAttribute("debug") == "true" ? true : false;
	isRetry = general->getAttribute("isretry") == "true" ? true : false;

	keepOverlayInforActivated = elc::toInt(overlay->getAttribute("keepoverlayinforactivated"));
	blackheight = elc::toInt(overlay->getAttribute("blackheight"));
	capacity = elc::toInt(overlay->getAttribute("capacity"));

	//videoquality
	m_gop = elc::toInt(videoquality->getAttribute("gop"));
	m_bitrate = elc::toInt(videoquality->getAttribute("bitrate"));

	return true;
}
