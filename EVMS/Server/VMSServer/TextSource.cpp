#include "stdafx.h"
#include "TextSource.h"

namespace BLL
{
	TextSource::TextSource(void)
	{
		
	}


	TextSource::~TextSource(void)
	{

	}

	sql::ResultSet* TextSource::SelectAll()
	{
		std::string sql = std::string("SELECT* FROM vms_text_resource");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(sql);

		std::string l_pass("");
		if (table == NULL)
		{
			std::wcout << "Get all data from vms_text_resource fail" << std::endl;
			LOG_ERROR("Get all data from vms_text_resource fail");
		}
		else
		{
			return table;
		}
		return NULL;
	};

	sql::ResultSet* TextSource::Select(int p_id)
	{
		std::string sql = std::string("SELECT* FROM vms_text_resource where id =");
					sql += std::string("'");
					sql += std::to_string(p_id);
					sql += std::string("'");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(sql);

		std::string l_pass("");
		if (table == NULL)
		{
			std::wcout << "Get all data from vms_text_resource fail" << std::endl;
			LOG_ERROR("Get all data from vms_text_resource fail");
		}
		else
		{
			return table;
		}
		
		return NULL;
	};

	bool TextSource::Insert(
		float p_x,
		float p_y,
		float p_w,
		float p_h,
		std::string p_font,
		std::string p_wfontw,
		float p_fontz,
		std::string p_des)
	{

		std::string sql = std::string("INSERT INTO vms_text_resource VALUES(") +
		std::string("''") +
		std::string("'") + std::to_string(p_x) + std::string("',") +
		std::string("'") + std::to_string(p_y) + std::string("',") +
		std::string("'") + std::to_string(p_w) + std::string("',") +
		std::string("'") + std::to_string(p_h) + std::string("',") +
		std::string("'") + p_des + std::string("',") +
		std::string("'") + p_font + std::string("',") +
		std::string("'") + p_wfontw + std::string("',") +
		std::string("'") + std::to_string(p_fontz) + std::string("'") +
		std::string(")");

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

	bool TextSource::Delete(int p_id)
	{
		std::string sql = std::string("DELETE FROM vms_text_resource WHERE id =") +
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
		
	bool TextSource::Update(
		int p_id,
		float p_x,
		float p_y,
		float p_w,
		float p_h,
		std::string p_font,
		std::string p_wfontw,
		float p_fontz,
		std::string p_des)
	{
		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//1. xpos
		//if(p_name.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_text_resource SET xpos =") +
				std::string("'") + std::to_string(p_x) + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update xpos failed!" << std::endl;
				return false;
			}
		}

		//2. ypos
		//if(p_name.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_text_resource SET ypos =") +
				std::string("'") + std::to_string(p_y) + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update ypos failed!" << std::endl;
				return false;
			}
		}

		//3. width
		//if(p_name.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_text_resource SET width =") +
				std::string("'") + std::to_string(p_w) + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update width failed!" << std::endl;
				return false;
			}
		}

		//4. height
		//if(p_location.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_text_resource SET height =") +
				std::string("'") + std::to_string(p_h) + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update height failed!" << std::endl;
				return false;
			}
		}
		
		//5. description
		if(p_des.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_text_resource SET description =") +
				std::string("'") + p_des + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update description failed!" << std::endl;
				return false;
			}
		}

		//6. font
		if(p_font.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_text_resource SET font =") +
				std::string("'") + p_font + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update font failed!" << std::endl;
				return false;
			}
		}

		//6. fontweight
		if(p_wfontw.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_text_resource SET fontw =") +
				std::string("'") + p_wfontw + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update font weight failed!" << std::endl;
				return false;
			}
		}

		//7. font size
		//if(p_fontz.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_text_resource SET fonts =") +
				std::string("'") + std::to_string(p_fontz) + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update font size failed!" << std::endl;
				return false;
			}
		}

		return true;
	};

}