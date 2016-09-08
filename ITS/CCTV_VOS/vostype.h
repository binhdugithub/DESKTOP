/*
 * vostype.h
 *
 *  Created on: Jul 27, 2014
 *      Author: xyz
 */

#ifndef VOSTYPE_H_
#define VOSTYPE_H_

#include <string>
#include <vector>

using namespace std;

//const int MAXEVENTS = 64;
const int MSGBUFSIZE = 1024;
const int MAXID = 8;
const int MAX_IMAGE_QUE = 10;

typedef struct MulticastMsg
{
	unsigned int laneid;
	unsigned int price;
	string timestamp;
	string staffname;
	string platenumber;
	string tickettype;
	string cameralanip;
	MulticastMsg() : laneid(0), price(0), timestamp("-+-"), cameralanip("0.0.0.0"),
			staffname("-+-"), platenumber("-+-"), tickettype("-+-"){}
	bool operator==(const MulticastMsg& other)
	{
		if(laneid == other.laneid && price == other.price && staffname == other.staffname && cameralanip == other.cameralanip&&
				platenumber == other.platenumber && tickettype == other.tickettype && timestamp == other.timestamp)
			return true;
		return false;
	}

	bool operator != (const MulticastMsg& other)
	{
		return !(*this == other);
	}

	MulticastMsg& operator=(const MulticastMsg& other)
	{
		laneid = other.laneid;
		price = other.price;
		staffname = other.staffname;
		platenumber = other.platenumber;
		tickettype = other.tickettype;
		timestamp = other.timestamp;
		cameralanip = other.cameralanip;
		return *this;
	}

} MulticastMsg;


typedef struct VideoFrame
{
	unsigned char* data;
	int width;
	int height;
	unsigned long time_stamp;
	VideoFrame()
	{
		data = NULL;
		width = height = 0;
		time_stamp = 0;
	}
	~VideoFrame()
	{

	}
} VideoFrame;

typedef struct Mpeg4Package
{
	uint8_t* data;
	uint32_t len;
	Mpeg4Package() : data(NULL), len(0){}
	void copy(Mpeg4Package* cp)
	{
		if(cp->data != NULL)
			cp->release();
		cp->len = len;
		cp->data = new uint8_t[len];
		memcpy(cp->data, data, len);
	}
	void release()
	{
		if(data != NULL)
		{
			delete [] data;
			data = NULL;
			len = 0;
		}
	}
} Mpeg4Package;

// handling soap type
enum voverlay_error {
	VOVERLAY_OK,					// Successfull
	VOVERLAY_SOURCE_NOT_FOUND,		// Source not exist
	VOVERLAY_SOURCE_EXIST,			// Source has existed
	VOVERLAY_FULLHD_NOT_SUPPORT,	// Dont support HD1080 resolution
	VOVERLAY_OVERLOAD,				// Server is out of load
	VOVERLAY_URL_INVALID,			// Url input is invalid
	VOVERLAY_INIT_FAILED,			// Server init failed: decoder, encoder, multicast receiver
	VOVERLAY_DB_FAILED				// failed when working with DB
};
#endif /* VOSTYPE_H_ */
