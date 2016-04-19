/*
 * DBWoker.cpp
 *
 *  Created on: 17 Jun, 2014
 *      Author: cuonglm
 */
#include "DBWoker.h"
#include "LogFile.h"
#include "commondef.h"

DBWoker* DBWoker::dbWoker = 0;

DBWoker::DBWoker()
{
	mDriver = get_driver_instance();
	isReady = false;
	mCon = NULL;
	mStmt = NULL;
	mRes = NULL;
	init();
}

DBWoker::~DBWoker()
{
	if(!mCon){
		if(!mCon->isClosed()) {
			mCon->close();
			mCon = NULL;
		}
	}
}

void DBWoker::init()
{
	try	{
		std::string sqlString = "tcp://" + getIpServerDB() + ":" + int2string(getPortDB());
		const char* user = getUser().c_str();
		const char* pass = getPass().c_str();
		const char* schema = getschema().c_str();

		mCon = mDriver->connect(sqlString.c_str(), user, pass);
		if(mCon == NULL) {
			LOG_ERROR("connect to DB error");
			isReady = false;
			return;
		}
		mCon->setSchema(schema);
		mStmt = mCon->createStatement();

		isReady = true;
	}

	catch(sql::SQLException &e)	{
		LOG_ERROR("# ERR: "<<std::string(e.what()));
		LOG_ERROR("MySQL error code:"<<int2string(e.getErrorCode()));
		if(mCon != NULL) {
			if(!mCon->isClosed())
				mCon->close();
			mCon = NULL;
		}
		isReady = false;
	}
}

DBWoker* DBWoker::getSingleton()
{
	if(!dbWoker)  {
		dbWoker = new DBWoker();
	}
	return dbWoker;
}

void DBWoker::insertData(std::string query )
{
	try  {
		if(!isReady)  {
			init();
		}
		if(!isReady)  {
			LOG_ERROR("don't ready to insert data");
			return;
		}
		mStmt = mCon->createStatement();
		std::string sqlQuery = query;
		cout<<sqlQuery<<endl;
		mStmt->execute(sqlQuery.c_str());
		delete mStmt;
		mStmt = NULL;
	}
	catch(sql::SQLException &e)	{
		LOG_ERROR("# ERR in init :  "<<std::string(e.what()));
		LOG_ERROR("MySQL error code:"<<int2string(e.getErrorCode()));
		isReady = false;
	}
}

void DBWoker::removeData()
{

}

std::string DBWoker::getData(std::string query){
	try	{
		if(!isReady) {
			LOG_INFO("call Init in getData");
			init();
		}
		if(!isReady) {
			LOG_ERROR("don't ready after init data");
			return NULL;
		}
		std::string sqlQuery = query;
		LOG_INFO(sqlQuery);
		mStmt = mCon->createStatement();
		mRes = mStmt->executeQuery(sqlQuery.c_str());
		if(mRes == NULL) {
			LOG_INFO("mRes = NULL, return """);
			return "";
		}
		if(!mRes->next()) {
			LOG_INFO("mRes->next() = NULL, return """);
			return "";
		}
		std::string result = "";
		result = mRes->getString("id");
		delete mRes;
		delete mStmt;
		return result;
	}
	catch(sql::SQLException &e)	{
		LOG_ERROR("# ERR in init :  "<<std::string(e.what()));
		LOG_ERROR("MySQL error code:"<<int2string(e.getErrorCode()));
		isReady = false;
		return "";
	}
}


