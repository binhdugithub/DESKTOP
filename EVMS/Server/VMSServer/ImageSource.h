#pragma once
#include "table.h"
namespace BLL
{
	class ImageSource :
		public Table
	{
	public:
		ImageSource(void);
		virtual ~ImageSource(void);
	public:
		virtual sql::ResultSet* SelectAll();
		virtual sql::ResultSet* SelectWhere(int);
		bool Insert(std::string p_link);
		bool Delete(int p_id);
		bool Update(int p_id, std::string p_link);
	};
}
