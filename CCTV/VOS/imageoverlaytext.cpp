/*
 * imageoverlaytext.cpp
 *
 *  Created on: Jul 20, 2014
 *      Author: xyz
 */

#include "imageoverlaytext.h"

const int expandStaff = 40; // expand staff position

ImageOverlayText::ImageOverlayText()
{
	// this class is passive class, called automatically when client has data
	// so set isstart to true, thread doEncode only stop when we realy remove source
	LOG_INFO("ImageOverlayText::ImageOverlayText create constructor");
	isStart = true;
	hasInit = false;
	imgWidth = 0;
	imgHeight = 0;
	multicastInfo = MulticastMsg();
	newMulticastInfor = true;
	if(DBControl::getSingleton().getDisplayPosition(posDsp) != 0)
	{
		cout<<"can not read position display from db"<<endl;
		// so we need to initialize this by default
		for(int i = 1; i <=6; ++i)
			posDsp.push_back(i);
	}
	regionInfo = vector<QRect>(6);
	dspTime = "00:00:00 00/00/00";
	startTimeEventProc = 0;
	hasDrawInfor = false;
	encodeFps = 25;
	isNoSignal = false;
	mThread = NULL;
}

ImageOverlayText::~ImageOverlayText()
{
	// TODO Auto-generated destructor stub
}


bool ImageOverlayText::initVideoOverlay(QImage* firstImg)
{

	resultImg = new QImage(firstImg->width(), firstImg->height(), firstImg->format());
	painter.begin(resultImg);
	//setup painter

	imgWidth = firstImg->width();
	imgHeight = firstImg->height();
	rWidth = (int)imgWidth/3;
	ry = imgHeight - DRAW_INFO_HEIGHT;
	// setup region to draw text
//	regionInfo.push_back(QRect(0*rWidth, 0, rWidth, DRAW_INFO_HEIGHT));
//	regionInfo.push_back(QRect(1*rWidth, 0, rWidth, DRAW_INFO_HEIGHT));
//	regionInfo.push_back(QRect(2*rWidth, 0, rWidth, DRAW_INFO_HEIGHT));
//	regionInfo.push_back(QRect(0*rWidth, ry, rWidth, DRAW_INFO_HEIGHT));
//	regionInfo.push_back(QRect(1*rWidth, ry, rWidth, DRAW_INFO_HEIGHT));
//	regionInfo.push_back(QRect(2*rWidth, ry, rWidth, DRAW_INFO_HEIGHT));

	regionInfo[posDsp[0] - 1] = QRect(0*rWidth, 0, rWidth - expandStaff, DRAW_INFO_HEIGHT); // lane id
	regionInfo[posDsp[1] - 1] = QRect(1*rWidth - expandStaff, 0, rWidth + 2*expandStaff, DRAW_INFO_HEIGHT); // staff
	regionInfo[posDsp[2] - 1] = QRect(2*rWidth + expandStaff, 0, rWidth - expandStaff, DRAW_INFO_HEIGHT); // time
	regionInfo[posDsp[3] - 1] = QRect(0*rWidth, ry, rWidth, DRAW_INFO_HEIGHT);
	regionInfo[posDsp[4] - 1] = QRect(1*rWidth, ry, rWidth, DRAW_INFO_HEIGHT);
	regionInfo[posDsp[5] - 1] = QRect(2*rWidth, ry, rWidth, DRAW_INFO_HEIGHT);
	// pre-fill the drawing region
	//painter.setOpacity(0.5);
	painter.fillRect(QRect(0,0, imgWidth, DRAW_INFO_HEIGHT), QColor(0,0,0));
	painter.fillRect(QRect(0,imgHeight - DRAW_INFO_HEIGHT, imgWidth, DRAW_INFO_HEIGHT), QColor(0,0,0));

	painter.setFont(QFont("Times New Roman", 13, QFont::Bold));
	painter.setPen(QColor(255,255,255));

	// draw line seperted the region infor
	painter.drawLine(1*rWidth - expandStaff, 5, 1*rWidth - expandStaff, DRAW_INFO_HEIGHT - 5);
	painter.drawLine(2*rWidth + expandStaff, 5, 2*rWidth + expandStaff, DRAW_INFO_HEIGHT - 5);
	painter.drawLine(1*rWidth, ry + 5, 1*rWidth, ry + DRAW_INFO_HEIGHT - 5);
	painter.drawLine(2*rWidth, ry + 5, 2*rWidth, ry + DRAW_INFO_HEIGHT - 5);

	param = VideoEncoderParam();
	param.width = imgWidth;
	param.height = imgHeight;
	param.gop = 5;
	param.bitrate = 500;
	param.fpsNum = encodeFps;
	encoder = new FFMpegVideoEncoder();
	encoder->openVideoEncoder(param);
	encodeData = new uint8_t[1024*1024];
	encodeSize = 0;
	convertCtx = sws_getContext(param.width, param.height, PIX_FMT_RGB24,
	    		param.width, param.height, PIX_FMT_YUV420P, SWS_FAST_BILINEAR, NULL, NULL, NULL);

	mThread = new std::thread(encodeThread, this);
	//mThread = std::unique_ptr<std::thread>(new std::thread(encodeThread, this));
	//std::unique_ptr<std::thread> mThread(new std::thread(encodeThread, this));

	LOG_INFO("ImageOverlayText::initVideoOverlay OK");
	return hasInit = true;

}

