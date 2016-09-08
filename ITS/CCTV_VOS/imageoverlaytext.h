/*
 * imageoverlaytext.h
 *
 *  Created on: Jul 20, 2014
 *      Author: xyz
 */

#ifndef IMAGEOVERLAYTEXT_H_
#define IMAGEOVERLAYTEXT_H_

#include "videoeffect.h"
#include "mycommon.h"
#include "vostype.h"
#include "ffmpegvideoencoder.h"
#include "dbcontrol.h"
#include "config.h"

//PIXEL

class ImageOverlayText
{
public:
	ImageOverlayText();
	virtual ~ImageOverlayText();
	void setMulticastMsg(const MulticastMsg& msg);
	void setSource(const string& url);
	string getSource() const;
	string getIP() const;
	MulticastMsg getMulticastMsg() const;
	void startOverlay();
	void stopOverlay();
	bool isStart;
	Mpeg4Package* getEncodeData();
	static void onDataReceived(VideoFrame* vf, void* usr);
	void close();
	int imgWidth;
	int imgHeight;
	double encodeFps;
	void setNoSignal(bool noSignal);
	int DRAW_INFO_HEIGHT;
	int fontsize;

protected:
	bool initVideoOverlay(QImage* firstImg);
	void addImageToQue(QImage* image);
	void addPackageToQue(Mpeg4Package* pakage);
	static void encodeThread(void* userData);
	void addVideoEffect(QImage* src);
	void doEncode();

private:
	vector<string> mText;
	queue<QImage*> imageQue;
	queue<Mpeg4Package*> mp4Que;
	std::thread* mThread;
	//std::unique_ptr<std::thread> mThread;
	recursive_mutex dataLocker;
	recursive_mutex multicastLocker;
	recursive_mutex startLocker;
	recursive_mutex pakageLocker;
	QPainter painter;
	QImage* resultImg;
	bool hasInit;
	string mUrl;
	string ip;
	MulticastMsg multicastInfo;
	void drawNewInfo();
	vector<QRect> regionInfo;
	FFMpegVideoEncoder* encoder;
	uint8_t* encodeData;
	unsigned long encodeSize;
	VideoEncoderParam param;
	std::recursive_mutex mp4Locker;
	SwsContext* convertCtx;// convert bgr2yuv
	QImage* getImage(); // to see if some other thread try to call it
	bool newMulticastInfor;
	vector<int> posDsp; // position to display, read from db
	int rWidth;
	int ry;
	QString dspTime;
	uint32_t startTimeEventProc;
	bool hasDrawInfor;
	bool isNoSignal;
	//QImage* noSignalImg;
};

#endif /* IMAGEOVERLAYTEXT_H_ */
