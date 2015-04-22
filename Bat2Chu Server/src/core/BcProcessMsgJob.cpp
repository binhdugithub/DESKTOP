/*
 * BcProcessMsgJob.cpp
 *
 *  Created on: Jul 12, 2014
 *      Author: binhdu
 */

#include "BcProcessMsgJob.h"
#include "../database/BLL/Images.h"
#include <netinet/in.h>

#include <stdlib.h>


BcProcessMsgJob::BcProcessMsgJob():
		mNetInterface(NULL),
		mDataManager(NULL)
{
	// TODO Auto-generated constructor stub
	//bcs = NULL;
	//mMysqlConn = NULL;
}

BcProcessMsgJob::BcProcessMsgJob(BcNetworkInterfaceJob* pBcs):
		mNetInterface(pBcs),
		mDataManager(NULL)
{
	//bcs = pBcs ;
	//mMysqlConn = NULL ;
};


BcProcessMsgJob::~BcProcessMsgJob()
{
	// TODO Auto-generated destructor stub
	std::cout << __FILE__ << " (" << __LINE__ << " ) [~BcProcessMsgJob] job :" << this  << std::endl;
	mDataManager = NULL;
	mNetInterface = NULL;

}

void BcProcessMsgJob::SetDataManager(BcDataManager* pDaMng)
{
	mDataManager = pDaMng;
}


bool BcProcessMsgJob::DoJob()
{
	if(!isRunningFlag)
		return false;

	if(mNetInterface == NULL)
	{
		ThreadManager::getSingletonPtr()->PostEventRemoveJob(this);
		return false ;
	}

	const char* msg = mNetInterface->PopMsg();

	if(msg == NULL)
	{
		return false;
	}
	else
	{
		ProcessMsg(msg);
		return true;
	}

	return false;
}


void BcProcessMsgJob::ProcessMsg(const char* msg)
{
	std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "Entry point !" << std::endl;

	if(msg == NULL)
	{
		std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << " Message is null !" << std::endl;
		return ;
	}

	uint32_t MsgTypeTemp = msg[0] | (msg[1]<<8) | (msg[2]<<16) | (msg[3]<<24);
	uint32_t MsgType = ntohl(MsgTypeTemp) ;

	switch(MsgType)
	{
		case Msg::MSG_REQ :
		{
			ProcessRequestMsg(msg + sizeof(MsgType));
			break;
		}

		case Msg::MSG_RES :
		{
			ProcessResponseMsg(msg + sizeof(MsgType));
			break;
		}
		default:
		{
			std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "Type of MsgTypeTemp :" << MsgTypeTemp << std::endl;
			std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "Type of MsgType :" << MsgType << std::endl;
			DoUnknowMsg(msg+ sizeof(MsgType));
			break;
		}

	}//end switch header

};

void BcProcessMsgJob::ProcessRequestMsg(const char* pMsg)
{
	uint32_t MsgReqType = pMsg[0] | (pMsg[1]<<8) | (pMsg[2]<<16) | (pMsg[3]<<24);
	MsgReqType = ntohl(MsgReqType) ;

	switch(MsgReqType)
	{
		case MsgRequest::MSG_REQ_CONNECT:
		{

			break;
		}
		case MsgRequest::MSG_REQ_CREATE_USER:
		{
			DoRequestCreateUser();
			break;
		}
		case MsgRequest::MSG_REQ_GET_IMAGE:
		{
			DoRequestGetImage(pMsg + sizeof(MsgReqType));
			break;
		}
		case MsgRequest::MSG_REQ_NEXT_LEVEL:
		{
			DoRequestNextLevel(pMsg + sizeof(MsgReqType));
			break;
		}
		case MsgRequest::MSG_REQ_UPDATE_USERNAME:
		{

			break;
		}
		case MsgRequest::MSG_REQ_UPDATE_FACEBOOK:
		{

			break;
		}
		default:
		{

			break;
		}

	}
}

void BcProcessMsgJob::ProcessResponseMsg(const char* pMsg)
{

}