void ImageOverlayText::addImageToQue(QImage* image)
{
	dataLocker.lock();
	imageQue.push(image);
	if(imageQue.size() > MAX_IMAGE_QUE)
	{
		QImage* tmpImg = imageQue.front();
		imageQue.pop();
		delete tmpImg; tmpImg = NULL;
	}
	dataLocker.unlock();

}

void ImageOverlayText::setMulticastMsg(const MulticastMsg& msg)
{
	//cout<<"Set MulticastMSG: staff = "<<msg.staffname<<endl;
	multicastLocker.lock();
	startTimeEventProc = elc::GetTickCount();
	//if(multicastInfo == msg)
	//{
	//	multicastLocker.unlock();
	//	return;
	//}
	newMulticastInfor = true;
	multicastInfo = msg;
	hasDrawInfor = false;
	multicastLocker.unlock();
}

void ImageOverlayText::setNoSignal(bool noSignal)
{
	isNoSignal = noSignal;
	LOG_INFO("ImageOverlayText::setNoSignal -isNosignal="<<noSignal);
	if(isNoSignal)
	{
		LOG_INFO("ImageOverlayText::setNoSignal Paint image -w="<<imgWidth<<" -h="<<imgHeight);
//		painter.fillRect(QRect(0, DRAW_INFO_HEIGHT, imgWidth, imgHeight - 2*DRAW_INFO_HEIGHT), QColor(10,10,10));
//		painter.setFont(QFont("Times New Roman", 20, QFont::Bold));
//		painter.drawText(QRect(0, imgHeight/2 - 10, imgWidth, 30), Qt::AlignCenter, "No Signal! Reconnecting ...");
//		painter.setFont(QFont("Times New Roman", 13, QFont::Bold));
	}
}

MulticastMsg ImageOverlayText::getMulticastMsg() const
{
	return multicastInfo;
}

void ImageOverlayText::setSource(const string& url)
{
	mUrl = url;
	ip = elc::getIpFromRtspUrl(url);
}

string ImageOverlayText::getSource() const
{
	return mUrl;
}

string ImageOverlayText::getIP() const
{
	return ip;
}

QImage* ImageOverlayText::getImage()
{
	//cout<<"Get image from que"<<endl;
	dataLocker.lock();
	QImage* img = NULL;
	if(!imageQue.empty())
	{
		img = imageQue.front();
		imageQue.pop();
	}
	dataLocker.unlock();
	return img;
}

void ImageOverlayText::onDataReceived(VideoFrame* vf, void* usr)
{

	//cout<<"ondata"<<endl;
	QImage* img = new QImage(vf->data, vf->width, vf->height, QImage::Format_RGB888);
	ImageOverlayText* pthis = (ImageOverlayText*)usr;
	pthis->addVideoEffect(img);
	delete vf; vf = NULL;
	//cout<<"I am "<<pthis<<" and I received data"<<endl;



}

void ImageOverlayText::addVideoEffect(QImage* src)
{
	if(!hasInit)
		initVideoOverlay(src);

	QImage tmp = src->copy(0, DRAW_INFO_HEIGHT, imgWidth, imgHeight - 2*DRAW_INFO_HEIGHT);
	painter.drawImage(0, DRAW_INFO_HEIGHT, tmp);

	QString timestamp = QString::fromStdString(elc::getCurrentTimeDisplay());
	if(dspTime != timestamp)
	{
		dspTime = timestamp;
		painter.fillRect(QRect(2*rWidth + expandStaff, 0, rWidth - expandStaff, DRAW_INFO_HEIGHT), QColor(0,0,0));
		painter.drawLine(2*rWidth + expandStaff, 5, 2*rWidth + expandStaff, DRAW_INFO_HEIGHT - 5);
		painter.drawText(regionInfo[2], Qt::AlignCenter, dspTime);

		multicastLocker.lock();
		if((elc::GetTickCount() - startTimeEventProc >= Config::keepOverlayInforActivated*1000) && hasDrawInfor)
		{
			painter.fillRect(QRect(0,imgHeight - DRAW_INFO_HEIGHT, imgWidth, DRAW_INFO_HEIGHT), QColor(0,0,0));
			painter.drawLine(1*rWidth, ry + 5, 1*rWidth, ry + DRAW_INFO_HEIGHT - 5);
			painter.drawLine(2*rWidth, ry + 5, 2*rWidth, ry + DRAW_INFO_HEIGHT - 5);
			painter.drawText(regionInfo[3], Qt::AlignCenter, "-+-");
			painter.drawText(regionInfo[4], Qt::AlignCenter, "-+-");
			painter.drawText(regionInfo[5], Qt::AlignCenter, "-+-");
		}
		multicastLocker.unlock();

	}

	multicastLocker.lock();
	if(newMulticastInfor)
	{
		drawNewInfo();
		newMulticastInfor = false;
	}
	multicastLocker.unlock();
	QImage* img = new QImage(resultImg->bits(), imgWidth, imgHeight, resultImg->format());
	addImageToQue(img);
	delete src; src = NULL;

}

