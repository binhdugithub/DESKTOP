#include "stdafx.h"
#include "History.h"

namespace BLL
{

	History::History(void)
	{
	}


	History::~History(void)
	{
	}

	sql::ResultSet* History::SelectAll()
	{
		std::string sql = std::string("SELECT* FROM vms_history,vms_action where vms_history.action = vms_action.id");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(sql);
		if (table == NULL)
		{
			std::wcout << "Get all table vms_history failed" << std::endl;
			LOG_ERROR("Get all table vms_history failed");
		}
		else
		{
			return table;
		}

		return NULL;
	};

	sql::ResultSet* History::SelectWhere(std::string p_username,
									int p_action,
									std::string p_starttime,
									std::string p_endtime)
	{
		std::string l_sql = std::string("SELECT* FROM vms_history,vms_action where vms_history.action = vms_action.id ");
		if(p_username.length() > 0)
			l_sql += std::string("AND username = ") + std::string("'") + p_username + std::string("'");

		if(p_action != INT_MAX)
			l_sql += std::string(" AND action= ") + std::string("'") + std::to_string(p_action) + std::string("'");

		if(p_starttime.length() > 0)
		{
			l_sql += std::string(" AND UNIX_TIMESTAMP(vms_history.time) >= UNIX_TIMESTAMP(") + std::string("'") + p_starttime + std::string("')");
		}


		if(p_endtime.length() > 0)
		{
			l_sql += std::string("AND UNIX_TIMESTAMP(vms_history.time) <= UNIX_TIMESTAMP(") + std::string("'") + p_endtime + std::string("')");
		}

		l_sql += std::string(" ORDER BY vms_history.id");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(l_sql);
		if (table == NULL)
		{
			std::wcout << "Get where table vms_history failed" << std::endl;
			LOG_ERROR("Get where table vms_history failed");
		}
		else
		{
			return table;
		}

		return NULL;
	}

	bool History::Insert(std::string p_username,
				int p_action,
				std::string p_detail)
	{
		std::string sql =
		std::string("INSERT INTO vms_history(username, action,detail) VALUES(") +
		std::string("'") + p_username + std::string("',") +
		std::string("'") + std::to_string(p_action) + std::string("',") +
		std::string("'") + p_detail + std::string("')");
	
		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		if (mDA->QueryUpdate(sql) > 0)
		{
			return true;		
		}
		else
		{
			return false;
		}

		return false;

	};

	bool History::Delete(int p_id)
	{
		std::string sql = std::string("DELETE FROM vms_history WHERE id =") +
			std::string("'") + std::to_string(p_id) + std::string("'");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		if (mDA->QueryUpdate(sql) > 0)
			return true;
		else
			return false;
	};

	bool History::Update(int p_id, 
				std::string p_username,
				int p_action,
				std::string p_time,
				std::string p_detail)
	{

		return false;
	};
}