void BcProcessMsgJob::AddBytes2Buffer(const void* _src, uint32_t _leng, unsigned char _dest[], uint32_t& _offset)
{
	const char* src = (const char*)_src;
	for(int i=0; i< _leng; i++)
	{
		_dest[i+_offset] = src[i];
	}

	_offset += _leng;
}

bool BcProcessMsgJob::DoRequestCreateUser()
{

	int idUser = mDataManager->TBUsers->CreateNewUser();


	if(idUser > 0)
	{
		std::cout << __FILE__ << " (" << __LINE__ << " ) [" << __func__<< "] Send idUser :" << idUser << std::endl;
		uint32_t MsgType = htonl(Msg::MSG_RES);
		uint32_t MsgResType = htonl(MsgResponseACK::MSG_RES_CREATE_USER_OK);
		idUser = htonl(idUser);

		uint32_t lngMsg = sizeof(MsgType) + sizeof(MsgResType) + sizeof(idUser);
		uint32_t offset = 0;
		unsigned char buffer[lngMsg];
		uint32_t lngMsg_temp = htonl(lngMsg);

		AddBytes2Buffer(&lngMsg_temp, sizeof(lngMsg_temp), buffer, offset);
		AddBytes2Buffer(&MsgType, sizeof(MsgType), buffer, offset);
		AddBytes2Buffer(&MsgResType, sizeof(MsgResType), buffer, offset);
		AddBytes2Buffer(&idUser, sizeof(idUser), buffer, offset);

		mNetInterface->Write(buffer, offset) ;

		return true;
	}
	else
	{
		std::cout << __FILE__ << " (" << __LINE__ << " ) [" << __func__<< "Reject idUser :" << idUser << std::endl;
		uint32_t MsgType = htonl(Msg::MSG_RES);
		uint32_t MsgResType = htonl(MsgResponseACK::MSG_RES_CREATE_USER_FAIL);
		idUser = htonl(idUser);



		uint32_t lngMsg = sizeof(MsgType) + sizeof(MsgResType) + sizeof(idUser);
		uint32_t offset = 0;
		unsigned char buffer[lngMsg];
		uint32_t lngMsg_temp = htonl(lngMsg);

		AddBytes2Buffer(&lngMsg_temp, sizeof(lngMsg_temp), buffer, offset);
		AddBytes2Buffer(&MsgType, sizeof(MsgType), buffer, offset);
		AddBytes2Buffer(&MsgResType, sizeof(MsgResType), buffer, offset);
		AddBytes2Buffer(&idUser, sizeof(idUser), buffer, offset);

		mNetInterface->Write(buffer, offset) ;

		return true;
	}

	return false;
}

