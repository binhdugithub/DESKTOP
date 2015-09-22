#include "stdafx.h"
#include "Device.h"
#include "LogFile.h"

namespace BLL
{

	Device::Device(void)
	{

	}


	Device::~Device(void)
	{
	}

	int Device::Insert(
		std::string p_manufacturer,
		std::string p_model,
		float p_width,
		float p_height,
		int p_ncolor,
		std::string p_multitype
			)
	{
		std::string sql =
			std::string("INSERT INTO vms_device(manufacturer,model, width,height,ncolor, multitype) VALUES(") +
			std::string("'") + p_manufacturer + std::string("',") +
			std::string("'") + p_model + std::string("',") +
			std::string("'") + std::to_string(p_width) + std::string("',") +
			std::string("'") + std::to_string(p_height) + std::string("',") +
			std::string("'") + std::to_string(p_ncolor) + std::string("',") +
			std::string("'") + p_multitype + std::string("')");
	
		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
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


	bool Device::Delete(int id)
	{
		std::string sql = std::string("DELETE FROM vms_device WHERE vmsid =") +
			std::string("'") + std::to_string(id) + std::string("'");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		if (mDA->QueryUpdate(sql) > 0)
			return true;
		else
			return false;
	};


	bool Device::Update(
		int p_id,
		std::string p_manufacturer,
		std::string p_model,
		float p_width,
		float p_height,
		int p_ncolor,
		std::string p_multitype
		)
	{
		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//1. manufacturer
		if(p_manufacturer.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_device SET manufacturer =") +
				std::string("'") + p_manufacturer + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update manufacturer failed!" << std::endl;
				return false;
			}
		}

		//2. width
		if(p_width != FLT_MAX)
		{
			std::string sql = std::string("UPDATE vms_device SET width =") +
				std::string("'") + std::to_string(p_width) + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update width failed!" << std::endl;
				return false;
			}
		}

		//3. height
		if(p_height != FLT_MAX)
		{
			std::string sql = std::string("UPDATE vms_device SET height =") +
				std::string("'") + std::to_string(p_height) + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update height failed!" << std::endl;
				return false;
			}
		}

		//4. model
		if(p_model.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_device SET model =") +
				std::string("'") + p_model + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update model failed!" << std::endl;
				return false;
			}
		}
		
		//5. color
		if(p_ncolor != INT_MAX)
		{
			std::string sql = std::string("UPDATE vms_device SET ncolor =") +
				std::string("'") + std::to_string(p_ncolor) + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update ncolor failed!" << std::endl;
				return false;
			}
		}

		//6. multitype
		if(p_multitype.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_device SET multitype =") +
				std::string("'") + p_multitype + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update multitype failed!" << std::endl;
				return false;
			}
		}

		
		return true;
	};

	sql::ResultSet* Device::SelectAll()
	{
		std::string sql = std::string("SELECT* FROM vms_device");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
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

	sql::ResultSet* Device::SelectAll(std::string pUsername)
	{
		std::string sql = std::string("SELECT*");
					sql += std::string(" FROM  vms_device, vms_user_device where vms_device.vmsid = vms_user_device.vmsid AND ");
					sql += std::string("vms_user_device.username = '");
					sql += pUsername + std::string("'");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(sql);

		if (table == NULL)
		{
			std::wcout << "Get all table vms_device failed" << std::endl;
			LOG_ERROR("Get all table vms_device failed");
		}
		
		return table;
	
	}

	sql::ResultSet* Device::SelectWhere(std::string id)
	{
		std::string sql = std::string("SELECT* FROM vms_device where vmsid = ") +
			std::string("'") + id + std::string("'");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
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
