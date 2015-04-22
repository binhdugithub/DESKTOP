/*
 * DataAccess.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: binhdu
 */

#include <assert.h>

#include "DataAccess.h"


namespace DAL
{ // namespace DAL


DataAccess::DataAccess(std::string pHost, std::string pUser, std::string pPassword, std::string pDatabase)
{
	mConn = NULL;

	mHost = pHost;
	mUser = pUser;
	mPassword = pPassword;
	mDatabase = pDatabase;
}

DataAccess::~DataAccess()
{
	// TODO Auto-generated destructor stub
	if(mConn)
	{
		mConn->close();
		delete mConn;
		mConn = NULL;

	}

};


sql::Connection* DataAccess::GetConnection()
{

	if(mConn != NULL)
	{
		return mConn;
	}
	else
	{
		std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "The first time to init connection" << std::endl;
	}

	try
	{
		mConn = get_driver_instance()->connect(mHost,mUser, mPassword);
		mConn->setSchema(mDatabase) ;
		mConn->setAutoCommit(false);

		std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "mConn :" << mConn << std::endl;
		return mConn;

	}
	catch (sql::SQLException &e)
	{
	  std::cout << "# ERR: SQLException in " << __FILE__;
	  std::cout << "(" << __FUNCTION__ << ") on line "  << __LINE__ << std::endl;
	  std::cout << "# ERR: " << e.what();
	  std::cout << " (MySQL error code: " << e.getErrorCode();
	  std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

	  assert(0);
	}

	return NULL;
};


sql::ResultSet* DataAccess::GetTable(std::string sql)
{
	mConnMutex.lock();
	std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << " sql: " << sql << std::endl;
	try
	{
		//send pQuery to datatabse

		sql::Statement *stmt ;
		stmt = this->GetConnection()->createStatement() ;

		sql::ResultSet *lResult = stmt->executeQuery(sql);

		delete stmt ;

		mConnMutex.unlock();
		return lResult;

	}
	catch (sql::SQLException &e)
	{
		std::cout << "ERROR: SQLException in " << __FILE__;
		std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
		std::cout << "ERROR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;

		if (e.getErrorCode() == 1047) {
			/*
			Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
			Message: Unknown command
			*/
			std::cout << "\nYour server does not seem to support Prepared Statements at all. ";
			std::cout << "Perhaps MYSQL < 4.1?" << std::endl;
		}

		mConnMutex.unlock();
		return NULL;
	}
	catch (std::runtime_error &e)
	{

		std::cout << "ERROR: runtime_error in " << __FILE__;
		std::cout << " (" << __func__ << ") on line " << __LINE__ << std::endl;
		std::cout << "ERROR: " << e.what() << std::endl;

		mConnMutex.unlock();
		return NULL;
	}

	mConnMutex.unlock();
	return NULL;
};


int DataAccess::ExcuteUpdate(std::string sql)
{
	mConnMutex.lock();
	std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << " sql: " << sql << std::endl;
	try
	{
		sql::Statement *stmt ;
		stmt = this->GetConnection()->createStatement();
		int rowEffect = stmt->executeUpdate(sql) ;
		this->GetConnection()->commit();

		delete stmt ;

		mConnMutex.unlock();
		return rowEffect;
	}
	catch (sql::SQLException &e)
	{
		std::cout << "ERROR: SQLException in " << __FILE__;
		std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
		std::cout << "ERROR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;

		if (e.getErrorCode() == 1047)
		{
			/*
			Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
			Message: Unknown command
			*/
			std::cout << "\nYour server does not seem to support Prepared Statements at all. ";
			std::cout << "Perhaps MYSQL < 4.1?" << std::endl;
		}

		mConnMutex.unlock();
		return -1;
	}
	catch (std::runtime_error &e)
	{

		std::cout << "ERROR: runtime_error in " << __FILE__;
		std::cout << " (" << __func__ << ") on line " << __LINE__ << std::endl;
		std::cout << "ERROR: " << e.what() << std::endl;

		mConnMutex.unlock();
		return -1;
	}


	mConnMutex.unlock();
	return -1;

};

sql::ResultSet* DataAccess::ExcuteInsertAndQuery(std::string sqlInsert, std::string sqlQuery)
{
	mConnMutex.lock();
	std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << " sqlUpdate: " << sqlInsert << std::endl;
	std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << " sqlQuery: " << sqlQuery << std::endl;

	sql::Statement *stmt;
	stmt = this->GetConnection()->createStatement();
	try
	{
		stmt->executeUpdate(sqlInsert);
		sql::ResultSet *data = stmt->executeQuery(sqlQuery);

		if(data)
		{
			this->GetConnection()->commit();
			delete stmt;

			mConnMutex.unlock();
			return data;
		}
		else
		{
			delete stmt;
			mConnMutex.unlock();
			return NULL;
		}
	}
	catch (sql::SQLException &e)
	{

		std::cout << "ERROR: SQLException in " << __FILE__;
		std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
		std::cout << "ERROR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;

		if (e.getErrorCode() == 1047)
		{
			/*
			Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
			Message: Unknown command
			*/
			std::cout << "\nYour server does not seem to support Prepared Statements at all. ";
			std::cout << "Perhaps MYSQL < 4.1?" << std::endl;
		}

		delete stmt;
		mConnMutex.unlock();
		return NULL;
	}
	catch (std::runtime_error &e)
	{

		std::cout << "ERROR: runtime_error in " << __FILE__;
		std::cout << " (" << __func__ << ") on line " << __LINE__ << std::endl;
		std::cout << "ERROR: " << e.what() << std::endl;

		delete stmt;
		mConnMutex.unlock();
		return NULL;
	}


	delete stmt;
	mConnMutex.unlock();
	return NULL;
}


}//end namespace DAL