bool BcProcessMsgJob::DoRequestNextLevel(const char* msg)
{

	if(msg == NULL)
		return false;

	uint32_t userID = msg[0] | msg[1]<<8|msg[2]<<16|msg[3]<<24 ;
	userID = ntohl(userID);

	if(userID < 0)
		return false;

	//update to database
	mDataManager->TBUsers->UpdateLevelAndRuby(userID) ;

	//get image from Images
	BLL::ImageObject *MyImage = mDataManager->TBImages->GetImage(userID);

	if(MyImage == NULL)
	{
		std::cout << __FILE__ << " (" << __LINE__ << " ) [" << __func__<< "Hết dữ liệu " << std::endl;
		uint32_t MsgType = htonl(Msg::MSG_RES);
		uint32_t MsgResType = htonl(MsgResponseACK::MSG_RES_END_OF_LEVEL);

		uint32_t lngMsg = sizeof(MsgType) + sizeof(MsgResType) ;
		uint32_t offset = 0;
		unsigned char buffer[lngMsg];
		uint32_t lngMsg_temp = htonl(lngMsg);

		AddBytes2Buffer(&lngMsg_temp, sizeof(lngMsg_temp), buffer, offset);
		AddBytes2Buffer(&MsgType, sizeof(MsgType), buffer, offset);
		AddBytes2Buffer(&MsgResType, sizeof(MsgResType), buffer, offset);

		mNetInterface->Write(buffer, offset) ;

		return false;
	}

	FILE *fptr;
	std::string fullPathImage = mNetInterface->mRootPathImage + std::string("/") + MyImage->mUrl;

	fptr = fopen(fullPathImage.c_str(),"r");
	if(fptr == NULL)
	{
		std::cout << __FILE__ << " (" << __LINE__ << " ) [" << __func__<<"] Open image " << fullPathImage << " fail" << std::endl;
		return false;
	}
	else
	{

		fseek(fptr,0, SEEK_END) ;
		long int sizeFile = ftell(fptr) ;
		fseek(fptr,0,SEEK_SET) ;

		if(sizeFile <= 0)
		{
			std::cout << __FILE__ << " (" << __LINE__ << " ) [" << __func__<<"] Image " << MyImage->mUrl << " so small" << std::endl;
			//return false;
		}
		else
		{
			char *imageBuff = new char[sizeFile] ;
			int sizeImage = fread(imageBuff, sizeof(char) , sizeFile, fptr) ;

			if(sizeImage <= 0)
			{
				std::cout << __FILE__ << " (" << __LINE__ << " ) [" << __func__<<"] Image " << MyImage->mUrl << " read file fail" << std::endl;
			}
			else
			{

				std::cout << "------------------------- Send Image ----------------------------------" << std::endl ;
				uint32_t MsgType = htonl(Msg::MSG_RES);
				uint32_t MsgResType = htonl(MsgResponseACK::MSG_RES_NEXT_LEVEL_OK);
				uint32_t lngEnResult = htonl(MyImage->mEnResult.length());
				uint32_t lngVnResult = htonl(MyImage->mVnResult.length());
				uint32_t lngImage = htonl(sizeImage);

				uint32_t lngMsg =sizeof(MsgType)+ sizeof(MsgResType)+
							sizeof(lngEnResult)+ MyImage->mEnResult.length() +
							sizeof(lngVnResult)+ MyImage->mVnResult.length() +
							sizeof(lngImage)+ sizeImage ;
				std::cout << __FILE__ << " (" << __LINE__ << " ) [" << __func__<<"] Will send : " << lngMsg << " bytes" << std::endl;

				uint32_t offset = 0;
				unsigned char buffer[lngMsg];
				uint32_t lngMsg_temp = htonl(lngMsg);

				AddBytes2Buffer(&lngMsg_temp, sizeof(lngMsg_temp), buffer, offset);
				AddBytes2Buffer(&MsgType, sizeof(MsgType), buffer, offset);
				AddBytes2Buffer(&MsgResType, sizeof(MsgResType), buffer, offset);
				AddBytes2Buffer(&lngEnResult, sizeof(lngEnResult), buffer, offset);
				AddBytes2Buffer(MyImage->mEnResult.c_str(), MyImage->mEnResult.length(), buffer, offset);
				AddBytes2Buffer(&lngVnResult, sizeof(lngVnResult), buffer, offset);
				AddBytes2Buffer(MyImage->mVnResult.c_str(), MyImage->mVnResult.length(), buffer, offset);
				AddBytes2Buffer(&lngImage, sizeof(lngImage), buffer, offset);
				AddBytes2Buffer(imageBuff, sizeImage, buffer, offset);

				mNetInterface->Write(buffer, offset) ;

			}

			delete imageBuff;
			imageBuff = NULL;
		}
	}

	//close file
	fclose(fptr) ;

	return true ;
}


