/*
 * DataAccess.h
 *
 *  Created on: Jul 18, 2014
 *      Author: binhdu
 */

#ifndef DATAACCESS_H_
#define DATAACCESS_H_

#include <stdlib.h>
#include <iostream>
#include <mutex>

#include <cppconn/resultset.h>
#include "mysql_driver.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

namespace DAL
{

class DataAccess
{

protected:
	sql::Connection *mConn;
	//std::recursive_mutex mConnMutex;
	std::string mHost;
	std::string mUser;
	std::string mPassword;
	std::string mDatabase;

	std::recursive_mutex m_accessmutex;

public:
	DataAccess();
	//DataAccess(std::string pHost = HOST, std::string pUser=USER, std::string pPassword = PASS , std::string pDatabase = DATABASE);
	virtual ~DataAccess();

public:
	sql::Connection* GetConnection();
	sql::ResultSet* QueryData(std::string);
	int QuerySystem(std::string);
	int QueryUpdate(std::string);
};

} /* namespace DAL */

#endif /* DATAACCESS_H_ */
