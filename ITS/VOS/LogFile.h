
#include <log4cplus/logger.h>  
#include <log4cplus/loggingmacros.h>  

using namespace log4cplus;  
using namespace log4cplus::helpers;  

// global object  
extern Logger logger;

// define some macros for simplicity  
#define LOG_TRACE(logEvent)         LOG4CPLUS_TRACE(logger, logEvent)  
#define LOG_DEBUG(logEvent)         LOG4CPLUS_DEBUG(logger, logEvent)  
#define LOG_INFO(logEvent)          LOG4CPLUS_INFO(logger, logEvent)  
#define LOG_WARN(logEvent)          LOG4CPLUS_WARN(logger, logEvent)  
#define LOG_ERROR(logEvent)         LOG4CPLUS_ERROR(logger, logEvent)  
#define LOG_FATAL(logEvent)         LOG4CPLUS_FATAL(logger, logEvent)  

//	Logger logger;
void InitLogger(bool daemonized);



/*
#include <iostream>
#include <log4cplus/helpers/loglog.h>

using namespace std;
using namespace log4cplus::helpers;

void printMsgs() {
    cout << "Entering printMsgs()..." << endl;
    LogLog::getLogLog()->debug(LOG4CPLUS_TEXT("This is a Debug statement..."));
    LogLog::getLogLog()->warn(LOG4CPLUS_TEXT("This is a Warning..."));
    LogLog::getLogLog()->error(LOG4CPLUS_TEXT("This is a Error..."));
    cout << "Exiting printMsgs()..." << endl << endl;
}

void testLog()
{
    log4cplus::initialize ();
    printMsgs();

    cout << "Turning on debug..." << endl;
    LogLog::getLogLog()->setInternalDebugging(true);
    printMsgs();

    cout << "Turning on quiet mode..." << endl;
    LogLog::getLogLog()->setQuietMode(true);
    printMsgs();
}

*/