bool BcProcessMsgJob::DoRequestGetImage(const char* msg)
{
	if(msg == NULL)
			return false;

	uint32_t userID = msg[0] | msg[1]<<8|msg[2]<<16|msg[3]<<24 ;
	userID = ntohl(userID);

	if(userID < 0)
		return false;
	//get image from Images
	BLL::ImageObject *MyImage = mDataManager->TBImages->GetImage(userID);

	if(MyImage == NULL)
	{
		std::cout << __FILE__ << " (" << __LINE__ << " ) [" << __func__<< "Hết dữ liệu " << std::endl;
		uint32_t MsgType = htonl(Msg::MSG_RES);
		uint32_t MsgResType = htonl(MsgResponseACK::MSG_RES_END_OF_LEVEL);

		uint32_t lngMsg = sizeof(MsgType) + sizeof(MsgResType) ;
		uint32_t offset = 0;
		unsigned char buffer[lngMsg];
		uint32_t lngMsg_temp = htonl(lngMsg);

		AddBytes2Buffer(&lngMsg_temp, sizeof(lngMsg_temp), buffer, offset);
		AddBytes2Buffer(&MsgType, sizeof(MsgType), buffer, offset);
		AddBytes2Buffer(&MsgResType, sizeof(MsgResType), buffer, offset);

		mNetInterface->Write(buffer, offset) ;

		return false;
	}

	FILE *fptr;
	std::string fullPathImage = mNetInterface->mRootPathImage + std::string("/") + MyImage->mUrl;

	fptr = fopen(fullPathImage.c_str(),"r");
	if(fptr == NULL)
	{
		std::cout << __FILE__ << " (" << __LINE__ << " ) [" << __func__<<"] Open image " << fullPathImage << " fail" << std::endl;
		return false;
	}
	else
	{

		fseek(fptr,0, SEEK_END) ;
		long int sizeFile = ftell(fptr) ;
		fseek(fptr,0,SEEK_SET) ;

		if(sizeFile <= 0)
		{
			std::cout << __FILE__ << " (" << __LINE__ << " ) [" << __func__<<"] Image " << MyImage->mUrl << " so small" << std::endl;
			//return false;
		}
		else
		{
			char *imageBuff = new char[sizeFile] ;
			int sizeImage = fread(imageBuff, sizeof(char) , sizeFile, fptr) ;

			if(sizeImage <= 0)
			{
				std::cout << __FILE__ << " (" << __LINE__ << " ) [" << __func__<<"] Image " << MyImage->mUrl << " read file fail" << std::endl;
			}
			else
			{

				std::cout << "------------------------- Send Image ----------------------------------" << std::endl ;
				uint32_t MsgType = htonl(Msg::MSG_RES);
				uint32_t MsgResType = htonl(MsgResponseACK::MSG_RES_NEXT_LEVEL_OK);
				uint32_t lngEnResult = htonl(MyImage->mEnResult.length());
				uint32_t lngVnResult = htonl(MyImage->mVnResult.length());
				uint32_t lngImage = htonl(sizeImage);

				uint32_t lngMsg =sizeof(MsgType)+ sizeof(MsgResType)+
							sizeof(lngEnResult)+ MyImage->mEnResult.length() +
							sizeof(lngVnResult)+ MyImage->mVnResult.length() +
							sizeof(lngImage)+ sizeImage ;
				std::cout << __FILE__ << " (" << __LINE__ << " ) [" << __func__<<"] Will send : " << lngMsg << " bytes" << std::endl;

				uint32_t offset = 0;
				unsigned char buffer[lngMsg];
				uint32_t lngMsg_temp = htonl(lngMsg);

				AddBytes2Buffer(&lngMsg_temp, sizeof(lngMsg_temp), buffer, offset);
				AddBytes2Buffer(&MsgType, sizeof(MsgType), buffer, offset);
				AddBytes2Buffer(&MsgResType, sizeof(MsgResType), buffer, offset);
				AddBytes2Buffer(&lngEnResult, sizeof(lngEnResult), buffer, offset);
				AddBytes2Buffer(MyImage->mEnResult.c_str(), MyImage->mEnResult.length(), buffer, offset);
				AddBytes2Buffer(&lngVnResult, sizeof(lngVnResult), buffer, offset);
				AddBytes2Buffer(MyImage->mVnResult.c_str(), MyImage->mVnResult.length(), buffer, offset);
				AddBytes2Buffer(&lngImage, sizeof(lngImage), buffer, offset);
				AddBytes2Buffer(imageBuff, sizeImage, buffer, offset);

				mNetInterface->Write(buffer, offset) ;

			}

			delete imageBuff;
			imageBuff = NULL;
		}
	}

	//close file
	fclose(fptr) ;

	return true ;
}


void BcProcessMsgJob::DoUnknowMsg(const char* pMsg)
{

	if(strlen(pMsg) <=  0)
		return ;

	std::cout << __FILE__ << " in function " << __func__ << " on line : " << __LINE__ << " msg: " <<  pMsg << std::endl;

}



