/*
 * Camera.h
 *
 *  Created on: Dec 2, 2015
 *      Author: root
 */

#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_

#include <string.h>
#include <iostream>
using namespace std;

class Camera
{
public:
	Camera();
	virtual ~Camera();

	//properties
	std::string m_Id;
	std::string m_Ip;
	std::string m_Url;
	int 		m_Mode;
	int 		m_Length;

	//method
	Camera(std::string, std::string, std::string, int, int p_recordMod = -1);

};

#endif /* SRC_CAMERA_H_ */
