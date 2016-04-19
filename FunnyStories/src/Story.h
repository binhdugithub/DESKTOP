/*
 * Story.h
 *
 *  Created on: Dec 15, 2015
 *      Author: root
 */

#ifndef SRC_STORY_H_
#define SRC_STORY_H_

#include "DataAccess.h"
#include "MyLogger.h"

#include <iostream>

namespace BLL
{

class Story
{
private:
	DAL::DataAccess *m_DA;
public:
	Story();
	virtual ~Story();

	sql::ResultSet* SelectAll();
	sql::ResultSet* SelectList(int p_idstart, int p_limit);
	sql::ResultSet* SelectWhere(int p_id);
	bool Insert(
			std::string p_title,
			std::string p_content,
			std::string p_image,
			std::string p_audio
		);

	bool Delete(int p_id);
	bool Update(
			int 		p_id,
			std::string p_title,
			std::string p_content,
			std::string p_image,
			std::string p_audio,
			float 		p_rate);
};
}
#endif /* SRC_STORY_H_ */
