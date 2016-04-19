/*
 * App.h
 *
 *  Created on: Mar 10, 2016
 *      Author: root
 */

#ifndef SRC_APP_H_
#define SRC_APP_H_

#include "DataAccess.h"
#include "MyLogger.h"
#include <iostream>

namespace BLL
{

class App
{
private:
	DAL::DataAccess *m_DA;
public:
	App();
	virtual ~App();

	sql::ResultSet* SelectAll();
	sql::ResultSet* SelectList(int p_idstart);
};

}

#endif /* SRC_APP_H_ */
