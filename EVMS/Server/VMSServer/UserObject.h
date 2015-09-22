#pragma once

#include "table.h"
namespace BLL
{

	class UserObject :
		public Table
	{
	public:
		UserObject(void);
		virtual ~UserObject(void);
	
	public:
		virtual sql::ResultSet* SelectAll();
		bool Insert(std::string, int);
		bool Delete(std::string);
		//bool Update(std::string, int);

	};
}

