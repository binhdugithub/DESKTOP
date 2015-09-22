#pragma once
#include "table.h"

namespace BLL
{
	class TextSource :
		public Table
	{
	public:
		TextSource(void);
		virtual ~TextSource(void);
	public:
		virtual sql::ResultSet* SelectAll();
		virtual sql::ResultSet* Select(int p_id);
		bool Insert(
			float p_x,
			float p_y,
			float p_w,
			float p_h,
			std::string p_font,
			std::string p_wfontw,
			float p_fontz,
			std::string p_des);
		bool Delete(int p_id);
		
		bool Update(
			int p_id,
			float p_x,
			float p_y,
			float p_w,
			float p_h,
			std::string p_font,
			std::string p_wfontw,
			float p_fontz,
			std::string p_des);
	};
}
