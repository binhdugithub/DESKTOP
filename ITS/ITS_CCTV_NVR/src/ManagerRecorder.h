/*
 * ManagerRecorder.h
 *
 *  Created on: Dec 3, 2015
 *      Author: root
 */

#ifndef SRC_MANAGERRECORDER_H_
#define SRC_MANAGERRECORDER_H_

#include <iostream>
#include <string.h>
#include <thread>
#include <mutex>
#include <vector>

#include "Recorder.h"
#include "commondef.h"


using namespace std;

class ManagerRecorder
{
protected:
	static ManagerRecorder *m_instance;
	std::thread *m_HMainThread;
	bool volatile m_IsRunning;
	std::recursive_mutex m_ListRecorderMutex;
	std::vector<Recorder*> m_ListRecorder;
public:
	ManagerRecorder();
	virtual ~ManagerRecorder();
	void StartMain();
	bool AddRecorder(Recorder *p_recorder);
	bool RemoveRecorder(Recorder *p_recorder);
	Recorder* FindRecorder(std::string p_id);
	bool StopRecord(std::string p_id);
	bool StartRecord(std::string, std::string, int, int);
	static void MainThread(void *p_param);
	static ManagerRecorder* GetSingleton();
};

#endif /* SRC_MANAGERRECORDER_H_ */
