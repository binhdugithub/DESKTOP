#pragma once
#include "table.h"
#include "LogFile.h"

namespace BLL
{

	class Role :
		public Table
	{
	public:
		Role(void);
		virtual ~Role(void);

	public:
		virtual sql::ResultSet* SelectAll();
		bool Insert(int, std::string);
		bool Delete(int);
		bool Update(int, std::string);
	};

}//end namespace BLL
