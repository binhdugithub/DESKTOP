/*
 * BcThreadObject.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: binhdu
 */

#include "BcThreadObject.h"
#include "BcProcessMsgJob.h"

BcThreadObject::BcThreadObject()
{
	// TODO Auto-generated constructor stub
	mDataManager = new  BcDataManager() ;
}


BcThreadObject::BcThreadObject(std::string pHost, std::string pUser, std::string pPassword, std::string pDatabase)
{
	mDataManager = new  BcDataManager(pHost,pUser,pPassword,pDatabase) ;
}


BcThreadObject::~BcThreadObject()
{
	// TODO Auto-generated destructor stub
	if(mDataManager)
	{
		delete mDataManager ;
		mDataManager = NULL ;
	}
}

bool BcThreadObject::AddJob(ThreadJob* pJob)
{
	if(ThreadObject::AddJob(pJob))
	{
		BcProcessMsgJob *Job = dynamic_cast<BcProcessMsgJob*>(pJob) ;
		if(Job != 0 && Job != NULL)
		{
			Job->SetDataManager(mDataManager) ;
			//std::cout << __FILE__ << " (" << __LINE__ << " ) [AddJob] add mDataManager" <<  std::endl;
			return true;
		}
	}

	return false;
}
