/*
 * DataAccess.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: binhdu
 */

#include <assert.h>
#include "DataAccess.h"
#include "Configuration.h"
#include "LogFile.h"


namespace DAL
{ // namespace DAL


	DataAccess::DataAccess()
	{
		std::cout << "-----------------Create new Data acess -----------------" << std::endl;
		LOG_INFO("-----------------Create new Data acess -----------------");
		mHost = std::string(Configuration::GetSingleton()->getIpServerDB());
		mUser = std::string(Configuration::GetSingleton()->getUser());
		mPassword = std::string(Configuration::GetSingleton()->getPass());
		mDatabase = std::string(Configuration::GetSingleton()->getschema());
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

		if(mConn != NULL)
		{
			return mConn;
		}

		try
		{
			mConn = get_driver_instance()->connect(mHost, mUser, mPassword);

			if(mConn)
			{
				std::cout << "Create new connection" << std::endl;
				LOG_INFO("Create new connection");
				mConn->setSchema(mDatabase) ;
				mConn->setAutoCommit(false);
				return mConn;
			}
			else
			{
				std::cout <<"Create connection failed" << std::endl;
				LOG_ERROR("Create connection failed");
			}		
		}
		catch (sql::SQLException &e)
		{
		  LOG_ERROR("GetConnection # ERR: SQLException in " << __FILE__ );
		  LOG_ERROR("# ERR: " << e.what() );
		  LOG_ERROR(" (MySQL error code: " << e.getErrorCode() );
		  LOG_ERROR(", SQLState: " << e.getSQLState().c_str() << " )" );

		  LOG_ERROR("Create connection fail");
		  
		}


		if(mConn)
		{
			std::cout << "Close connection:" << mConn << std::endl;
			mConn->close();
			delete mConn;
			mConn = NULL;
		}
		return NULL;
	};


	sql::ResultSet* DataAccess::QueryData(std::string p_sql)
	{
		std::cout << p_sql << std::endl;
		LOG_INFO(p_sql);
		try
		{
			sql::Connection *l_conn = GetConnection();
			if(l_conn)
			{
				m_accessmutex.lock();
				sql::Statement *stmt = l_conn->createStatement() ;
				if(stmt)
				{
					sql::ResultSet *lResult = stmt->executeQuery(p_sql);
					delete stmt ;
					stmt = NULL;
					l_conn = NULL;

					m_accessmutex.unlock();
					return lResult;
				}
			
				l_conn = NULL;
			}
		}
		catch (sql::SQLException &e)
		{
			LOG_ERROR("QuerryData fail");
			std::cout << "QueryData ERROR: SQLException in " << __FILE__ << std::endl;
			std::cout << "ERROR: " << e.what();
			std::cout << " (MySQL error code: " << e.getErrorCode() << std::endl;
			std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;

			if (e.getErrorCode() == 1047) 
			{
				std::cout << "\nYour server does not seem to support Prepared Statements at all. ";
				std::cout << "Perhaps MYSQL < 4.1?" << std::endl;
			}

			if(mConn)
			{
				std::cout << "Close connection:" << mConn << std::endl;
				mConn->close();
				delete mConn;
				mConn = NULL;
			}
		}
		catch (std::runtime_error &e)
		{
			LOG_ERROR("QuerryData fail runtime error");
			std::cout << "QueryData ERROR: runtime_error in " << __FILE__  << std::endl;
			std::cout << "ERROR: " << e.what() << std::endl;

			if(mConn)
			{
				std::cout << "Close connection:" << mConn << std::endl;
				mConn->close();
				delete mConn;
				mConn = NULL;
			}
		}

		m_accessmutex.unlock();
		return NULL;
	};


	int DataAccess::QueryUpdate(std::string p_sql)
	{
		std::cout << p_sql << std::endl;
		LOG_INFO(p_sql);
		try
		{
			sql::Connection *l_conn = GetConnection();
			if(l_conn)
			{
				m_accessmutex.lock();
				sql::Statement *stmt = l_conn->createStatement();
				if(stmt)
				{
					int rowEffect = stmt->executeUpdate(p_sql) ;
					l_conn->commit();
					delete stmt ;
					stmt = NULL;
					l_conn = NULL;

					m_accessmutex.unlock();
					return rowEffect;
				}
			
				l_conn = NULL;

				m_accessmutex.unlock();
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

			if(mConn)
			{
				std::cout << "Close connection:" << mConn << std::endl;
				mConn->close();
				delete mConn;
				mConn = NULL;
			}
		}
		catch (std::runtime_error &e)
		{

			std::cout << "ERROR: runtime_error in " << __FILE__;
			std::cout << "ERROR: " << e.what() << std::endl;
			LOG_ERROR("Runtime error");
			LOG_ERROR(e.what());

			if(mConn)
			{
				std::cout << "Close connection:" << mConn << std::endl;
				mConn->close();
				delete mConn;
				mConn = NULL;
			}
		}

		m_accessmutex.unlock();
		return -1;

	};



	int DataAccess::QuerySystem(std::string p_sql)
	{
		std::cout << p_sql << std::endl;
		LOG_INFO(p_sql);
		try
		{
			sql::Connection *l_conn = GetConnection();
			if(l_conn)
			{
				m_accessmutex.lock();
				sql::Statement *stmt = l_conn->createStatement();
				if(stmt)
				{
					int rowEffect = stmt->execute(p_sql);
					l_conn->commit();

					delete stmt;
					stmt = NULL;
					l_conn = NULL;

					m_accessmutex.unlock();
					return rowEffect;
				}
			
				l_conn = NULL;
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

			if(mConn)
			{
				std::cout << "Close connection:" << mConn << std::endl;
				mConn->close();
				delete mConn;
				mConn = NULL;
			}
		}
		catch (std::runtime_error &e)
		{
			std::cout << "ERROR: runtime_error in " << __FILE__;
			std::cout << "ERROR: " << e.what() << std::endl;

			if(mConn)
			{
				std::cout << "Close connection:" << mConn << std::endl;
				mConn->close();
				delete mConn;
				mConn = NULL;
			}
		}

		m_accessmutex.unlock();
		return -1;

	};

}//end namespace DAL
