/*
 * commondef.h
 *
 *  Created on: 7 Jul, 2014
 *      Author: cuonglm
 */

#ifndef COMMONDEF_H_
#define COMMONDEF_H_

#include <queue>
#include <pthread.h>
#include <string>
#include <iostream>
#include "LogFile.h"
#include "DBWoker.h"
#include <vector>

#define TIMEOUT_RTSP   15   //second


//main
//extern Boolean isExit;

//log
extern std::string textLog;

//storage
static std::string storagePath;

//RTSP Server
static int portListentRTSP;
static std::string userRTSP;
static std::string passRTSP;

//DB
static std::string ipserverDB;
static int portDB;
static std::string user;
static std::string pass;
static std::string schema;

void initConfig();

//RTSP server
void setPortRTSPServer(int port);
int getPortRTSPServer();
void setPassRTSPServer(std::string pass);
std::string getPassRTSPServer();
void setUserRTSPServer(std::string user);
std::string getUserRTSPServer();

//storage
void setStoragePath(std::string storagePath);
std::string getStoragePath();

//DB
std::string getIpServerDB();
int getPortDB();
std::string getUser();
std::string getPass();
std::string getschema();

std::string int2string(int number);
std::string getAddrPoint(void* mThis);
std::vector<std::string> split(char* s, const char* delim);
int getdir (string dir, vector<string> &files);
#endif /* COMMONDEF_H_ */
