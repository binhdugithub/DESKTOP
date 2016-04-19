/*
 * Story.cpp
 *
 *  Created on: Dec 15, 2015
 *      Author: root
 */

#include "Story.h"


namespace BLL
{

Story::Story()
{
	// TODO Auto-generated constructor stub
	m_DA = new DAL::DataAccess();

}

Story::~Story()
{
	// TODO Auto-generated destructor stub
	if (m_DA)
	{
		delete m_DA;
		m_DA = NULL;
	}
}


sql::ResultSet* Story::SelectAll()
{
	std::string sql = std::string("SELECT* FROM Story ORDER BY id ASC");

	if (m_DA == NULL)
	{
		m_DA = new DAL::DataAccess();
	}

	sql::ResultSet  *table = m_DA->QueryData(sql);

	if (table == NULL)
	{
		std::cout << "Get all table Story failed" << std::endl;
		LOG_ERROR("Get all table Story failed");
	}
	else
	{
		return table;
	}

	return NULL;
}

sql::ResultSet* Story::SelectList(int p_idstart, int p_limit)
{
	std::string sql = std::string("");

	if (p_limit > 0)
	{
		sql = std::string("SELECT* FROM Story WHERE id > ");
		sql += std::to_string(p_idstart);
		sql += std::string(" ORDER BY id ASC LIMIT ");
		sql += std::to_string(p_limit);
	}
	else
	{
		sql = std::string("SELECT* FROM Story WHERE id > ");
		sql += std::to_string(p_idstart);
		sql += std::string(" ORDER BY id ASC ");
	}


	if (m_DA == NULL)
	{
		m_DA = new DAL::DataAccess();
	}

	sql::ResultSet  *table = m_DA->QueryData(sql);

	if (table == NULL)
	{
		std::cout << "Get all table Story failed" << std::endl;
		LOG_ERROR("Get all table Story failed");
	}
	else
	{
		return table;
	}

	return NULL;
}


sql::ResultSet* Story::SelectWhere(int p_id)
{
	std::string sql = std::string("SELECT* FROM Story WHERE id = ") +
			std::string("'") + std::to_string(p_id) + std::string("'");

	if (m_DA == NULL)
	{
		m_DA = new DAL::DataAccess();
	}

	sql::ResultSet  *table = m_DA->QueryData(sql);

	if (table == NULL)
	{
		std::cout << "Get Story failed" << std::endl;
		LOG_ERROR("Get Story failed");
	}
	else
	{
		return table;
	}

	return NULL;

}

bool Story::Insert(std::string p_title,std::string p_content,std::string p_image,std::string p_audio)
{
	return true;
}

bool Story::Delete(int p_id)
{
	return true;
}

bool Story::Update(int 		p_id,std::string p_title,std::string p_content,std::string p_image,std::string p_audio,float p_rate)
{
	return true;
}

}//end namespace BLL
