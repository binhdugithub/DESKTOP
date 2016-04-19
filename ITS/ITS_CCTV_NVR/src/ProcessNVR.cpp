/*
( * ProcessNVR.cpp
 *
 *  Created on: 17 Jun, 2014
 *      Author: cuonglm
 */

#include "ProcessNVR.h"


#define NO_ERROR 0
#define ERROR_USER_PASS 401
#define ERROR_ERROR_URL 404
#define ERROR_IP_SERVER -115
#define ERROR_IP_INTER_SERVER 500

ProcessNVR::ProcessNVR() {

}

ProcessNVR::~ProcessNVR()
{
	pthread_join(mThreadDB, NULL);
	LOG_INFO("Sucess Joint thread ThreadDB");

	pthread_join(mThreadMonitor, NULL);
	LOG_INFO("Sucess Joint thread MonitorHDD");

}

void ProcessNVR::start()
{
	std::cout << "Start doWorkDB" << std::endl;
	if (pthread_create(&mThreadDB, NULL, doWorkDB, (void*) this))
	{
		LOG_ERROR("Init Thread doWorkDB False, return");
		return;
	}

	//auto reload NVR
	std::vector<std::vector<std::string>> l_arrayCam = DBInterface::GetSingleton()->GetRecordedCam();
	int l_leng = l_arrayCam.size();
	std::cout << "Start auto reload:" << l_leng << std::endl;
	for (int i = 0; i < l_leng; i++)
	{
		std::vector<std::string> l_cam = l_arrayCam[i];
		char *l_videoid = (char*) l_cam[0].c_str();
		char *l_videourl = (char*) l_cam[1].c_str();
		int l_mode = std::stoi(l_cam[2]);
		int l_duration = std::stoi(l_cam[3]);
		AutoRecord(l_videoid, l_videourl, l_mode, l_duration);
	}

	std::cout << "Start monitorHDD" << std::endl;
	if (pthread_create(&mThreadMonitor, NULL, monitorHDD, (void*) this))
	{
		LOG_ERROR("Init Thread MonitorHDD False, return");
		return;
	}

	std::cout << "Start loop" << std::endl;
	ManagerRecorder::GetSingleton()->StartMain();



	int port = Configuration::GetSingleton()->getPortListen();
	textLog = "Start listen Soap ";
	LOG_INFO(textLog <<":" << port);
	std::cout << "Start listen Soap:"<< port << std::endl;
	nvrService nvrserver;

	for (int i = 0; i < 10; i++)
	{
		int l_ret = nvrserver.run(port);
		if (l_ret != SOAP_OK)
		{
			std::cout << "start Soap error:" << l_ret << std::endl;
			LOG_ERROR("Start Soap Error:" << l_ret);
			sleep(10);
			if (i == 9)
			{
				isExit = true;
				return;
			}

		}
		else
		{
			LOG_INFO("Start Soap Sucess");
			break;
		}
	}


}


void* ProcessNVR::doWorkDB(void* pVoid)
{
	while (isExit == false)
	{
		if (getSizeDBQueue() > 0)
		{
			std:: string l_query = getDBQueue();
			if (l_query != "")
			{
				if(l_query.find("INSERT") != std::string::npos ||
					l_query.find("insert") != std::string::npos)
				{
					if(!DBInterface::GetSingleton()->Insert(l_query))
					{
						std::cout << "Put querry insert again" << std::endl;
						LOG_ERROR("Put querry insert again");
						pushDBQueue(l_query);
					}
				}
				else if (l_query.find("UPDATE") != std::string::npos ||
						l_query.find("update") != std::string::npos)
				{
					if(!DBInterface::GetSingleton()->Update(l_query))
					{
						std::cout << "Put querry update again" << std::endl;
						LOG_ERROR("Put querry update again");
						insertFirstDBQueue(l_query);
					}
				}
				else if (l_query.find("DELETE") != std::string::npos ||
						l_query.find("delete") != std::string::npos)
				{
					if(!DBInterface::GetSingleton()->Delete(l_query))
					{
						std::cout << "Put querry delete again" << std::endl;
						LOG_ERROR("Put querry delete again");
						pushDBQueue(l_query);
					}
				}
				else
				{
					std::cout << "I don't know what kind of querry:" << l_query << std::endl;
					LOG_ERROR("I dont know what kind of querry: " << l_query);
				}
			}
		}

		usleep(10);
	}
}

unsigned long ProcessNVR::checkFreeDiskSpace(std::string directory)
{
	struct statvfs diskData;
	statvfs(directory.c_str(), &diskData);
	unsigned long available = (unsigned long long) diskData.f_bavail
			* (unsigned long long) diskData.f_bsize / (1024 * 1024 * 1024);
	return available;
}