void ImageOverlayText::startOverlay()
{
	//isStart = true;
	//hasInit = false;
	//mThread = new std::thread(encodeThread, this);
}

void ImageOverlayText::close() // exit thread
{
	startLocker.lock();
	isStart = false;
	startLocker.unlock();
	if(mThread != NULL)
	{	LOG_INFO("ImageOverlayText::close delete thread ");
		mThread->join();
		delete mThread;
		mThread = NULL;
	}
}

void ImageOverlayText::stopOverlay()
{
	LOG_INFO("ImageOverlayText::stopOverlay() start stopping");
	startLocker.lock();
	isStart = false;
	startLocker.unlock();
	// clear cache
	//cout<<"stop overlay -> delete image que"<<endl;
	dataLocker.lock();
	if(!imageQue.empty())
	{
		for(size_t i = 0; i < imageQue.size(); ++i)
		{
			QImage* img = imageQue.front();
			imageQue.pop();
			delete img;
		}
		imageQue = queue<QImage*>();
	}
	dataLocker.unlock();
	cout<<"stop overlay -> delete mp4 package"<<endl;

	mp4Locker.lock();
	if(!mp4Que.empty())
	{
		for(size_t i = 0; i < mp4Que.size(); ++i)
		{
			Mpeg4Package* pk = mp4Que.front();
			mp4Que.pop();
			delete pk;
		}
		mp4Que = queue<Mpeg4Package*>();
	}
	mp4Locker.unlock();
	if(mThread)
	{
		mThread->join();
		delete mThread;
		mThread = NULL;
	}
	LOG_INFO("stop overlay -> stop successfull");
	//hasInit = false;
}

void ImageOverlayText::drawNewInfo()
{
	//painter.setPen(QColor::fromRgb(0,0,0));
	//cout<<"drawing info ..."<<endl;
	painter.fillRect(QRect(0,0, imgWidth - rWidth + expandStaff, DRAW_INFO_HEIGHT), QColor(0,0,0));
	painter.fillRect(QRect(0,imgHeight - DRAW_INFO_HEIGHT, imgWidth, DRAW_INFO_HEIGHT), QColor(0,0,0));
	// draw line seperted the region infor
	painter.drawLine(1*rWidth - expandStaff, 5, 1*rWidth - expandStaff, DRAW_INFO_HEIGHT - 5);
	painter.drawLine(2*rWidth + expandStaff, 5, 2*rWidth + expandStaff, DRAW_INFO_HEIGHT - 5);
	painter.drawLine(1*rWidth, ry + 5, 1*rWidth, ry + DRAW_INFO_HEIGHT - 5);
	painter.drawLine(2*rWidth, ry + 5, 2*rWidth, ry + DRAW_INFO_HEIGHT - 5);
	//QString::fromStdWString();
	QString laneid = QString::fromUtf8("Số hiệu làn: ") + QString::number(multicastInfo.laneid);
	QString staff = QString::fromUtf8("Nhân viên: ") + QString::fromUtf8(multicastInfo.staffname.c_str());//*/ =QString::fromUtf8("Đặng Ngọc Tùng");
	QString plate = QString::fromUtf8("Biển số: ") + QString::fromUtf8(multicastInfo.platenumber.c_str());//QString::fromUtf8("Biển số: 29A6969");
	QString vclass = QString::fromUtf8("Loại xe: ") + QString::fromUtf8(multicastInfo.vehicleclass.c_str());//QString::fromUtf8("Loại xe: Container");
	QString price = QString::fromUtf8("Giá tiền: ") + QString::fromStdString(elc::toVNCurrencyFormat(multicastInfo.price));
	//QString staff = "LONGNV";//QString::fromStdString(multicastInfo.staffname);
	painter.drawText(regionInfo[0], Qt::AlignCenter, laneid);
	painter.drawText(regionInfo[1], Qt::AlignCenter, staff);
	//painter.drawText(regionInfo[3], Qt::AlignCenter, timestamp);// timstamp is drawn by each frame
	painter.drawText(regionInfo[3], Qt::AlignCenter, vclass);
	painter.drawText(regionInfo[4], Qt::AlignCenter, price);
	painter.drawText(regionInfo[5], Qt::AlignCenter, plate);

	//noSignalImg = resultImg;
	hasDrawInfor = true;
}

