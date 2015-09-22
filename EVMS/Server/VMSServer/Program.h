#pragma once
#include "table.h"

namespace BLL
{
	class Program :
		public Table
	{
	public:
		Program(void);
		virtual ~Program(void);

		virtual sql::ResultSet* SelectAll();
		sql::ResultSet* Select(int);
		bool Insert(std::string, int, std::string, float, float);
		bool Delete(int);
		bool Update(int, std::string, int, std::string, float, float);
	};

}
