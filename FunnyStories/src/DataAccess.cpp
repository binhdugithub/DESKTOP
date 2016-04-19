/*
 * DataAccess.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: binhdu
 */

#include <assert.h>
#include "DataAccess.h"
#include "Configuration.h"
#include "MyLogger.h"


namespace DAL
{ // namespace DAL


	DataAccess::DataAccess()
	{
		mHost = std::string(Configuration::GetSingleTon()->db_host);
		mUser = std::string(Configuration::GetSingleTon()->db_user);
		mPassword = std::string(Configuration::GetSingleTon()->db_pass);
		mDatabase = std::string(Configuration::GetSingleTon()->db_database);
		mConn = NULL;
	}


	DataAccess::~DataAccess()
	{
		// TODO Auto-generated destructor stub
		if(mConn)
		{
			std::cout << "Close connection:" << mConn << std::endl;
			mConn->close();
			delete mConn;
			mConn = NULL;
		}

	};

	sql::Connection* DataAccess::GetConnection()
	{
		static int a = 0;
		a++;

		std::cout << "-------------------------------------------------> " << a << std::endl;

		if(mConn != NULL)
		{
			return mConn;
		}
		
		try
		{
			mConn = get_driver_instance()->connect(mHost, mUser, mPassword);

			if(mConn)
			{
				mConn->setSchema(mDatabase) ;
				mConn->setAutoCommit(false);
				std::cout << "Create connection :" << mConn << std::endl;
				return mConn;
			}
			else
			{
				std::cout <<"Create connection failed" << std::endl;
				LOG_ERROR("Create connection failed");
				return NULL;
			}		
		}
		catch (sql::SQLException &e)
		{
		  LOG_ERROR("# ERR: SQLException in " << __FILE__ );
		  LOG_ERROR("# ERR: " << e.what() );
		  LOG_ERROR(" (MySQL error code: " << e.getErrorCode() );
		  LOG_ERROR(", SQLState: " << e.getSQLState().c_str() << " )" );

		  LOG_ERROR("Create connection fail");
		  
		}

		return NULL;
	};


	sql::ResultSet* DataAccess::QueryData(std::string p_sql)
	{
		std::cout << "Exute sql:" << p_sql << std::endl;
		LOG_INFO("Exute sql: " << p_sql);
		try
		{
			sql::Connection *l_conn = GetConnection();
			if(l_conn)
			{
				sql::Statement *stmt = l_conn->createStatement() ;
				if(stmt)
				{
					sql::ResultSet *lResult = stmt->executeQuery(p_sql);
					delete stmt ;
					stmt = NULL;
					l_conn = NULL;

					return lResult;
				}
			
				l_conn = NULL;
				return NULL;
			}
			else
			{
				return NULL;
			}
		}
		catch (sql::SQLException &e)
		{
			LOG_ERROR("QuerryData fail");
			std::cout << "ERROR: SQLException in " << __FILE__ << std::endl;
			std::cout << "ERROR: " << e.what();
			std::cout << " (MySQL error code: " << e.getErrorCode() << std::endl;
			std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;

			if (e.getErrorCode() == 1047) 
			{
				std::cout << "\nYour server does not seem to support Prepared Statements at all. ";
				std::cout << "Perhaps MYSQL < 4.1?" << std::endl;
			}

			return NULL;
		}
		catch (std::runtime_error &e)
		{
			LOG_ERROR("QuerryData fail runtime error");
			std::cout << "ERROR: runtime_error in " << __FILE__  << std::endl;
			std::cout << "ERROR: " << e.what() << std::endl;
			return NULL;
		}

		return NULL;
	};


	int DataAccess::QueryUpdate(std::string p_sql)
	{
		std::cout << "Exute sql:" << p_sql << std::endl;
		try
		{

			sql::Connection *l_conn = GetConnection();
			if(l_conn)
			{
				sql::Statement *stmt = l_conn->createStatement();
				if(stmt)
				{
					int rowEffect = stmt->executeUpdate(p_sql) ;
					l_conn->commit();
					delete stmt ;
					stmt = NULL;
					l_conn = NULL;

					return rowEffect;
				}
			
				l_conn = NULL;
				return -1;
			}
			else
			{
				return -1;
			}
			
		}
		catch (sql::SQLException &e	)
		{
			std::cout << "ERROR: SQLException in " << __FILE__ << std::endl;
			std::cout << "ERROR: " << e.what() << std::endl;
			std::cout << " (MySQL error code: " << e.getErrorCode() << std::endl;
			std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;

			if (e.getErrorCode() == 1047)
			{
				std::cout << "\nYour server does not seem to support Prepared Statements at all. " << std::endl;
				std::cout << "Perhaps MYSQL < 4.1?" << std::endl;
			}
			return -1;
		}
		catch (std::runtime_error &e)
		{

			std::cout << "ERROR: runtime_error in " << __FILE__;
			std::cout << "ERROR: " << e.what() << std::endl;
			LOG_ERROR("Runtime error");
			LOG_ERROR(e.what());
			return -1;
		}

		return -1;

	};



	int DataAccess::QuerySystem(std::string p_sql)
	{
		std::cout << p_sql << std::endl;
		try
		{
			sql::Connection *l_conn = GetConnection();
			if(l_conn)
			{
				sql::Statement *stmt = l_conn->createStatement();
				if(stmt)
				{
					int rowEffect = stmt->execute(p_sql);
					l_conn->commit();

					delete stmt;
					stmt = NULL;
					l_conn = NULL;

					return rowEffect;
				}
			
				l_conn = NULL;
				return -1;
			}
			else
			{
				return -1;
			}
			

		}
		catch (sql::SQLException &e)
		{
			std::cout << "ERROR: SQLException in " << __FILE__;
			std::cout << "ERROR: " << e.what();
			std::cout << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;

			if (e.getErrorCode() == 1047)
			{
				std::cout << "\nYour server does not seem to support Prepared Statements at all. ";
				std::cout << "Perhaps MYSQL < 4.1?" << std::endl;
			}

			return -1;
		}
		catch (std::runtime_error &e)
		{
			std::cout << "ERROR: runtime_error in " << __FILE__;
			std::cout << "ERROR: " << e.what() << std::endl;
			return -1;
		}
		return -1;

	};

}//end namespace DAL
