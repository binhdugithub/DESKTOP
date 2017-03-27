#ifndef LOG_H
#define LOG_H

// Qt includes
#include <QDebug>
#include <QThread>

/// DEFINE FOR LOG
enum LOGLEVEL{Off, Falta, Error, Warning, Info, Debug1, Debug2, Debug3, Trace, All};
extern LOGLEVEL logLvl;

#if(1)
#define gLog(msg,logLvl){\
	if(logLvl >= logLvl){\
	QString str = "";\
	switch(logLvl){\
	case Falta:\
	str.append("[Fal]");\
	break;\
	case Error:\
	str.append("[Err]");\
	break;\
	case Warning:\
	str.append("[War]");\
	break;\
	case Info:\
	str.append("[Inf]");\
	break;\
	case Debug1:\
	str.append("[De1]");\
	break;\
	case Debug2:\
	str.append("[De2]");\
	break;\
	case Debug3:\
	str.append("[De3]");\
	break;\
	default:\
	str.append("[Def]");\
	break;\
	}\
	qDebug() << QThread::currentThreadId() << __TIME__\
	<< __FILE__ << __LINE__ << __FUNCTION__\
	<< str << msg;\
	}\
	}
#else
#define gLog(msg, _logLvl){\
	std::stringstream os;\
	os << msg;\
	if(_logLvl <= logLvl)\
	switch(_logLvl){\
	case Off:\
	break;\
	case Falta:\
	LOG4CXX_FATAL(logger, "(" << __FUNCTION__ << ") - " << os.str());\
	break;\
	case Error:\
	LOG4CXX_ERROR(logger, "(" << __FUNCTION__ << ") - " << os.str());\
	break;\
	case Warning:\
	LOG4CXX_WARN(logger, "(" << __FUNCTION__ << ") - " << os.str());\
	break;\
	case Info:\
	LOG4CXX_INFO(logger, "(" << __FUNCTION__ << ") - " << os.str());\
	break;\
	case Debug1:\
	LOG4CXX_DEBUG(logger, "(" << __FUNCTION__ << ") - " << os.str());\
	break;\
	case Debug2:\
	LOG4CXX_DEBUG(logger, "(" << __FUNCTION__ << ") - " << os.str());\
	break;\
	case Debug3:\
	LOG4CXX_DEBUG(logger, "(" << __FUNCTION__ << ") - " << os.str());\
	break;\
	case Trace:\
	LOG4CXX_TRACE(logger, "(" << __FUNCTION__ << ") - " << os.str());\
	break;\
	default:\
	break;\
	}\
	}
#endif
#endif // LOG_H

