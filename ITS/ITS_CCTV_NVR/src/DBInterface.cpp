
#include "DBInterface.h"

DBInterface* DBInterface::m_Instance = NULL;

DBInterface::DBInterface()
{
	m_DA = new DAL::DataAccess();
}


DBInterface::~DBInterface()
{
	if (m_DA)
	{
		delete m_DA;
		m_DA = NULL;
	}
}


DBInterface* DBInterface::GetSingleton()
{
	if(m_Instance == NULL)
	{
		m_Instance = new DBInterface();
	}

	return m_Instance;
}

bool DBInterface::Insert(std::string p_query)
{
	try
		{
			if (m_DA == NULL)
			{
				m_DA = new DAL::DataAccess();
			}

			if(m_DA->QueryUpdate(p_query) >= 0)
				return true;

		}
		catch (sql::SQLException &e)
		{
			//LOG_ERROR("QuerryData fail");
			std::cout << "ERROR: SQLException in " << __FILE__ << std::endl;
			std::cout << "ERROR: " << e.what();
			std::cout << " (MySQL error code: " << e.getErrorCode() << std::endl;
			std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;

			if (e.getErrorCode() == 1047)
			{
				std::cout << "\nYour server does not seem to support Prepared Statements at all. ";
				std::cout << "Perhaps MYSQL < 4.1?" << std::endl;
			}
		}
		catch (std::runtime_error &e)
		{
			//LOG_ERROR("QuerryData fail runtime error");
			std::cout << "ERROR: runtime_error in " << __FILE__  << std::endl;
			std::cout << "ERROR: " << e.what() << std::endl;
		}

	return false;
}

bool DBInterface::Update(std::string p_query)
{

	if (m_DA == NULL)
	{
		m_DA = new DAL::DataAccess();
	}

	if(m_DA->QueryUpdate(p_query) >= 0)
		return true;

	return false;
}

bool DBInterface::Delete(std::string p_query)
{
	try
	{
		if (m_DA == NULL)
		{
			m_DA = new DAL::DataAccess();
		}

		if(m_DA->QueryUpdate(p_query) >= 0)
			return true;

	}
	catch (sql::SQLException &e)
	{
		//LOG_ERROR("QuerryData fail");
		std::cout << "ERROR: SQLException in " << __FILE__ << std::endl;
		std::cout << "ERROR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode() << std::endl;
		std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;

		if (e.getErrorCode() == 1047)
		{
			std::cout << "\nYour server does not seem to support Prepared Statements at all. ";
			std::cout << "Perhaps MYSQL < 4.1?" << std::endl;
		}
	}
	catch (std::runtime_error &e)
	{
		//LOG_ERROR("QuerryData fail runtime error");
		std::cout << "ERROR: runtime_error in " << __FILE__  << std::endl;
		std::cout << "ERROR: " << e.what() << std::endl;
	}


	return false;
}

std::vector<std::vector<std::string>> DBInterface::GetListFile2Delete(int p_number)
{
	std::vector<std::vector<std::string>> l_arrayFile;
	std::string l_query = "SELECT id, filename, starttime FROM its_nvr_videostorage ORDER BY starttime ASC LIMIT " + std::to_string(p_number);
	try
	{
		if (m_DA == NULL)
		{
			m_DA = new DAL::DataAccess();
		}

		sql::ResultSet *table = m_DA->QueryData(l_query);

		if (table)
		{
			while (table->next())
			{
				std::vector<std::string> l_file;
				l_file.push_back(std::string(table->getString(1)));
				l_file.push_back(std::string(table->getString(2)));
				l_file.push_back(std::string(table->getString(3)));

				l_arrayFile.push_back(l_file);
			}

			delete table;
			table = NULL;

		}
		else
		{
			std::cout << "DATABASE: GetListFile2Delete faile" << std::endl;
			LOG_ERROR("DATABASE: GetListFile2Delete failed");
		}

	}
	catch (sql::SQLException &e)
	{
		//LOG_ERROR("QuerryData fail");
		std::cout << "ERROR: SQLException in " << __FILE__ << std::endl;
		std::cout << "ERROR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode() << std::endl;
		std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;

		if (e.getErrorCode() == 1047)
		{
			std::cout << "\nYour server does not seem to support Prepared Statements at all. ";
			std::cout << "Perhaps MYSQL < 4.1?" << std::endl;
		}
	}
	catch (std::runtime_error &e)
	{
		//LOG_ERROR("QuerryData fail runtime error");
		std::cout << "ERROR: runtime_error in " << __FILE__  << std::endl;
		std::cout << "ERROR: " << e.what() << std::endl;
	}

	return l_arrayFile;
}

std::vector<std::vector<std::string>> DBInterface::GetRecordedCam()
{
	std::vector<std::vector<std::string>> l_arrayCam;

	std::string l_query = "SELECT id, recordurl, recordmode, cliplength FROM its_cam WHERE recordmode != 0";
	try
	{
		if (m_DA == NULL)
		{
			m_DA = new DAL::DataAccess();
		}


		sql::ResultSet *table = m_DA->QueryData(l_query);
		if(table)
		{
			while (table->next())
			{
				std::vector<std::string> l_cam;
				l_cam.push_back(std::string(table->getString(1)));
				l_cam.push_back(std::string(table->getString(2)));
				l_cam.push_back(std::to_string(table->getInt(3)));
				l_cam.push_back(std::to_string(table->getInt(4)));

				l_arrayCam.push_back(l_cam);
			}

			delete table;
			table = NULL;
		}
		else
		{
			std::cout << "DATABASE: GetRecordedCam faile" << std::endl;
			LOG_ERROR("DATABASE: GetRecordedCam failed");
		}


	}
	catch (sql::SQLException &e)
	{
		//LOG_ERROR("QuerryData fail");
		std::cout << "ERROR: SQLException in " << __FILE__ << "/" <<  __FUNCTION__ << std::endl;
		std::cout << "ERROR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode() << std::endl;
		std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;

		if (e.getErrorCode() == 1047)
		{
			std::cout << "\nYour server does not seem to support Prepared Statements at all. ";
			std::cout << "Perhaps MYSQL < 4.1?" << std::endl;
		}
	}
	catch (std::runtime_error &e)
	{
		//LOG_ERROR("QuerryData fail runtime error");
		std::cout << "ERROR: runtime_error in " << __FILE__  << std::endl;
		std::cout << "ERROR: " << e.what() << std::endl;
	}

	return l_arrayCam;
}

