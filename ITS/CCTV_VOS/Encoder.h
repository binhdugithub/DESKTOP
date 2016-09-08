#ifndef ENCODE_H
#define ENCODE_H

typedef void (*PVSOFTCALLBACKVFUNCTION)(unsigned char*,int,unsigned long,int,void*);
typedef void (*PVSOFT_LOG)( void *, int i_level, const char *psz);


#define VSS_BALINE_PROFILE 66
#define VSS_MAIN_PROFILE 77
#define VSS_HIGHT_PROFILE 100

#define VSS_ENTROPY_CAVLC 0
#define VSS_ENTROPY_CABAC 1

#define VSS_RATE_CONTROL_VBR 0
#define VSS_RATE_CONTROL_CBR 1
#define VSS_RATE_CONTROL_CBR_FILTER 2

#define VSS_FRAME_RATE_FULL 1 //30 for NTSC,25 for PAL
#define VSS_FRAME_RATE_15 2 //15 for all
#define VSS_FRAME_RATE_10 3 //10 frame/s
#define VSS_FRAME_RATE_5 6

#define VSS_COLOR_PAL 0
#define VSS_COLOR_NTSC 1


typedef struct VSS_SETTING
{
	int nProfile; //66 baseline, 77 main
	int nLevel; //Chi ho tro tu 1 den 4.2

	int nEntropyMode; //CAVLC or CABAC. Note rang CABAC khong ho trong trong baseline
	int nRateControlMode; //0: CBR,1 VBR
	int nSenceDectect; //1 enable, 0 disable

	int nBitrate; //Tinh theo kilobit

	int nContentEncoder; //1: Content 0:Source

	//lien quan den cac thu khac
	int nWidth;  //frame width
	int nHeight; //frame height
	int nIdrPicture; //khoang cach giua 2 frame I

	int nFrameRate; // 0 full, 15: 1, 10:2,5:3
	int nColor;  //0 PAL,1 NTSC
	int nSource; //0: Composite, 1: SVideo

}VSS_SETTING;


class CEncoder
{
protected:

public:
	CEncoder(void);
	virtual ~CEncoder(void);

	virtual int setting(void* pParam) { return 0; }
	virtual int getVideoSetting(void* pParam) { return 0; }
	virtual int Init()=0;
	virtual int Exit() {return 0;};
	virtual int encode(char** pData, unsigned long dwSize, unsigned long dwTS) {return 0; }

	virtual int changeBitrate(int nNewBitrate) { return 0; }
	virtual int fastUpdate() { return 0; }


};

#endif
