/*
 * Camera.cpp
 *
 *  Created on: Dec 2, 2015
 *      Author: root
 */

#include "Camera.h"

Camera::Camera()
{
	// TODO Auto-generated constructor stub
	m_Id = std::string("");
	m_Ip = std::string("");
	m_Url = std::string("");
	m_Length = 0;
	m_Mode   = -1;
}

Camera::Camera(std::string p_id, std::string p_ip, std::string p_recordUrl, int p_recordLength, int p_recordMode)
{
	m_Id = p_id;
	m_Ip = p_ip;
	m_Url = p_recordUrl;
	m_Length = p_recordLength;
	m_Mode = p_recordMode;
}


Camera::~Camera()
{
	// TODO Auto-generated destructor stub
	m_Id = std::string("");
	m_Ip = std::string("");
	m_Url = std::string("");
	m_Length = 0;
	m_Mode = -1;
}

