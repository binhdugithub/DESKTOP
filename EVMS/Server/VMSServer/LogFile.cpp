
#include "stdafx.h"

#include <log4cplus/logger.h>  
#include <log4cplus/consoleappender.h>  
#include <log4cplus/fileappender.h>  
#include <log4cplus/layout.h>  
#include <log4cplus/configurator.h>  

#include "LogFile.h"  

log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("logmain"));

void InitLogger(bool daemonized)  
{  
	initialize();
	if (daemonized)  
		PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("configLog.txt"));  
/*	else  
		PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("configLog.txt"));*/  
} 