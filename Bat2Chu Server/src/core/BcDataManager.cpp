/*
 * BcDataManager.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: binhdu
 */

#include "BcDataManager.h"

BcDataManager::BcDataManager()
{
	// TODO Auto-generated constructor stub
	mDA = new DAL::DataAccess();

	TBImages = new BLL::Images(mDA);
	TBUsers = new BLL::Users(mDA) ;
}

BcDataManager::BcDataManager(std::string pHost, std::string pUser, std::string pPassword, std::string pDatabase)
{
	// TODO Auto-generated constructor stub
	mDA = new DAL::DataAccess(pHost,pUser,pPassword,pDatabase);

	TBImages = new BLL::Images(mDA);
	TBUsers = new BLL::Users(mDA) ;
}

BcDataManager::~BcDataManager()
{
	// TODO Auto-generated destructor stub
	if(mDA)
	{
		delete mDA;
		mDA = NULL;
	}

	if(TBImages)
	{
		delete TBImages;
		TBImages = NULL ;
	}

	if(TBUsers)
	{
		delete TBUsers;
		TBUsers = NULL ;
	}
}


void BcDataManager::SetDAL(DAL::DataAccess* pDa)
{
	mDA = pDa ;
}

