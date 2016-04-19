///*
// * mpeg4encoder.h
// *
// *  Created on: Jul 21, 2014
// *      Author: xyz
// */
//
//#ifndef MPEG4ENCODER_H_
//#define MPEG4ENCODER_H_
//
//#include <xvid.h>
//extern "C"{
//#include <libavcodec/avcodec.h>
//#include <libavformat/avformat.h>
//#include <libswscale/swscale.h>
//}
//#include "mycommon.h"
//
//#define VSS_BALINE_PROFILE 66
//#define VSS_MAIN_PROFILE 77
//#define VSS_HIGHT_PROFILE 100
//
//#define VSS_ENTROPY_CAVLC 0
//#define VSS_ENTROPY_CABAC 1
//
//#define VSS_RATE_CONTROL_VBR 0
//#define VSS_RATE_CONTROL_CBR 1
//#define VSS_RATE_CONTROL_CBR_FILTER 2
//
//#define VSS_FRAME_RATE_FULL 1 //30 for NTSC,25 for PAL
//#define VSS_FRAME_RATE_15 2 //15 for all
//#define VSS_FRAME_RATE_10 3 //10 frame/s
//#define VSS_FRAME_RATE_5 6
//
//#define VSS_COLOR_PAL 0
//#define VSS_COLOR_NTSC 1
//
//#define VSS_COLOR_RGB24  0 // most common receid from camera
//#define VSS_COLOR_RGB32  1
//#define VSS_COLOR_YUV420 2
//
//typedef struct VSS_SETTING
//{
//	int nProfile; //66 baseline, 77 main
//	int nLevel; //Chi ho tro tu 1 den 4.2
//
//	int nEntropyMode; //CAVLC or CABAC. Note rang CABAC khong ho trong trong baseline
//	int nRateControlMode; //0: CBR,1 VBR
//	int nSenceDectect; //1 enable, 0 disable
//
//	int nBitrate; //Tinh theo kilobit
//
//	int nContentEncoder; //1: Content 0:Source
//
//	//lien quan den cac thu khac
//	int nWidth;  //frame width
//	int nHeight; //frame height
//	int nIdrPicture; //khoang cach giua 2 frame I
//
//	int nFrameRate; // 0 full, 15: 1, 10:2,5:3
//	int nColor;  //0 PAL,1 NTSC
//	int nSource; //0: Composite, 1: SVideo
//	int nColorSpace; // color space
//
//	// create default params
//	VSS_SETTING() : nProfile(VSS_BALINE_PROFILE), nLevel(30), nEntropyMode(VSS_ENTROPY_CAVLC), nFrameRate(VSS_FRAME_RATE_FULL),
//			nColor(1), nBitrate(512), nWidth(640), nHeight(480), nSenceDectect(1), nRateControlMode(VSS_RATE_CONTROL_CBR),
//			nIdrPicture(33), nContentEncoder(0), nColorSpace(VSS_COLOR_RGB24) {}
//
//} VSS_SETTING;
//
//
//class Mpeg4Encoder
//{
//public:
//	Mpeg4Encoder();
//	virtual ~Mpeg4Encoder();
//	bool initVideoEncoder(const VSS_SETTING& param);
//	bool closeVideoEncoder();
//	int encodeFrame(unsigned char* src, unsigned char* dst);
//
//private:
//	SwsContext* convertContext; // convert rgb to yuv
//	void*			m_hMpeg4;
//	unsigned long	m_NumOfFrames;
//	void*			m_hMpeg4Mutex;
//	bool			m_bFastUpdate;
//	char*			m_pOutput; // origin LPBYTE
//	VSS_SETTING		m_videoparam;
//	AVFrame*        m_yuvImage;
//};
//
//#endif /* MPEG4ENCODER_H_ */
