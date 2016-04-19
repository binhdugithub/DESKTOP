/*
 * ManagerRecorder.cpp
 *
 *  Created on: Dec 3, 2015
 *      Author: root
 */

#include "ManagerRecorder.h"

ManagerRecorder* ManagerRecorder::m_instance = NULL;
ManagerRecorder::ManagerRecorder()
{
	// TODO Auto-generated constructor stub

}

ManagerRecorder::~ManagerRecorder()
{
	// TODO Auto-generated destructor stub
	if(m_HMainThread)
	{
		m_IsRunning = false;
		m_HMainThread->join();
		delete m_HMainThread;
		m_HMainThread = 0;
	}

	while(!m_ListRecorder.empty())
	{
		delete m_ListRecorder.front();
		m_ListRecorder.erase(m_ListRecorder.begin());
	}
}

ManagerRecorder* ManagerRecorder::GetSingleton()
{
	if(m_instance == NULL)
	{
		m_instance = new ManagerRecorder();
	}

	return m_instance;
}

bool ManagerRecorder::AddRecorder(Recorder *p_recorder)
{
	std::cout << "In AddRecorder" << std::endl;
	if(p_recorder)
	{


		m_ListRecorderMutex.lock();
		std::cout << "Pass lock" << std::endl;

		for(auto it = m_ListRecorder.begin(); it != m_ListRecorder.end(); ++it)
		{
			if((*it)->m_Camera->m_Id == p_recorder->m_Camera->m_Id)
			{
				std::cout << "Already Cam: " << p_recorder->m_Camera->m_Id << " => add failed" << std::endl;
				m_ListRecorderMutex.unlock();
				return false;
			}
		}

		std::cout << "Add cam " << p_recorder->m_Camera->m_Id << std::endl;
		LOG_INFO("Add cam " << p_recorder->m_Camera->m_Id);
		std::string l_query = "UPDATE its_cam SET recordmode = 2 WHERE id = '" +p_recorder->m_Camera->m_Id + "' ;";
		insertFirstDBQueue(l_query);

		m_ListRecorder.push_back(p_recorder);
		m_ListRecorderMutex.unlock();

		return true;
	}
	else
	{
		std::cout << "Add cam fail cuz Recorder is NULL" << std::endl;
	}

	return false;
}

bool ManagerRecorder::RemoveRecorder(Recorder *p_recorder)
{
	if(p_recorder)
	{
		m_ListRecorderMutex.lock();
		for(auto it = m_ListRecorder.begin(); it != m_ListRecorder.end(); it++)
		{

			if((*it) == p_recorder)
			{
				delete (p_recorder);
				p_recorder = NULL ;
				m_ListRecorder.erase(it);

				m_ListRecorderMutex.unlock();
				return true;
			}
		}

		m_ListRecorderMutex.unlock();
		return false;
	}

	return false;
}

Recorder* ManagerRecorder::FindRecorder(std::string p_id)
{
	m_ListRecorderMutex.lock();
	Recorder *FinderRecorder = NULL;
	if(p_id.length() > 0)
	{
		for(auto it = m_ListRecorder.begin(); it != m_ListRecorder.end(); it++)
		{
			if((*it)->m_Camera->m_Id == p_id)
			{
				FinderRecorder = *it;
				break;
			}
		}
	}

	m_ListRecorderMutex.unlock();
	return FinderRecorder;
}

bool ManagerRecorder::StopRecord(std::string p_id)
{
	m_ListRecorderMutex.lock();
	Recorder *MyRecorder = this->FindRecorder(p_id);
	if(MyRecorder)
	{
		MyRecorder->m_Status = STOPRECORD;
	}
	else
	{
		m_ListRecorderMutex.unlock();
		return false;
	}

	m_ListRecorderMutex.unlock();
	return true;
}

bool ManagerRecorder::StartRecord(std::string p_id, std::string p_url,int p_leng, int p_mod)
{
	m_ListRecorderMutex.lock();
	if(p_id.length() > 0 && p_url.length() > 0 && p_leng > 0)
	{
		Recorder *MyRecorder = this->FindRecorder(p_id);
		if(MyRecorder)
		{
			std::cout << "Already instance of Recorder in list" << std::endl;
			if(MyRecorder->m_Status == RECORDING)
			{
				std::string l_query = "UPDATE its_cam SET recordmode = 1 WHERE id = '" + p_id + "' ;";
				insertFirstDBQueue(l_query);
			}

			m_ListRecorderMutex.unlock();
			return false;
		}
		else
		{
			std::cout << "Creat new instance of Recorder" << std::endl;
			LOG_INFO("Create new instance of Recorder");

			MyRecorder = new Recorder(p_id, "", p_url, p_leng, p_mod, RETRYRECORD);

			AddRecorder(MyRecorder);
		}
	}
	else
	{
		std::cout << "Parametter failed" << std::endl;
	}

	m_ListRecorderMutex.unlock();
	return true;
}

void ManagerRecorder::StartMain()
{
	m_IsRunning = true;
	m_HMainThread = new std::thread(MainThread, this);
}

void ManagerRecorder::MainThread(void *p_param)
{
	ManagerRecorder *MyClass = (ManagerRecorder*)p_param;
	while(MyClass->m_IsRunning)
	{
		MyClass->m_ListRecorderMutex.lock();
		for(auto it = MyClass->m_ListRecorder.begin(); it != MyClass->m_ListRecorder.end(); ++it)
		{
			//std::cout << "Info cam:" << (*it)->m_Camera->m_Id << " status:" << (*it)->m_Status<< std::endl;

			if((*it)->m_Status == RETRYRECORD)
			{
				(*it)->StartRecord();
			}
			else if((*it)->m_Status == STOPRECORD)
			{
				std::cout << "ManagerRecorder delete cam : " << (*it)->m_Camera->m_Id << std::endl;
				LOG_INFO("Delete cam: " << (*it)->m_Camera->m_Id);

				std::cout <<" Set cam to status 0" << std::endl;
				std::string l_query = "UPDATE its_cam SET recordmode = 0 WHERE id = '" + (*it)->m_Camera->m_Id + "' ;";
				insertFirstDBQueue(l_query);

				delete (*it);
				MyClass->m_ListRecorder.erase(it);

 				break;
			}
		}

		MyClass->m_ListRecorderMutex.unlock();

		std::cout << "Sleep 1 second" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	}

	std::cout << "Out loop of ManagerRecorder" << std::endl;
}
