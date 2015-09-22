#include "stdafx.h"
#include "Action.h"
#include "LogFile.h"

namespace BLL
{

	Action::Action(void)
	{
	}


	Action::~Action(void)
	{
	}

	sql::ResultSet* Action::SelectAll()
	{
		std::string sql = std::string("SELECT* FROM vms_action");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(sql);

		std::string l_pass("");
		if (table == NULL)
		{
			std::wcout << "Get all data from vms_action fail" << std::endl;
			LOG_ERROR("Get all data from vms_action fail");
		}
		else
		{
			return table;
		}

		return NULL;
	}


	bool Action::Insert(int p_id, std::string p_name)
	{
		std::string sql = std::string("INSERT INTO vms_action VALUES(");
		sql += std::string("'") + std::to_string(p_id) + std::string("'");
		sql += std::string("'") + p_name + std::string("'");
		sql += std::string(")");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		if (mDA->QueryUpdate(sql) > 0)
			return true;
		else
			return false;

		return false;
	};

	bool Action::Delete(int p_id)
	{
		std::string sql = std::string("DELETE FROM vms_action WHERE id =") +
					sql += std::string("'") + std::to_string(p_id) + std::string("'");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		if (mDA->QueryUpdate(sql) > 0)
			return true;
		else
			return false;

		return false;
	};

	bool Action::Update(int p_id, std::string p_name)
	{
		std::string sql = std::string("UPDATE vms_action SET description =") +
			std::string("'") + p_name + std::string("'") +
			std::string("where id = ") +
			std::string("'") + std::to_string(p_id) + std::string("'");

		if (mDA->QueryUpdate(sql) < 0)
		{
			std::wcout << L"Update role failed!" << std::endl;
			return false;
		}

		return true;
	};

}