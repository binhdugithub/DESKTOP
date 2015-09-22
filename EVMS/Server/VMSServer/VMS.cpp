#include "stdafx.h"
#include "VMS.h"
#include "LogFile.h"

namespace BLL
{

	VMS::VMS(void)
	{

	}


	VMS::~VMS(void)
	{
	}

	int VMS::Insert(
			std::string name,
			float width,
			float height,
			std::string location,
			std::string content
			)
	{
		std::string sql =
			std::string("INSERT INTO vms_device(name,width, height,location,content) VALUES(") +
			std::string("'") + name + std::string("',") +
			std::string("'") + std::to_string(width) + std::string("',") +
			std::string("'") + std::to_string(height) + std::string("',") +
			std::string("'") + location + std::string("',") +
			std::string("'") + content + std::string("')");
	
		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		std::cout << "Excute: " << sql << std::endl;
		if (mDA->QueryUpdate(sql) > 0)
		{
			std::string sql = std::string("SELECT LAST_INSERT_ID()");
			sql::ResultSet *data = mDA->QueryData(sql);
			int id_vms = -1;
			if(data)
			{
				while (data->next())
				{
					id_vms = data->getInt(1);
					break;
				}
			}
			
			return id_vms;
		}
		else
		{

			return -1;
		}

		return -1;
	};


	bool VMS::Delete(int id)
	{
		std::string sql = std::string("DELETE FROM vms_device WHERE vmsid =") +
			std::string("'") + std::to_string(id) + std::string("'");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		std::cout << "Excute: " << sql << std::endl;
		if (mDA->QueryUpdate(sql) > 0)
			return true;
		else
			return false;
	};


	bool VMS::Update(int id,
		std::string name,
		float width,
		float height,
		std::string location,
		std::string content)
	{

		return false;
	};

	sql::ResultSet* VMS::SelectAll()
	{
		std::string sql = std::string("SELECT* FROM vms_device");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(sql);

		if (table == NULL)
		{
			std::wcout << "Get all table vms_device failed" << std::endl;
			LOG_ERROR("Get all table vms_device failed");
		}
		else
		{
			return table;
		}

		return NULL;
	}

	sql::ResultSet* VMS::SelectAll(std::string pUsername)
	{
		std::string sql = std::string("SELECT*");
					sql += std::string(" FROM  vms_device, vms_user_device where vms_device.vmsid = vms_user_device.vmsid AND ");
					sql += std::string("vms_user_device.username = '");
					sql += pUsername + std::string("'");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(sql);

		if (table == NULL)
		{
			std::wcout << "Get all table vms_device failed" << std::endl;
			LOG_ERROR("Get all table vms_device failed");
		}
		else
		{
			return table;
		}

		return NULL;
	}

	sql::ResultSet* VMS::SelectWhere(std::string id)
	{
		std::string sql = std::string("SELECT* FROM vms_device where vmsid = ") +
			std::string("'") + id + std::string("'");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(sql);

		if (table == NULL)
		{
			std::wcout << "Get where table vms_device failed" << std::endl;
			LOG_ERROR("Get where table vms_device failed");
		}
		else
		{
			return table;
		}

		return NULL;
	}

}//end namespace BLL
