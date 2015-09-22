#include "stdafx.h"
#include "Object.h"
#include "Define_Mif.h"

namespace BLL
{

Object::Object(void)
{
}


Object::~Object(void)
{

}


sql::ResultSet* Object::SelectAll()
{
	std::string sql = std::string("SELECT* FROM vms_object, vms_device WHERE vms_object.device_id = vms_device.id");

	if (mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	//std::cout << "Excute: " << sql << std::endl;
	sql::ResultSet  *table = mDA->QueryData(sql);

	if (table == NULL)
	{
		std::wcout << "Get all table vms_object failed" << std::endl;
		LOG_ERROR("Get all table vms_object failed");
	}
	else
	{
		return table;
	}

	return NULL;
};

sql::ResultSet* Object::SelectAll(std::string pUsername)
{
	std::string sql("");
	BLL::User *MyUser = new BLL::User();
	if(MyUser->IsAdmin(pUsername))
	{
		sql = std::string("SELECT* FROM  vms_object,  vms_device WHERE vms_device.id = vms_object.device_id");
	}
	else
	{
		sql = std::string("SELECT*");
		sql += std::string(" FROM  vms_object, vms_device, vms_user_object WHERE vms_object.id = vms_user_object.object_id AND vms_device.id = vms_object.device_id AND ");
		sql += std::string("vms_user_object.username = '");
		sql += pUsername + std::string("'");
	}

	if (mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	//std::cout << "Excute: " << sql << std::endl;
	sql::ResultSet  *table = mDA->QueryData(sql);

	if (table == NULL)
	{
		std::wcout << "Get all table vms_object failed" << std::endl;
		LOG_ERROR("Get all table vms_object failed");
	}
		
	if(MyUser)
	{
		delete MyUser;
		MyUser = NULL;
	}


	return table;
};


sql::ResultSet* Object::SelectWhere(int p_id)
{
	std::string sql = std::string("SELECT* FROM  vms_object,  vms_device WHERE vms_device.id = vms_object.device_id AND vms_object.id =") +
		std::string("'") +std::to_string(p_id) + std::string("'");

	if (mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	//std::cout << "Excute: " << sql << std::endl;
	sql::ResultSet  *table = mDA->QueryData(sql);

	if (table == NULL)
	{
		std::wcout << "Get where table vms_object failed" << std::endl;
		LOG_ERROR("Get where table vms_object failed");
	}
	else
	{
		return table;
	}

	return NULL;

};

bool Object::ExistName(std::string p_name)
{
	std::string sql = std::string("SELECT* FROM vms_object WHERE name =");
	sql += std::string("'") + p_name + std::string("'");

	if (mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	sql::ResultSet  *table = mDA->QueryData(sql);
	bool l_true_false = false;;

	if (table == NULL)
	{
		std::wcout << "Get table vms_object failed" << std::endl;
		LOG_ERROR("Get table vms_object failed");

		l_true_false = false;
	}
	else
	{
		if(table->rowsCount() >0)
		{
			l_true_false = true;
		}
		else
		{
			l_true_false = false;
		}
	}

	delete table;

	return l_true_false;
};

bool Object::ExistIP(std::string p_ip)
{
	std::string sql = std::string("SELECT* FROM vms_object WHERE ip =");
	sql += std::string("'") + p_ip + std::string("'");

	if (mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	sql::ResultSet  *table = mDA->QueryData(sql);
	bool l_true_false = false;;

	if (table == NULL)
	{
		std::wcout << "Get table vms_object failed" << std::endl;
		LOG_ERROR("Get table vms_object failed");

		l_true_false = false;
	}
	else
	{
		if(table->rowsCount() >0)
		{
			l_true_false = true;
		}
		else
		{
			l_true_false = false;
		}
	}

	delete table;

	return l_true_false;
};

int Object::Insert(
	std::string p_name,
	std::string p_ip,
	int p_port,
	std::string p_description,
	std::string p_location,
	int p_deviceid,
	std::string  p_program,
	std::string p_screenshot,
	int p_status
	)
{
	std::string sql =
		std::string("INSERT INTO vms_object(name,ip, port,description, location, device_id) VALUES(") +
		std::string("'") + p_name + std::string("',") +
		std::string("'") + p_ip + std::string("',") +
		std::string("'") + std::to_string(p_port) + std::string("',") +
		std::string("'") + p_description + std::string("',") +
		std::string("'") + p_location + std::string("',") +
		std::string("'") + std::to_string(p_deviceid) + std::string("')");
		//std::string("'") + p_program + std::string("',") +
		//std::string("'") + p_screenshot + std::string("')");
	
		//std::string("'") + std::to_string(p_status) + std::string("')");
	
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

			delete data;
			data = NULL;
		}
			
		return id_vms;
	}
	else
	{

		return -1;
	}

	return -1;
};

bool Object::Delete(int p_id)
{
	std::string sql = std::string("DELETE FROM vms_object WHERE id =") +
		std::string("'") + std::to_string(p_id) + std::string("'");

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

int Object::Update(
	int p_id,
	std::string p_name,
	std::string p_ip,
	int p_port,
	std::string p_description,
	std::string p_location,
	int p_deviceid,
	std::string  p_program,
	std::string p_screenshot,
	int p_status)
{
	if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//1. name
		if(p_name.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_object SET name =") +
				std::string("'") + p_name + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update name failed!" << std::endl;
				return exist_vms_name;
			}
		}

		//2. ip
		if(p_ip.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_object SET ip =") +
				std::string("'") + p_ip + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update ip failed!" << std::endl;
				return exist_vms_ip;
			}
		}

		//3. description
		if(p_description.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_object SET description =") +
				std::string("'") + p_description + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update description failed!" << std::endl;
				return false;
			}
		}
		//4. location
		if(p_location.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_object SET location =") +
				std::string("'") + p_location + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update location failed!" << std::endl;
				return false;
			}
		}
		//5. screenshot
		if(p_screenshot.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_object SET screenshot =") +
				std::string("'") + p_screenshot + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update screenshot failed!" << std::endl;
				return false;
			}
		}

		//6. program
		if(p_program.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_object SET program =") +
				std::string("'") + p_program + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update program failed!" << std::endl;
				return false;
			}
		}

		//7. width
		if(p_deviceid != INT_MAX)
		{
			std::string sql = std::string("UPDATE vms_object SET device_id =") +
				std::string("'") + std::to_string(p_deviceid) + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update deviceid failed!" << std::endl;
				return false;
			}
		}

		//8. height
		if(p_status != INT_MAX)
		{
			std::string sql = std::string("UPDATE vms_object SET status =") +
				std::string("'") + std::to_string(p_status) + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update height failed!" << std::endl;
				return false;
			}
		}

		//9. port
		if(p_port != INT_MAX)
		{
			std::string sql = std::string("UPDATE vms_object SET port =") +
				std::string("'") + std::to_string(p_port) + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update port failed!" << std::endl;
				return false;
			}
		}
		
	return true;
};

}