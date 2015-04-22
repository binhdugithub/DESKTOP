/*
 * BcMsg.cpp
 *
 *  Created on: Jul 11, 2014
 *      Author: binhdu
 */

#include "BcMsg.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <string.h>


BcMsg::BcMsg()
{
	// TODO Auto-generated constructor stub
	mData = NULL;

}

BcMsg::BcMsg(std::string pMsg)
{
	// TODO Auto-generated constructor stub
	this->mTag = -1 ;
	//CreateRcvMsg(pMsg);

}

BcMsg::BcMsg(int pResOrReq, int pType, void* pData,int pLeng)
{
	this->mTag = -1;
	CreateSendMsg(pResOrReq, pType, pData, pLeng) ;
}
/*
std::vector<std::string> BcMsg::SplitStringMsg(std::string pMsg, char pCharToken)
{
	//std::cout <<"String message:[" << pMsg <<"] token follow :[" << pCharToken << "]" << std::endl;

	std::cout << __FILE__<< "(" << __LINE__ << ") [SplitStringMsg] strMsg :" << pMsg << std::endl;
	std::vector<std::string> tokenMsg ;
	int lengMsg = pMsg.size();

	int iStart = 0 ;
	int iEnd = -1 ;
	for(int i = 0 ; i < lengMsg ; i++)
	{
		if(i == lengMsg -1)
		{
			if(iStart < i)
			{
				iEnd = i;
				std::string token = pMsg.substr(iStart,iEnd - iStart);
				tokenMsg.push_back(token);
			}

			break;
		}
		else if(pMsg[i] == pCharToken)
		{

			iEnd = i;
			if(iStart == iEnd)
			{
				iStart = i + 1 ;
				continue;
			}


			std::string token = pMsg.substr(iStart,iEnd - iStart);
			tokenMsg.push_back(token);

			iStart = i + 1 ;
			i++;
			continue;
		}
	}

	return tokenMsg ;
};

*/

void BcMsg::CreateSendMsg(int pResOrRep, int pType, void* pData, int pLeng)
{
	this->mTag = BcMsg::Class_BcResponseNextLevel ;

	BcResponseNextLevel *data = new BcResponseNextLevel(pResOrRep,
														pType,
														pData,
														pLeng);



	this->mData = (void*)data;

}


BcMsg::~BcMsg()
{
	// TODO Auto-generated destructor stub
	if(mData)
	{
		//delete mBuffer ;
		mData = NULL ;
	}
}


int BcMsg::GetTag()
{
	return mTag ;
}

void* BcMsg::GetBuffer()
{
	return mData;
};


//class BcRequestNextLevel
BcRequestNextLevel::BcRequestNextLevel()
{
	mLevel = -1;
	mScore = -1;

};

BcRequestNextLevel::BcRequestNextLevel(int pLevel,int pScore)
{
	mLevel = pLevel;
	mScore = pScore ;
}

BcRequestNextLevel::~BcRequestNextLevel()
{
	mLevel = -1;
	mScore = -1;

};

//class BcResponseNextLevel
BcResponseNextLevel::BcResponseNextLevel()
{

};


BcResponseNextLevel::BcResponseNextLevel(int pResOrRep,int pType, void* pImage ,int pLeng)
{
	this->mHeader =std::to_string(pResOrRep) +  std::string("|") \
				 + std::to_string(pType)     +   std::string("|") ;

	this->mImage = pImage ;

	this->mLeng = this->mHeader.length() + pLeng ;

};


BcResponseNextLevel:: ~BcResponseNextLevel()
{

};
