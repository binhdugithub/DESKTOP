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
bool Config::isMulticast = false;
string Config::dbHost = "";
string Config::dbName = "";
string Config::dbUser = "";
string Config::dbPwd = "";
int Config::svrport = 0;
string Config::multicastIp = "";
int Config::multicastPort = 0;
int Config::keepOverlayInforActivated = 60;
unsigned short Config::rtpPortNum = 18888;
unsigned short Config::rtcpPortNum = rtpPortNum+1;
unsigned char Config::ttl = 255;
string Config::streamingDestinationIp = "default";

bool Config::readConfig(const string& fileName)
{
	ElcXmlFile xml(fileName, ElcXmlFile::READ);
	ElcXmlFileNode* root = xml.getRoot();
	ElcXmlFileNode* cctv = xml.getNode(root, "cctv");
	ElcXmlFileNode* vos = xml.getNode(cctv, "vos");
	ElcXmlFileNode* database = xml.getNode(vos, "database");
	ElcXmlFileNode* general = xml.getNode(vos, "general");
	ElcXmlFileNode* network = xml.getNode(vos, "network");
	ElcXmlFileNode* streaming = xml.getNode(vos, "streaming");
	ElcXmlFileNode* overlay = xml.getNode(vos, "overlay");
	if(!root || !cctv || !vos || !database || !network || !general || !overlay || !streaming)
		return false;
	dbHost = database->getAttribute("host");
	dbName = database->getAttribute("dbname");
	dbUser = database->getAttribute("user");
	dbPwd = database->getAttribute("pass");
	svrport = elc::toInt(network->getAttribute("svrport"));
	multicastIp = network->getAttribute("multicastip");
	multicastPort = elc::toInt(network->getAttribute("multicastport"));
	isDebug = general->getAttribute("debug") == "true" ? true : false;
	isRetry = general->getAttribute("isretry") == "true" ? true : false;
	isMulticast = general->getAttribute("ismulticast") == "true" ? true : false;
	keepOverlayInforActivated = elc::toInt(overlay->getAttribute("keepoverlayinforactivated"));
	rtpPortNum = (unsigned short)elc::toInt(streaming->getAttribute("rtpport"));
	rtcpPortNum = (unsigned short)elc::toInt(streaming->getAttribute("rtcpport"));
	streamingDestinationIp = streaming->getAttribute("destinationip");
	ttl = (unsigned char)toInt(streaming->getAttribute("ttl"));
	LOG_INFO("Config::readconfig() dbHost="<<dbHost<<" dbName="<<dbName<<" dbUser="<<dbUser<<" dbPwd="<<dbPwd<<" svrport="<<svrport<<" multicastIp="<<multicastIp<<" multicastPort="<<multicastPort<<
			" streamingdestianionip="<<streamingDestinationIp<<" rtpport="<<rtpPortNum<<" rtcpport="<<rtcpPortNum<<" ttl="<<ttl<<" keepOverlayInforActivated="<<keepOverlayInforActivated<<" isMulticast="<<isMulticast);
	if(dbHost == "" || dbName == "" || svrport <= 0 || multicastIp == "" || multicastPort <=0 || keepOverlayInforActivated <= 0 || rtpPortNum <= 0 || rtcpPortNum <= 0 || ttl < 0)
		return false;
	return true;
}
