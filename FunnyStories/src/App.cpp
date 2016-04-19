/*
 * App.cpp
 *
 *  Created on: Mar 10, 2016
 *      Author: root
 */

#include "App.h"

namespace BLL
{
App::App()
{
	// TODO Auto-generated constructor stub
	m_DA = new DAL::DataAccess();
}

App::~App()
{
	// TODO Auto-generated destructor stub
	if (m_DA)
	{
		delete m_DA;
		m_DA = NULL;
	}
}


sql::ResultSet* App::SelectAll()
{
	std::string sql = std::string("SELECT* FROM App");

	if (m_DA == NULL)
	{
		m_DA = new DAL::DataAccess();
	}

	sql::ResultSet  *table = m_DA->QueryData(sql);

	if (table == NULL)
	{
		std::cout << "Get all table App failed" << std::endl;
		LOG_ERROR("Get all table App failed");
	}
	else
	{
		return table;
	}

	return NULL;
}

sql::ResultSet* App::SelectList(int p_idstart)
{
	std::string sql = std::string("SELECT* FROM App WHERE id > ");
	sql += std::to_string(p_idstart);

	if (m_DA == NULL)
	{
		m_DA = new DAL::DataAccess();
	}

	sql::ResultSet  *table = m_DA->QueryData(sql);

	if (table == NULL)
	{
		std::cout << "Get all table App failed" << std::endl;
		LOG_ERROR("Get all table App failed");
	}
	else
	{
		return table;
	}

	return NULL;
}

}//end namespace BLL
