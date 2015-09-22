// VMSServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LogFile.h"
#include "Configuration.h"

#include "RestConnection.h"
#include "DataAccess.h"

int main()
{

	//cout << endl;
	//cout << "Let's have MySQL count from 10 to 1..." << endl;



	//try {
	//	sql::Driver *driver;
	//	sql::Connection *con;
	//	sql::Statement *stmt;
	//	sql::ResultSet *res;
	//	sql::PreparedStatement *pstmt;

	//	/* Create a connection */
	//	driver = get_driver_instance();
	//	con = driver->connect("tcp://192.168.6.150:3306", "its", "its123");
	//	/* Connect to the MySQL test database */
	//	con->setSchema("vmssystem");

	//	std::string abc("SELECT * FROM vms_user WHERE username= ?");
	//	pstmt = con->prepareStatement(abc);
	//	pstmt->setString(1,std::string("binhngt"));
	//	res = pstmt->executeQuery();

	//	/* Fetch in reverse = descending order! */
	//	res->afterLast();
	//	while (res->previous())
	//	{
	//		//std::string username = std::string(res->getString("username").c_str());
	//		try
	//		{
	//			//sql::SQLString test = res->getString(5);
	//			//res->
	//			cout << "Username:" << res->getString(1) << endl;
	//			std::cout << "RoleId:" << res->getInt("roleId") << endl;
	//		}
	//		catch (sql::SQLException &e)
	//		{
	//			cout << e.what() << std::endl;
	//		}
	//	}
	//		
	//	delete res;

	//	delete pstmt;
	//	delete con;

	//}
	//catch (sql::SQLException &e) {
	//	cout << "# ERR: SQLException in " << __FILE__ << std::endl;
	//	cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
	//	cout << "# ERR: " << e.what() << std::endl;
	//	cout << " (MySQL error code: " << e.getErrorCode() << std::endl;
	//	cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	//}

	//cout << endl;

	//http_client l_client(L"http://192.168.7.40:80/test/server.php");
	//return 0;

	InitLogger(true);
	LOG_INFO("Hello world!!");

	RestConnection *Test = new RestConnection();
	Test->StartListen();


	while (1)
	{
	}

	return 0;
}

