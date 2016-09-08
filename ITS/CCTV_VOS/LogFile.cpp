#include <log4cplus/logger.h>  
#include <log4cplus/consoleappender.h>  
#include <log4cplus/fileappender.h>  
#include <log4cplus/layout.h>  
#include <log4cplus/configurator.h>  

#include "LogFile.h"
using namespace std;
Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("logmain"));

#include <iostream>

void InitLogger(bool daemonized)
{  
	log4cplus::initialize();
//	cout << "After initialize()..." << endl;
	if (daemonized)
		PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("/opt/vos/etc/configlog.txt"));
//	else
//		PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("./configLog.txt"));
//	cout << "After doConfigure..." << endl;
//	LOG_INFO("---------- START EVENT PROCESSING ----------");
//	LOG_ERROR("---------- START EVENT PROCESSING ----------");
//	cout << "Return InitLogger!!!" << endl;
}
