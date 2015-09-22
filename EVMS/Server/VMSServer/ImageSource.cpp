#include "stdafx.h"
#include "ImageSource.h"

namespace BLL
{

	ImageSource::ImageSource(void)
	{
	}


	ImageSource::~ImageSource(void)
	{
	}

	sql::ResultSet* ImageSource::SelectAll()
	{
		std::string sql = std::string("SELECT* FROM vms_image_resource");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(sql);

		if (table == NULL)
		{
			std::wcout << "vms_image_resource get table fail" << std::endl;
			LOG_ERROR("vms_image_resource get table fail");
		}
		else
		{
			return table;
		}

		return NULL;
	};

	sql::ResultSet* ImageSource::SelectWhere(int)
	{

		return NULL;
	};

	bool ImageSource::Insert(std::string p_link)
	{

		return false;
	};

	bool ImageSource::Delete(int p_id)
	{
		std::string sql = std::string("DELETE FROM vms_image_resource WHERE id =") +
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
	};

	bool ImageSource::Update(int p_id, std::string p_link)
	{

		return false;
	};

}
