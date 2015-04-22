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
#include <cppconn/resultset.h>
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "mysql_connection.h"
#include <mutex>


#define HOST "127.0.0.1"
#define USER "root"
#define PASS "root"
#define DATABASE "Bat2Chu"

namespace DAL
{

class DataAccess
{

protected:
	sql::Connection *mConn;
	std::recursive_mutex mConnMutex;
	std::string mHost;
	std::string mUser;
	std::string mPassword;
	std::string mDatabase;

public:
	DataAccess(std::string pHost = HOST, std::string pUser=USER, std::string pPassword = PASS , std::string pDatabase = DATABASE);
	virtual ~DataAccess();

public:
	sql::Connection* GetConnection();
	sql::ResultSet* GetTable(std::string);
	int ExcuteUpdate(std::string);
	sql::ResultSet* ExcuteInsertAndQuery(std::string, std::string);

};

} /* namespace DAL */

#endif /* DATAACCESS_H_ */
