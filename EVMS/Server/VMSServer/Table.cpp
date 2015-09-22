/*
 * Table.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: binhdu
 */

#include "stdafx.h"
#include "Table.h"


namespace BLL {

	Table::Table()
	{
		mDA = new DAL::DataAccess();
	}


	Table::~Table()
	{
		if (mDA)
		{
			delete mDA;
			mDA = NULL;
		}
	}


	sql::ResultSet* Table::SelectAll()
	{


		return NULL;
	}


} /* namespace BLL */
