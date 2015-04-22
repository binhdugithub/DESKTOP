#include <iostream>
#include <vector>

#include "threadpool/ThreadManager.h"
#include "threadpool/ThreadJob.h"
#include "threadpool/HandleThreadPoolEvent.h"
#include "core/BcNetworkInterfaceJob.h"
#include "core/BcThreadObject.h"
#include "../tinyxml/tinyxml.h"

#define FILE_CONFIG "./Resources/config.xml"

typedef struct
{
	std::string ip ;
	unsigned short port ;
	bool heartbeat ;
	bool timeout ;
}NetInf, *PNetInf ;

typedef struct
{
	std::string host;
	std::string user;
	std::string password;
	std::string databaseName;
	std::string rootPathImage;
}DatabaseInf, *PDatabaseInf;


typedef struct
{
	std::string path;
	std::string fileName ;
}LogInf, *PLogInf;


bool readFileConfig(std::string , PNetInf, PDatabaseInf, PLogInf);

int main()
{
	std::cout << "------------------Start Server---------------" << std::endl;
	std::cout << "----Read file config----" << std::endl;

	PNetInf netInf = new NetInf();
	PDatabaseInf dataInf = new DatabaseInf();
	PLogInf logInf = new LogInf();

	bool res = readFileConfig(FILE_CONFIG, netInf, dataInf, logInf) ;

	if(res == false)
	{
		std::cout << "Load file config fail !!!!" << std::endl;
		return 0;
	}

	BcNetworkInterfaceJob *Service = new BcNetworkInterfaceJob(dataInf->rootPathImage);
	res = Service->StartListen(netInf->port);

	if(!res)
	{
		if(Service)
		{
			delete Service;
			Service = NULL ;
		}


		return 0;
	}


	//threadpool init
	int lCpu = ThreadManager::getSingletonPtr()->NumCPU();
	std::cout << __FILE__ << __LINE__ << " Value of NumCPU :" << lCpu << std::endl;
	if(lCpu <= 0)
	{
		return false ;
	}

	for(int i= 0; i < lCpu ; i++)
	{
		BcThreadObject *Obj = new BcThreadObject(
				dataInf->host,
				dataInf->user,
				dataInf->password,
				dataInf->databaseName);

		ThreadManager::getSingletonPtr()->AddObject(Obj);
	}


	//add the first job of network
	ThreadManager::getSingletonPtr()->AddJob(Service);

	while(1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	return 0;
}

bool readFileConfig(std::string pPath, PNetInf pNet, PDatabaseInf pData, PLogInf pLog)
{
	TiXmlDocument doc(FILE_CONFIG) ;
	if(!doc.LoadFile())
	{
		doc.Clear();
		return false ;
	}

	//load file config successful ad read information!!!
	TiXmlElement *eRoot = doc.RootElement(); // Bat2Chu
	TiXmlElement *eSetting = eRoot->FirstChildElement("Setting") ;

	TiXmlElement *eNetwork = eSetting->FirstChildElement("network") ;
	TiXmlElement *eDatabase = eSetting->FirstChildElement("database");
	TiXmlElement *eLog = eSetting->FirstChildElement("log");

	//get network information
	pNet->port = atoi(eNetwork->FirstChildElement("port")->FirstChild()->Value()) ;
	const char *bHeartbeatString =eNetwork->FirstChildElement("heartbeat")->Attribute("enable") ;
	if(strcmp(bHeartbeatString, "yes") == 0)
	{
		pNet->heartbeat = true;

		const char*iTimeoutString = eNetwork->FirstChildElement("heartbeat")->Attribute("timeout") ;
		pNet->timeout = atoi(iTimeoutString) ;

	}
	else
	{
		pNet->heartbeat = false;
	}

	//get database information
	pData->host = std::string(eDatabase->Attribute("host")) ;
	pData->user = std::string(eDatabase->Attribute("user")) ;
	pData->password = std::string(eDatabase->Attribute("password")) ;
	pData->databaseName = std::string(eDatabase->Attribute("database_name")) ;
	pData->rootPathImage = std::string(eDatabase->Attribute("root_path_image")) ;

	//get log information
	pLog->fileName = std::string(eLog->Attribute("file"));
	pLog->path = std::string(eLog->Attribute("path")) ;


	doc.Clear();
	return true;

}
