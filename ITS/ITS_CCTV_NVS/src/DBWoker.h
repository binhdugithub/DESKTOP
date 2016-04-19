/*
 * WokerDB.h
 *
 *  Created on: 17 Jun, 2014
 *      Author: cuonglm
 */

#ifndef WOKERDB_H_
#define WOKERDB_H_

#include <string>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

class DBWoker
{
public:
	DBWoker();
	~DBWoker();

	void insertData(std::string query);
	std::string getData(std::string query);
	void removeData();
	static DBWoker* getSingleton();
	void init();

private:
	static DBWoker* dbWoker;
	sql::Driver* mDriver;
	sql::Connection* mCon;
	sql::Statement* mStmt;
	sql::ResultSet* mRes;
	int isReady;

};



#endif /* WOKERDB_H_ */