void ImageOverlayText::encodeThread(void* userParam)
{
	ImageOverlayText* pthis = (ImageOverlayText*)userParam;
	pthis->doEncode();
}

void ImageOverlayText::doEncode()
{
	LOG_INFO("ImageOverlayText::doEncode start thread");
	while(1)
	{
		QImage* img = NULL;
		startLocker.lock();
		if(!isStart)
		{
			startLocker.unlock();
			break;
		}
		startLocker.unlock();

		if(isNoSignal)  // if no signal recieve, trying to reconnect ...
		{
			//if(Config::isDebug)
				//LOG_INFO("ImageOverlayText::doEncode Encode nosignal image");
			QString timestamp = QString::fromStdString(elc::getCurrentTimeDisplay());
			if(dspTime != timestamp)
			{
				dspTime = timestamp;
				painter.fillRect(QRect(2*rWidth + expandStaff, 0, rWidth - expandStaff, DRAW_INFO_HEIGHT), QColor(0,0,0));
				painter.drawLine(2*rWidth + expandStaff, 5, 2*rWidth + expandStaff, DRAW_INFO_HEIGHT - 5);
//				painter.fillRect(QRect(2*rWidth, 0, rWidth, DRAW_INFO_HEIGHT), QColor(0,0,0));
//				painter.drawLine(2*rWidth, 5, 2*rWidth, DRAW_INFO_HEIGHT - 5);
				painter.drawText(regionInfo[2], Qt::AlignCenter, dspTime);
				painter.fillRect(QRect(0, DRAW_INFO_HEIGHT, imgWidth, imgHeight - 2*DRAW_INFO_HEIGHT), QColor(10,10,10));
				painter.setFont(QFont("Times New Roman", 20, QFont::Bold));
				painter.drawText(QRect(0, imgHeight/2 - 10, imgWidth, 30), Qt::AlignCenter, "No Signal! Reconnecting ...");
				painter.setFont(QFont("Times New Roman", 13, QFont::Bold));
			}
			img = new QImage(resultImg->bits(), imgWidth, imgHeight, resultImg->format());
			//if(Config::isDebug)
			//{
				//img->save("./nosignal.jpg");
				//LOG_INFO("ImageOverlayText::doEncode save image successfully");
			//}

		}

		else
		{
			dataLocker.lock();
			if(imageQue.empty())
			{
				dataLocker.unlock();
				usleep(10*1000);
				continue;
			}
			img = imageQue.front();
			imageQue.pop();
			dataLocker.unlock();
		}


		uint32_t timeStamp = elc::GetTickCount();

		encoder->encodeVideoFrame(img->bits(), timeStamp, encodeData, encodeSize);
		delete img;
		img = NULL;
		if(encodeSize <= 0)
			continue;
		Mpeg4Package* mp4pk = new Mpeg4Package();
		mp4pk->data = new uint8_t[encodeSize];
		memcpy(mp4pk->data, encodeData, encodeSize);
		mp4pk->len = encodeSize;
		//if(Config::isDebug)
			//LOG_INFO("ImageOverlayText::doEncode Finish Doing encoding...");

		addPackageToQue(mp4pk);
		usleep(10);

	}
	LOG_INFO("ImageOverlayText::doEncode end thread");

}

void ImageOverlayText::addPackageToQue(Mpeg4Package* pakage)
{
	mp4Locker.lock();
	mp4Que.push(pakage);
	if(mp4Que.size() > MAX_IMAGE_QUE)
	{
		Mpeg4Package* tmpPkg = mp4Que.front();
		mp4Que.pop();
		tmpPkg->release();
		delete tmpPkg; tmpPkg = NULL;
	}
	mp4Locker.unlock();
}

Mpeg4Package* ImageOverlayText::getEncodeData()
{
	//cout<<"get image encode"<<endl;
	Mpeg4Package* pkt = NULL;
	mp4Locker.lock();
	if(!mp4Que.empty())
	{
		pkt = mp4Que.front();
		mp4Que.pop();
	}
	mp4Locker.unlock();
	//cout<<"get image encode ... add="<<pkt<<"  size="<<mp4Que.size()<<endl;
	return pkt;
}