int ProcessNVR::getItemOfDir(std::string dir, vector<std::string> &files)
{
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(dir.c_str())) == NULL)
	{
		LOG_ERROR("Error " <<std::to_string(errno)<<" opening "<<dir);
		return errno;
	}

	while ((dirp = readdir(dp)) != NULL)
	{
		if (dirp->d_name[0] != '.' && dirp->d_name[0] != '..'
				&& dirp->d_name[strlen(dirp->d_name) - 1] != '~')
			files.push_back(std::string(dirp->d_name));
	}

	closedir(dp);
	return 0;
}


unsigned long ProcessNVR::getDateCreatFolder(std::string path)
{
	struct stat t_stat;
	stat(path.c_str(), &t_stat);
	struct tm * timeinfo = localtime(&t_stat.st_ctime); // or gmtime() depending on what you want
	unsigned long date;
	//printf("File time and date: %s", asctime(timeinfo));
	date = timeinfo->tm_mday + (timeinfo->tm_mon + 1) * 30
			+ (timeinfo->tm_year + 1990) * 365;
	return date;
}

void ProcessNVR::DeleteFile(vector<std::string> l_file)
{
	std::string l_camName = l_file[0];
	std::string l_fileName = l_file[1];
	std::string l_time = l_file[2];
	std::string l_rootPathVideo = Configuration::GetSingleton()->getFilePath();

	if(l_fileName.length() <= 0 || l_time.length() <= 0)
	{
		std::cout << "Cannot delete file cuz leng <= 0" << std::endl;
		LOG_ERROR("Cannot tdelete file cuz leng <= 0");

		return;
	}

	struct tm tm;
	strptime(l_time.c_str(), "%Y-%m-%d %H:%M", &tm);

	std::string mon, day, h, m, s;

	if((tm.tm_mon + 1) < 10)
		mon = "0" + std::to_string(tm.tm_mon + 1);
	else
		mon = std::to_string(tm.tm_mon + 1);

	if(tm.tm_mday < 10)
		day = "0" + std::to_string(tm.tm_mday);
	else
		day = std::to_string(tm.tm_mday);
	if(tm.tm_hour<10)
		h = "0" + std::to_string(tm.tm_hour);
	else
		h = std::to_string(tm.tm_hour);

	//std::string l_temp = tm.
	std::string l_fullPathVideo;
	l_fullPathVideo = l_rootPathVideo +"/" + l_camName + "/"+std::to_string(tm.tm_year + 1900) + "/" + mon + "/"+  day + "/"+ h +"/" + l_fileName;

	try
	{
		std::string l_cmd2DeleteFile = "rm -f " + l_fullPathVideo;
		int l_value = system(l_cmd2DeleteFile.c_str());
		if(l_value == 0)
		{
			std::string l_query = "DELETE from its_nvr_videostorage WHERE filename = '"+ l_fileName + "';";
			pushDBQueue(l_query);
		}
		else
		{
			std::cout <<"-----> Delete file failed:" << l_value << std::endl;
			LOG_ERROR("------Delete file failed:" << l_value);
		}
	}
	catch(exception &ex)
	{
		std::cout << "Exception delete file:" << ex.what() << std::endl;
		LOG_ERROR("Exception delete file: " << ex.what());
	}


	return;
}
void* ProcessNVR::monitorHDD(void* pVoid)
{
	ProcessNVR* pThis = (ProcessNVR*) pVoid;

	unsigned long spaceDisk;
	int mode = Configuration::GetSingleton()->getModeNVR();
	unsigned long minSpace = Configuration::GetSingleton()->getMinCapacity();
	std::string l_RootVideoPath = Configuration::GetSingleton()->getFilePath();
	while (isExit == false)
	{
		spaceDisk = checkFreeDiskSpace(l_RootVideoPath);
		if (spaceDisk < minSpace)
		{
			if (mode == 0)
			{
				//std::cout << "Don't enought disk for record --- close session" << std::endl;
				LOG_INFO("Don't enought disk for record----close session");
				continue;
			}

			if (mode == 1)
			{
				std::cout << "Space Disk befor delete: " << std::to_string(spaceDisk) << std::endl;
				LOG_INFO("Space Disk befor delete: " << std::to_string(spaceDisk));


				//binhngt
				std::vector<std::vector<std::string>> l_arrayFile = DBInterface::GetSingleton()->GetListFile2Delete(NUMBER_OF_FILE_2_DELETE);
				int l_leng = l_arrayFile.size();
				for (int i = 0; i < l_leng; i++)
				{
					std::vector<std::string> l_file = l_arrayFile[i];
					pThis->DeleteFile(l_file);

					sleep(1);
				}
			}
		}
		else
		{
			std::cout << "Free space = " << spaceDisk << std::endl;
			//LOG_INFO("Free sapce =" << spaceDisk);

			sleep(10);
		}

		sleep(1);
	}

	std::cout << "***************Out Monitor HDD***************" << std::endl;

	return NULL;
}
//



