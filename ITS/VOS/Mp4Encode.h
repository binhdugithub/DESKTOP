#pragma once
//
//#include <xvid.h>
//#include "Encoder.h"
//#include "mycommon.h"
//
//class CMp4Encoder : public CEncoder
//{
//private:
//	void*			m_hMpeg4;
//	unsigned long	m_NumOfFrames;
//	void*			m_hMpeg4Mutex;
//	bool			m_bFastUpdate;
//
//	unsigned char*			m_pOutput;
//	VSS_SETTING		m_videoparam;
//
//public:
//	CMp4Encoder(void);
//	~CMp4Encoder(void);
//
//	int Init();
//	int Exit();
//
//	int setting(void* pParam);
//	int getVideoSetting(void* pParam); // void*
//	int encode(unsigned char* pDataIn, unsigned long dwSize, unsigned long dwTS); // char*
//	void getDefaultParam(VSS_SETTING* pSetting);
//
//	int changeBitrate(int nNewBitrate);
//	int fastUpdate();
//	void SetFormat(int nColor, int nFrameRate);
//
//	static CMp4Encoder* getInstance();
//	static void removeInstance();
//
//	void getEncodeData(unsigned char* pDataOut, unsigned long& dwSize, unsigned long& dwTS);
//protected:
//	int enc_init();
//	int enc_main(unsigned char *image, unsigned char *bitstream);
//	void OnEncodedData(unsigned char* pData, int nSize, unsigned long dwTS);
//	static CMp4Encoder* m_pInstance;
//	unsigned long outSize;
//	unsigned long timesptamp;
//};
