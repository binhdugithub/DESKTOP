/*
 * multicastprocessing.cpp
 *
 *  Created on: Jul 15, 2014
 *      Author: xyz
 */


#include "multicastprocessing.h"
#include <QtGui/qimage.h>
#include <QtGui/qpainter.h>
#include <fstream>

wstring widen( const string& str )
{
      wostringstream wstm ;
      //wstm.imbue(std::locale("en_US.UTF-8"));
      std::setlocale(LC_ALL, "en_US.utf8");
      const ctype<wchar_t>& ctfacet =
      use_facet< ctype<wchar_t> >( wstm.getloc() ) ;
      for( size_t i=0 ; i<str.size() ; ++i )
      wstm << ctfacet.widen( str[i] ) ;
      return wstm.str() ;
}

MulticastProcessing::MulticastProcessing()
{
	initOk = false;
	msgbuf = new char[MSGBUFSIZE];
}

MulticastProcessing::~MulticastProcessing()
{

}

bool MulticastProcessing::initMulticast(const std::string& ip, uint16_t port, int waitTime)
{
	initOk = false;
	if((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0)
	{
		LOG_ERROR("MulticastProcessing > Cannot innit soket");
		std::cout<<"Cannot init socket"<<std::endl;
		return false;
	}

	//allow multiple sockets to use the same PORT number
	u_int yes = 1;
	if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0)
	{
		LOG_ERROR("MulticastProcessing > Cannot allow multiple sockets to use the same PORT number");
		std::cout<<"Cannot allow multiple sockets to use the same PORT numbe"<<std::endl;
		return false;
	}

	//set up destination address
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_ANY); /* N.B.: differs from sender */
	addr.sin_port=htons(port);

	if (bind(fd,(struct sockaddr *) &addr,sizeof(addr)) < 0)
	{
		LOG_ERROR("MulticastProcessing > Cannot bind socket");
		std::cout<<"Cannot bind socket"<<std::endl;
		return false;
	}

	// use setsockopt() to request that the kernel join a multicast group */
	mreq.imr_multiaddr.s_addr=inet_addr(ip.c_str());
	mreq.imr_interface.s_addr=htonl(INADDR_ANY);
	if (setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0)
	{
		LOG_ERROR("MulticastProcessing > Cannot setsockopt");
		return false;
	}

	timeOut = waitTime;
	initOk = true;
	return true;
}

void MulticastProcessing::startListenning()
{
	LOG_INFO("MulticastProcessing::startListenning  Start listenning");
	if(!initOk)
	{
		LOG_ERROR("MulticastProcessing::startListenning Initialization failed");
		cout<<"Can not initialize"<<endl;
		return;
	}
	mThread = new std::thread(startThread, this);
}

void MulticastProcessing::startThread(void* userData)
{
	MulticastProcessing* pThis = (MulticastProcessing*)userData;
	pThis->doListenning();
}

void MulticastProcessing::doListenning()
{

	LOG_INFO("MulticastProcessing::doListenning Do listenning");
	// TODO need to reopen socket incase socket is closed
	unsigned int addrlen;
	int nbytes;
	addrlen = sizeof(addr);
//	ofstream myfile;
//	myfile.open ("./google.bin", ios::out | ios::app | ios::binary);

	while (1)
	{

		nbytes = recvfrom(fd, msgbuf, MSGBUFSIZE, 0, (sockaddr *) &addr, &addrlen);
//		cout<<"nbyte "<<nbytes<<endl;
//		myfile << msgbuf<<endl;
//		myfile.flush();
//		myfile.close();
//		exit(0);
		//std::cout<<"received msg size: "<<nbytes<<std::endl;

		if(nbytes < 0)
		{
			  LOG_ERROR("MulticastProcessing > Error while reading soket");
			  sleep(10);
			  continue;
		}
		//google::protobuf::
		if(tollMsg.ParseFromArray(msgbuf, nbytes))//tollMsg.ParseFromString(string(msgbuf))tollMsg.ParseFromArray(msgbuf, nbytes)*/)
		{

//			cout<<tollMsg.staffname()<<endl;
//			  sleep(5);
//			  QString txt = QString::fromUtf8(tollMsg.staffname().c_str());
//			  QImage img("./okImg.jpg");
//			  if(img.width() <= 0)
//				  cout<<"not valid image"<<endl;
//			  QPainter painter;
//				painter.begin(&img);
//
//				painter.setFont(QFont("Arial", 20, QFont::Bold));
//				painter.setPen(QColor(200,200,0));
//				painter.drawText(QPoint(200,200), txt);
//
//				img.save("./draw.jpg");
//				painter.end();

			  MulticastMsg mMsg = MulticastMsg();
			  mMsg.laneid = tollMsg.laneid();
			  mMsg.platenumber = tollMsg.platenumber();
			  mMsg.price = tollMsg.price();
			  mMsg.staffname = (tollMsg.staffname());
			  mMsg.vehicleclass = tollMsg.vehicleclass();
			  mMsg.timestamp = tollMsg.timestamp();
			  mMsg.cameralanip = tollMsg.cameralaneip();
			  //cout<<"ID: "<<tollMsg.laneid()<<" Price:  "<<tollMsg.price()<<" Staff "<< tollMsg.staffname()<<tollMsg.platenumber()<<" vclass "<< tollMsg.vehicleclass()<<" timestamp "<<tollMsg.timestamp()<<" camip "<<tollMsg.cameralaneip()<<endl;
			  processMsg(mMsg);
		  }
		  usleep(50*1000);
	 }
}

void MulticastProcessing::processMsg(const MulticastMsg& msg)
{
	ImageOverlayText* ov = SourceManager::getSingleton().findOverlay(msg.cameralanip/*laneid "rtsp://root:admin@192.168.7.68/axis-media/media.amp"*/);
	if(!ov)
		return;
	ov->setMulticastMsg(msg);
}

bool MulticastProcessing::isNewMsg(const MulticastMsg& msg)
{
	return true;
//	cout<<"is new Msg"<<endl;
//	if(multicastMsg.empty())
//	{
//		multicastMsg.push_back(msg);
//		return true;
//	}
//	bool hasMsg = false;
//	for(int i = 0; i < multicastMsg.size(); ++i)
//	{
//		if(multicastMsg[i]->laneid == msg->laneid)
//			hasMsg = true;
//		if(multicastMsg[i]->laneid == msg->laneid && multicastMsg[i]->platenumber == msg->platenumber && multicastMsg[i]->staffname == msg->staffname &&
//				multicastMsg[i]->price == msg->price && multicastMsg[i]->vehicleclass == msg->vehicleclass)
//			return false;
//	}
//	cout<<"end of is Msg"<<endl;
//	return !hasMsg;
}