int nvrService::startrecord(char *p_id, char *p_url, int p_mode, int p_leng, struct result_status *result)
{
	std::cout << "+++++++++START_RECORD for ID: " << p_url << std::endl;

	if (p_leng < 10 || p_leng > 1800 || std::string(p_id) == ""
			|| std::string(p_id) == "\0"
			|| std::string(p_url) == ""
			|| std::string(p_url) == "\0")
	{
		std::cout << "Parametter SOAP failed" << std::endl;
		LOG_ERROR("Parametter SOAP failed");

		result->errorid = 6;
		std::string error = "error parameter";
		result->errordesc = (char*) error.c_str();
		LOG_INFO("--------RESPOND: error parameter");

		return SOAP_OK;
	}


	bool l_StartBool = ManagerRecorder::GetSingleton()->StartRecord(std::string(p_id), std::string(p_url), p_leng, p_mode);

	std::string l_desc;

	if (l_StartBool)
	{
		result->errorid = 0;
		l_desc = "sucessfull";
	}
	else
	{
		result->errorid = 0;
		l_desc = "The Camera has recorded";
		LOG_INFO("---------RESPOND:The Camera has recorded:");
	}

	result->errordesc = (char*) l_desc.c_str();


	return SOAP_OK;

}

void ProcessNVR::AutoRecord(char *p_id, char *p_url,int p_mode, int p_leng)
{
	textLog = "+++++++++START_AUTORECORD for ID: "
			+ std::string(p_id);
	textLog  = textLog + " \nURL:  " + std::string(p_url)
			+ "\n RecordMode: " + std::to_string(p_mode) +
			+ " \nDuration: "+ std::to_string(p_leng);

	LOG_INFO(textLog);
	std::cout << textLog.c_str() << std::endl;

	if (p_leng < 10 || p_leng > 1800
			|| std::string(p_id) == ""
			|| std::string(p_id) == "\0"
			|| std::string(p_url) == ""
			|| std::string(p_url) == "\0")
	{
		std::cout << "Parametter failed" << std::endl;
		return;
	}

	p_mode = RETRYRECORD;
	ManagerRecorder::GetSingleton()->StartRecord(std::string(p_id), std::string(p_url), p_leng, p_mode);

}

int nvrService::stoprecord(char *p_id, struct result_status *result)
{
	std::cout << "+++++++++STOPRECORD VideoID : " << p_id << std::endl;
	textLog = "+++++++++STOPRECORD VideoID  " + std::string(p_id);
	LOG_INFO(textLog);

	if (std::string(p_id) == "" || std::string(p_id) == "")
	{
		LOG_INFO("---------RESPOND : error parameter");
		result->errorid = 6;
		std::string error = "error parameter";
		result->errordesc = (char*) error.c_str();
		return SOAP_OK;
	}

	std::string l_desc;

	if(ManagerRecorder::GetSingleton()->StopRecord(std::string(p_id)))
	{
		result->errorid = 0;
		l_desc = "Successful";
	}
	else
	{
		result->errorid = 0;
		l_desc = "Don't have this cam";
	}

	textLog = "---------RESPOND: " + l_desc;
	LOG_INFO(textLog);

	return SOAP_OK;
}

int nvrService::setWriterParam(int capacity, int writemode, struct result_status *result)
{
	textLog = "+++++++++SETWRITERPARAM: capacity " + std::to_string(capacity)
			+ " wirtemode  " + std::to_string(writemode);
	LOG_INFO(textLog);
	if (capacity <= 0)
	{
		textLog = "---------RESPOND: error parameter";
		LOG_INFO(textLog);
		result->errorid = 6;
		result->errordesc = "error parameter";
		return SOAP_OK;
	}

	std::string desc;
	Configuration::GetSingleton()->dataCapacity = capacity;
	Configuration::GetSingleton()->modeNVR = writemode;

	desc = "suscessfull";
	textLog = "---------RESPOND: " + desc;
	LOG_INFO(textLog);

	result->errorid = 0;
	result->errordesc = (char*) desc.c_str();

	return SOAP_OK;
}

int nvrService::setBackup(int mode, int timevalue, int capactityvalue, struct result_status *result)
{
	textLog = "+++++++++SETBACKUP : mode  " + std::to_string(mode) + "; timevalue  "
			+ std::to_string(timevalue) + ";  capacity "
			+ std::to_string(capactityvalue);
	LOG_INFO(textLog);
	textLog = "---------RESPOND : sucessful";
	LOG_INFO(textLog);

	return SOAP_OK;
}
