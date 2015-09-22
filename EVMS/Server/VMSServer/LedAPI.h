#ifndef _LED_API_CLASS_HEADER_
#define _LED_API_CLASS_HEADER_

#pragma once
#include <Windows.h>
#include <string>  
#include <fstream>  
using namespace std;

#define CONTROLLER_AX_UL            0x2055 
#define CONTROLLER_AX_UT            0x2155 
#define CONTROLLER_AX_U0            0x2255 
#define CONTROLLER_AX_U1            0x2355 
#define CONTROLLER_AX_U2            0x2455 
#define CONTROLLER_AX_MT            0x2052 
#define CONTROLLER_AX_M1            0x2152 
#define CONTROLLER_AX_M2            0x2252 
#define CONTROLLER_AX_M3            0x2352 
#define CONTROLLER_AX_M4            0x2452 
#define CONTROLLER_AX_AT            0x2051 
#define CONTROLLER_AX_A0            0x2151
#define CONTROLLER_BX_5UL           0x0855 
#define CONTROLLER_BX_5UT           0x0055 
#define CONTROLLER_BX_5U0           0x0155 
#define CONTROLLER_BX_5U1           0x0255
#define CONTROLLER_BX_5U2           0x0355 
#define CONTROLLER_BX_5U3           0x0455 
#define CONTROLLER_BX_5U4           0x0555 
#define CONTROLLER_BX_5U5           0x0655 
#define CONTROLLER_BX_5U            0x0755
#define CONTROLLER_BX_5MT           0x0552 
#define CONTROLLER_BX_5M1           0x0052 
#define CONTROLLER_BX_5M1X          0x0152 
#define CONTROLLER_BX_5M2           0x0252 
#define CONTROLLER_BX_5M3           0x0352 
#define CONTROLLER_BX_5M4           0x0452
#define CONTROLLER_BX_5E1           0x0154 
#define CONTROLLER_BX_5E2           0x0254 
#define CONTROLLER_BX_5E3           0x0354
#define CONTROLLER_BX_5AL           0x1851 
#define CONTROLLER_BX_5AT           0x0051 
#define CONTROLLER_BX_5AT_WIFI      0x1651 
#define CONTROLLER_BX_5A0           0x0151 
#define CONTROLLER_BX_5A1           0x0251 
#define CONTROLLER_BX_5A1_WIFI      0x0651 
#define CONTROLLER_BX_5A            0x0951 
#define CONTROLLER_BX_5A2           0x0351 
#define CONTROLLER_BX_5A2_RF        0x1351 
#define CONTROLLER_BX_5A2_WIFI      0x0751 
#define CONTROLLER_BX_5A3           0x0451 
#define CONTROLLER_BX_5A4           0x0551 
#define CONTROLLER_BX_5A4_RF        0x1551 
#define CONTROLLER_BX_5A4_WIFI      0x0851
#define CONTROLLER_BX_5Q0           0x0056 
#define CONTROLLER_BX_5Q1           0x0156 
#define CONTROLLER_BX_5Q2           0x0256 
#define CONTROLLER_BX_5Q0P         	0x1056 
#define CONTROLLER_BX_5Q1P          0x1156 
#define CONTROLLER_BX_5Q2P          0x1256 
#define CONTROLLER_BX_5QL           0x1356
#define CONTROLLER_BX_5QS1          0x0157 
#define CONTROLLER_BX_5QS2          0x0257 
#define CONTROLLER_BX_5QS           0x0357
#define CONTROLLER_BX_5QS1P         0x1157 
#define CONTROLLER_BX_5QS2P         0x1257 
#define CONTROLLER_BX_5QSP          0x1357 

//---------------------------------ERROR---------------------------------------------
#define   RETURN_ERROR_AERETYPE        		0xF7 //Area type is wrong. If users get error when add or delete Graphic&Text area, will return to there.。 
#define   RETURN_ERROR_RA_SCREENNO 			0xF8  //Already has this screen information. If users want to reset , please “DeleteScreen” delet this screen first, and then, add new one. 
#define   RETURN_ERROR_NOFIND_AREAFILE 		0xF9 //Do not find out valid area file (Graphic&Text area); 
#define   RETURN_ERROR_NOFIND_AREA 			0xFA //Do not find out valid display area; can use AddScreenProgramBmpTextArea to add area information. 
#define   RETURN_ERROR_NOFIND_PROGRAM		0xFB //Do not find out valid display area; can useAddScreenProgramto add program. 
#define   RETURN_ERROR_NOFIND_SCREENNO		0xFC //Do not find this screen in the system; can use AddScreen. 
#define   RETURN_ERROR_NOW_SENDING 			0xFD //It’s communicating now, please try again later. 
#define   RETURN_ERROR_NOSUPPORT_USB 		0xF6 //Do not support USB mode 
#define   RETURN_ERROR_NO_USB_DISK 			0xF5 //Can’t find usb route. 
#define   RETURN_ERROR_OTHER 				0xFF //Other error. 
#define   RETURN_NOERROR					0


// Parametter
#define SCREEN_NO   1 
//Screen number; This parameter is the same with LedshowTW 2015"
#define SCREEN_TYPE_SINGLE		1
#define SCREEN_TYPE_DOUBLE		2
#define SCREEN_TYPE_TRICOLOR	3
#define SCREEN_TYPE_FULL		4
#define SCREEN_TYPE_SING_DOUBLE 5
//1: Single color; 
//2: Double color; 
//3: Tri color; Note: Only supported by BX-4MC; and this type does not support any other type screen. 
//4: Full color; Note: Only supported by BX-5Q series; and this type does not support any other type screen. 
//5: Single and double color with gray scale; Note: Only supported by BX-5QS series and this type does not support any other type screen

#define SCREEN_PIXEL_MODE       1 //1: R+G; 2:G+R; This parameter is valid to double color, Default is 2
#define SCREEN_DATADA   1 //Data polarity;, 0x00: Data polarity is low, 0x01: Data polarity is high; Default is 0
#define SCREEN_DATAOE	 0 //OE polarity; 0x00:OE low; 0x01: OE high; Default is 0
#define SCREEN_ROWORDER  0 //Line mode; 0: normal; 1: add one line; 2: cut one line; Default is 
#define SCREEN_FREQPAR   0 //Scan frequency; 0~6; Default is 0;
#define SCREEN_COMM		"COM1" //Serial port name; It’s valid when it’s serialp ort communication; Like: COM1

#define SCREEN_BAUD_57600   57600 //Serial baud rate: In present, support 9600, 57600; Default is 57600
#define SCREEN_BAUD_9600   9600

#define SCREEN_FREQPAR		0 //Scan frequency; 0~6; Default is 0;

#define SEND_MODE_COMM   0
#define SEND_MODE_NET   2

///Single line or multi line display; 
//1: single line display; 
//0: multiline display; 
//It’s valid when it’s txt format on pFileName.
#define SHOW_SINGLE_LINE 1  
#define SHOW_MULTI_LINE  0

//
//Display mode 
//0x00: Random 
//0x01: Static 
//0x02: Direct show //0x03: Move left //0x04: Continuously move left 
//0x05: move up 3T cards do not support it //0x06: Continuously move up 3T cards do not support it 
//0x07: Flicker 3T cards do not support it //0x08: Snowing //0x09: Bubbling 
//0x0A: Middle out //0x0B: Moved around //0x0C: Horizontal crossmove 
//0x0D: Vertical crossmove //0x0E: Scroll closed //0x0F: Scroll opened 
//0x10: Left Stretch //0x11: Right Stretch //0x12: Up Stretch 
//0x13: Down Stretch 3T cardsdo not support it //0x14: Left Laser 
//0x15: Right Laser //0x16: Up Laser //0x17: Down Laser 
//0x18: Cross curtain left and right //0x19: Cross curtain up and down
//0x1A: Curtain scattered to the left //0x1B: Horizontal blinds 3T、3A、4A、 3A1、3A2、4A1、4A2、4A3、4AQ cards do not support it 
//0x1C: Vertical blinds 3T、3A、4A、3A1、 3A2、4A1、4A2、4A3、4AQ、3M、4M、 4M1、4MCcards do not support it 
//0x1D: Curtain left 3T、3A、4A cards do not support it //0x1E: Curtain right 3T、3A、4A cards do not support it 
//0x1F: Curtain up 3T、3A、4A cards do not support it //0x20: Curtain down 3T、3A、4A cards do not support it 
//0x21: Move to center from left to right 3T cards do not support it //0x22: Split to left and right 3T cards do not support it 
//0x23: Move to center from up and down 3T cards do not support it //0x24: Splite to up and down 3T cards do not support it 
//0x25: Move right //0x26: Continuously move right //0x27: Move down 3T cards do not support it 
//0x28: Continuously move down 3T cards do not support it 
#define DISPLAY_MODE_STATIC 0x01

//Run speed
//Run speed; 0~63;It will be slower if the value is bigger.
#define RUN_SPEED 30

// ÓÃ»§·¢ËÍÐÅÏ¢ÃüÁî±í
#define SEND_CMD_PARAMETER   0xA1FF //¼ÓÔØÆÁ²ÎÊý¡£
#define SEND_CMD_SCREENSCAN   0xA1FE //ÉèÖÃÉ¨Ãè·½Ê½¡£
#define SEND_CMD_SENDALLPROGRAM   0xA1F0 //·¢ËÍËùÓÐ½ÚÄ¿ÐÅÏ¢¡£
#define SEND_CMD_POWERON   0xA2FF //Ç¿ÖÆ¿ª»ú
#define SEND_CMD_POWEROFF   0xA2FE //Ç¿ÖÆ¹Ø»ú
#define SEND_CMD_TIMERPOWERONOFF   0xA2FD //¶¨Ê±¿ª¹Ø»ú
#define  SEND_CMD_CANCEL_TIMERPOWERONOFF   0xA2FC //È¡Ïû¶¨Ê±¿ª¹Ø»ú
#define SEND_CMD_RESIVETIME   0xA2FB //Ð£ÕýÊ±¼ä¡£
#define SEND_CMD_ADJUSTLIGHT   0xA2FA //ÁÁ¶Èµ÷Õû¡£

//NETWORK
#define SCREEN_WIDTH   64
#define SCREEN_HEIGHT   64
       
#define SCREEN_SOCKETIP		"192.168.6.237"
#define SCREEN_SOCKETPORT   5005
//END-----------------------------------------------------------------//

//BEGIN----------------------------------------------------------------
//-Function: InitDLLResource
//-Input: HANDLE hHandle: handle of application
//-return: Integer
//---------------------------------------------------------------------
typedef int(__stdcall *InitDLLResource)(HANDLE hHandle); 
//END------------------------------------------------------------------//

//BEGIN-----------------------------------------------------------------
//-Function: FreeDLLResource
//-Input:
//-return: integer
//---------------------------------------------------------------------
typedef void(__stdcall *FreeDLLResource)(); 
//END------------------------------------------------------------------//


//BEGIN-----------------------------------------------------------------
//-Function: AddScreen
//-Input:
//		-int nControlType:Controller mode in Hexadecimal
//		-int nScreenNo: screen number (1....x)
//		-int nWidth: width of display screen: integral multiple of 16; 
//		-int nHeight: Height of the display screen: integral multiple of 16
//		-int nScreenType: Type of display screen: 1:single color; 2:dual color; 3:RGB
//			NOTE: Only BX-4MC supports RGB
//		-int nPixelMode: pixel type; 1:R+G; 2:G+R; This parameters only support dual color; Default:2
//		-int nDataDA: Data polarity: 0x00; Negative:0x01; Default: 0;
//		-int mDataOE: OE polarity: OE low:0x00; OE hight:0x01; Default:0
//		-int nRowOrder: Row order mode; 0:normal; 1:add one line; 2: delete one line; Default:0
//		-int nFreqPar: Scan frequency: 0~6; Default:0
//		-char* pCom: Serial Port name; Valid in serial port communication mode; Ex: COM1
//		-int nBaud: Serial port baud rate: currently with 9600, 57600; Default:57600
//			NOTE: BX-3T only support 9600 baud rate
//		-char* pSocketIP: Controller IP address;  Valid in Ethernet communication mode; Ex: "192.168.0.235"
//		-int* pSocketPort: Controller ethernet port; Valid in Ethernet communication mode; Ex: 5005
//		-char* pScreenStatusFile: The saved INI file name which used for saving found display screen status parameters
//-return: integer
//---------------------------------------------------------------------

typedef int(__stdcall *AddScreen)(int nControlType,int nScreenNo,int nWidth,int nHeight,int nScreenType,
								  int nPixelMode,int nDataDA,int nDataOE,int nRowOrder,int nFreqPar,
								  char* pCom,int nBaud,char* pSocketIP,int nSocketPort,char* pScreenStatusFile);


//END--------------------------------------------------------------------//


//BEGIN-----------------------------------------------------------------
//-Function: AddScreenProgram
//-Input:
//		-int nScreenNo: screen number (1....x)
//		-int nProgramType: Program type; 0: normal program
//		-int nPlayLength: 0:automatically play by order, or the length of the playing program; 
//				Range: 1~65535; Unit: Seconds
//		-int nStartYear: The period of program: the year when you play. If it's without litmit, then the parameter is 65535; like: 2010
//		-int nStartMonth: The period of program: the month when you play. Like: 11
//		-int nStartDay: The period of program: the date when you play. Like 24
//		-int nEndYear: The period of program: The year when you stop playing. Like 2014
//		-int nEndMonth:	The period of program: the month when you stop playing. Like: 12
//		-int nEndDay: The period of program: the date when you stop playing. Like 22
//		-int nMonPlay: It plays or not on Monday in the period of program; 0:no; 1:yes
//		-int nTuesPlay: It plays or not on Tuesday in the period of program; 0:no; 1:yes
//		-int nWedPlay: It plays or not on Wednesday in the period of program; 0:no; 1:yes
//		-int nThursPlay: It plays or not on Thursday in the period of program; 0:no; 1:yes
//		-int nFriPlay: It plays or not on Friday in the period of program; 0:no; 1:yes
//		-int nSatPlay: It plays or not on Saturday in the period of program; 0:no; 1:yes
//		-int nSunPlay: It plays or not on Sunday in the period of program; 0:no; 1:yes
//		-int nStartHour: The time start to play (hour) at that day. Like: 8
//		-int nStartMinute: The time start to play (Minute) at that day. Like: 8
//		-int nEndHour: The time stop to play (hour) at that day. Like: 8
//		-int nEndMinute: The time stop to play (minute) at that day. Like: 8
//-return: integer
//---------------------------------------------------------------------
typedef int(__stdcall *AddScreenProgram)(int nScreenNo,int nProgramType,int nPlayLength,int nStartYear,
										 int nStartMonth,int nStartDay,int nEndYear,int nEndMonth,int nEndDay,
										 int nMonPlay,int nTuesPlay,int nWedPlay,int nThursPlay,int nFriPlay,
										 int nSatPlay,int nSunPlay,int nStartHour,int nStartMinute,int nEndHour,
										 int nEndMinute);

//END--------------------------------------------------------------------//


//BEGIN-----------------------------------------------------------------
//-Function: AddScreenProgramBmpTextArea
//-Input:
//		-int nScreenNo: screen number (1....x)
//		-int nProgramOrd: program number (0....x)
//		-int nX: the adscissa of area; On the top left corner of the display screen, the abscissa is 0; 
//				minimum value is 0
//		-int nY: the ordinate of area; On the top left corner of the display screen, the abscissa is 0; 
//				minimum value is 0
//		-int nWidth: the width of area; The maximum value does not bigger than the width of display screen- nX
//		-int nHeight: the height of area; The maximum value does not bigger than the height of display screen- nY
//-return: integer
//---------------------------------------------------------------------
typedef int(__stdcall *AddScreenProgramBmpTextArea)(int nScreenNo,int nProgramOrd,
						int nX,int nY,int nWidth,int nHeight);   
//END--------------------------------------------------------------------//


//BEGIN-----------------------------------------------------------------
//-Function: AddScreenProgramAreaBmpTextFile
//-Input:
//		-int nScreenNo: screen number (1....x)
//		-int nProgramOrd: program number (0....x)
//		-int nAreaOrd: Area number (0....x)
//		-int nSingle: single row or multiple rows; 0: single row; 1: multiple rows;
//		-char* pFileName: File name: support *.bmp, *.txt, *.rft
//			"add TXT file". It supports the function of end to end when the display mode is 
//			continuous move left or continuous move right
//		-int nFontName: font name; Support the current installed vector font; this parameter is valid when
//			pFileName is txt format.
//		-int nFontSize: font size; support the current size; this parameter is valid when
//			pFileName is txt format.
//		-int nBold: Font bold; support the current size; this parameter is valid when
//			pFileName is txt format.
//		-int nFontColor: Font color; 
//			0:black
//			1:red
//			2:green
//			3:yellow
//			4:blue
//			5:mauve
//			6:light green
//			7:white
//			This parameter is valid when pFileName is txt format
//		-int nStunt: Display mode
//		-int nRunSpeed: running speed: 0~63 (bigger is slower)
//		-int nShowTime: Hold time; 0~65525; unit:0.5 seconds
//-return: integer
//---------------------------------------------------------------------

//Red 255;Green65280;Yellow65535
#define	BLACK			0	//black
#define	RED				1	//red
#define	GREEN			2	//green
#define	YELLOW			3	//yellow
#define	BLUE			4	//blue
#define	MAUVE			5	//mauve
#define	LIGHT_GREEN		6	//light green
#define	WHITE			7	//white
typedef int(__stdcall *AddScreenProgramAreaBmpTextFile)(int nScreenNo,int nProgramOrd,int nAreaOrd,
						char* pFileName,int nShowSingle, char* pFontName,int nFontSize,
						int nBold,int nFontColor,int nStunt,int nRunSpeed,int nShowTime);
//END--------------------------------------------------------------------//


//BEGIN---------------------------------------------------------------------
//-Function: int DeleteScreen 
//-Input: 
//		-int nScreenNo: screen number (1....x)
//-return: integer
//------------------------------------------------------------------------
typedef int(__stdcall *DeleteScreen)(int nScreenNo);
//END--------------------------------------------------------------------//


//BEGIN---------------------------------------------------------------------
//-Function: int DeleteScreenProgram
//-Input: 
//		-int nScreenNo: screen number (1....x)
//		-int nProgramOrd: program number (0....x)
//-return: integer
//------------------------------------------------------------------------
typedef int(__stdcall *DeleteScreenProgram)(int nScreenNo, int nProgramOrd);
//END-------------------------------------------------------------------------//


//BEGIN--------------------------------------------------------------------
//-Function: int DeleteScreenProgramArea
//-Input: 
//		-int nScreenNo: screen number (1....x)
//		-int nProgramOrd: program number (0....x)
//		-int nAreaOrd: Area number (0....x)
//-return: integer
//------------------------------------------------------------------------
typedef int(__stdcall *DeleteScreenProgramArea)(int nScreenNo, int nProgramOrd, int nAreaOrd);
//END---------------------------------------------------------------------//



//BEGIN--------------------------------------------------------------------
//-Function: int SetScreenTimerPowerONOFF
//-Input: 
//		-int nScreenNo: screen number (1....x)
//		-int nOnHour1: the hour for On of group automatic ON/OFF
//		-int nOnMinute1:  the minute for On of group automatic ON/OFF
//		-int nOffHour1: the hour for Off of group automatic ON/OFF
//		-int nOffMinute1: the minute for Off of group automatic ON/OFF
//		-int nOnHour2: the hour for On of second group automatic ON/OFF
//		-int nOnMinute2:  the minute for On of second group automatic ON/OFF
//		-int nOffHour2: the hour for Off of second group automatic ON/OFF
//		-int nOffMinute2: the minute for Off of second group automatic ON/OFF
//		-int nOnHour3: the hour for On of third group automatic ON/OFF
//		-int nOnMinute3:  the minute for On of third group automatic ON/OFF
//		-int nOffHour3: the hour for Off of group third automatic ON/OFF
//		-int nOffMinute3: the minute for Off of third group automatic ON/OFF
//-return: integer
//------------------------------------------------------------------------
typedef int(__stdcall *SetScreenTimerPowerONOFF)(int nScreenNo, 
						int nOnHour1, int nOnMinute1, int nOffHour1, int nOffMinute1,
						int nOnHour2, int nOnMinute2, int nOffHour2, int nOffMinute2,
						int nOnHour3, int nOnMinute3, int nOffHour3, int nOffMinute3);
//END----------------------------------------------------------------------//


//BEGIN--------------------------------------------------------------------
//-Function: int SetScreenAdjustLight
//-Input: 
//		-int nScreenNo: screen number (1....x)
//		-int nAdjustType: type of adjusting brightness; 0: manually; 1: automatically
//		-int nHandleLight: the brightness value of manually adjust brightness; valid when nAdjustType = 0
//		-int nHour1: the time (hour) for the first group automatically brightness
//		-int nMinute1: The time (minute) for the first group automatically brightness
//		-int nLight1: the brightness value for the first group automatically brightness
//		-int nHour2: the time (hour) for the second group automatically brightness
//		-int nMinute2: The time (minute) for the second group automatically brightness
//		-int nLight2: the brightness value for the second group automatically brightness
//		-int nHour3: the time (hour) for the third group automatically brightness
//		-int nMinute3: The time (minute) for the third group automatically brightness
//		-int nLight13: the brightness value for the third group automatically brightness
//		-int nHour4: the time (hour) for the forth group automatically brightness
//		-int nMinute4: The time (minute) for the forth group automatically brightness
//		-int nLight14: the brightness value for the forth group automatically brightness
//-return: integer
//------------------------------------------------------------------------
typedef int(__stdcall *SetScreenAdjustLight)(int nScreenNo, int nAdjustType, int nHandleLight,
						int nHour1, int nMinute1, int nLight1,
						int nHour2, int nMinute2, int nLight2,
						int nHour3, int nMinute3, int nLight3,
						int nHour4, int nMinute4, int nLight4);
//END---------------------------------------------------------------------//


//BEGIN--------------------------------------------------------------------
//-Function: int SaveUSBScreenInfo
//-Input: 
//		-int nScreenNo: screen number (1....x)
//		-int nCorrectTime: Correcting time or not; 1: correcting time; 0 not correcting time
//				(NOTE: only support panel: BX-4UT, BX-4U0, BX-4U1, BX-4U2, BX-4U3). 
//		-int nAdvanceHour: the advanced hour of the correction time with the current computer. 
//				Range: 0 - 23; Only valid when bCorrectTime = 1				
//		-int nAdvanceMinute: The advanced minute of the correction time with the current computer.
//				Range: 0 - 59; Only valid when bCorrection = 1
//		-char pUsbDisk: Usb equipment route name; Format is "xx;\"; like: "F:\"
//-return: integer
//------------------------------------------------------------------------
typedef int(__stdcall *SaveUSBScreenInfo)(int nScreenNo,int nCorrectTime,
						int nAdvanceHour,int nAdvanceMinute, char* pUsbDisk);
//END----------------------------------------------------------------------//


//BEGIN--------------------------------------------------------------------
//-Function: int AddScreenProgramTimeArea
//-Input: 
//		-int nScreenNo: screen number (1....x)
//		-int nProgramOrd: program number (0....x)
//		-int nX: the adscissa of area; On the top left corner of the display screen, the abscissa is 0; 
//				minimum value is 0
//		-int nY: the ordinate of area; On the top left corner of the display screen, the abscissa is 0; 
//				minimum value is 0
//		-int nWidth: the width of area; The maximum value does not bigger than the width of display screen- nX
//		-int nHeight: the height of area; The maximum value does not bigger than the height of display screen- nY
//-return: integer
//------------------------------------------------------------------------
typedef int(__stdcall *AddScreenProgramTimeArea)(int nScreenNo,int nProgramOrd, int nX, int nY, int nWidth, int nHeight);
//END----------------------------------------------------------------------//



//BEGIN--------------------------------------------------------------------
//-Function: int AddScreenProgramTimeAreaFile
//-Input: 
//		-int nScreenNo: screen number (1....x)
//		-int nProgramOrd: program number (0....x)
//		-int nAreaOrd: area number (0....x)
//		-char* pInputTxt: fixed words
//		-char* pFontName: word's font
//		-int nSingle: single row or multiple rows; 0: single row; 1: multiple rows;
//				And nAlign does not worked in single row
//		-int nAlign: Text alignment mode is valid to multiple rows; 0:left;1:midle;2:right
//		-int nBold: bold or not; 0: no; 1: yes
//		-int nItalic: italic or not; 0: no; 1: yes
//		-int nUnderline: underline or not; 0: no; 1: yes
//		-int nUseTxt: Used fixed words or not; 0: no; 1: yes
//		-int nTxtColor: Fixed words color, decimalism of transferring color: red:255; green:65280; yellow: 65535
//		-int nUseYmd: use year/month/day or not; 0:no; 1:yes
//		-int nYmdStype: Format of year/month/day, listed below
//		-int nYmdColor: color of year/month/day. decimalism of transferring color
//		-int nUseWeek: use week or not; 0:no; 1:yes
//		-int nWeekStype: Week format, list below
//		-int nWeekColor: Week color, decimalism of transferring color
//		-int nUseHns: use hour/minute/seconds or not; 0:no; 1:yes
//		-int nHnsStype: hour/minute/seconds format, listed below
//		-int nHnsColor: hour/minute/seconds color, decimalism of transferring color
//		-int nAutoSet: automatically set corresponding width or not; 0:no; 1:yes (default:no)
//-return: integer
//------------------------------------------------------------------------
typedef int (__stdcall *AddScreenProgramTimeAreaFile)(int nScreenNo, int nProgramOrd, int nAreaOrd,
							char* pInputTxt, char* pFontName, int nSingleRow, int nAlign, int nBold,
							int nItalic, int nUnderLine, int nUseTxt, int nTxtColor, int nUseYmd,
							int nYmdStype, int nYmdColor, int nUseWeek, int nWeekColor, int nUseHns,
							int nHnsStype, int nHnsColor, int nAutoSet);
//END---------------------------------------------------------------------//



//BEGIN--------------------------------------------------------------------
//-Function: int AddScreenProgramClockArea
//-Input: 
//		-int nScreenNo: screen number (1....x)
//		-int nProgramOrd: program number (0....x)
//		-int nX: the adscissa of area; On the top left corner of the display screen, the abscissa is 0; 
//				minimum value is 0
//		-int nY: the ordinate of area; On the top left corner of the display screen, the abscissa is 0; 
//				minimum value is 0
//		-int nWidth: the width of area; The maximum value does not bigger than the width of display screen- nX
//		-int nHeight: the height of area; The maximum value does not bigger than the height of display screen- nY
//-return: integer
//------------------------------------------------------------------------
typedef int(__stdcall *AddScreenProgramClockArea)(int nScreenNo,int nProgramOrd, int nX, int nY, int nWidth, int nHeight);
//END----------------------------------------------------------------------//


//BEGIN--------------------------------------------------------------------
//-Function: int AddScreenProgramClockAreaFile
//-Input: 
//		-int nScreenNo: screen number (1....x)
//		-int nProgramOrd: program number (0....x)
//		-int nAreaOrd: area number (0....x)
//		-char* pInputTxt: fixed words
//		-char* pFontName: word's font
//		-int nSingle: single row or multiple rows; 0: single row; 1: multiple rows;
//				And nAlign does not worked in single row
//		-int nAlign: Text alignment mode is valid to multiple rows; 0:left;1:midle;2:right
//		-int nBold: bold or not; 0: no; 1: yes
//		-int nItalic: italic or not; 0: no; 1: yes
//		-int nUnderline: underline or not; 0: no; 1: yes
//		-int nUseTxt: Used fixed words or not; 0: no; 1: yes
//		-int nTxtColor: Fixed words color, decimalism of transferring color: red:255; green:65280; yellow: 65535
//		-int nUseYmd: use year/month/day or not; 0:no; 1:yes
//		-int nYmdStype: Format of year/month/day, listed below
//		-int nYmdColor: color of year/month/day. decimalism of transferring color
//		-int nUseWeek: use week or not; 0:no; 1:yes
//		-int nWeekStype: Week format, list below
//		-int nWeekColor: Week color, decimalism of transferring color
//		-int nUseHns: use hour/minute/seconds or not; 0:no; 1:yes
//		-int nHnsStype: hour/minute/seconds format, listed below
//		-int nHnsColor: hour/minute/seconds color, decimalism of transferring color
//		-int nAutoSet: automatically set corresponding width or not; 0:no; 1:yes (default:no)
//		-char* pXXXFontName: word font
//		-int nXXXSize: object size 0-8
//-return: integer
//------------------------------------------------------------------------
typedef int (__stdcall *AddScreenProgramClockAreaFile)(int nScreenNo, int nProgramOrd, int nAreaOrd,
	int nUseTxt, int nUseTime, int nUseWeek, 
	int nTimeStype, int nWeekStype, 
	int nTxtFontSize, int nTxtFontColor, int nTxtBold, int nTxtItalic, int nTxtUnderLine, 
	char* pTxtLeft, char* pTxtTop, 
	int nWeekFontSize, int nWeekFontColor, int nWeekBold, int nWeekItalic, int nWeekUnderLine,
	char* pWeekLeft, char* pWeekTop,
	int nClockFontSize, int nClockFontColor, int nClockBold, int nClockItalic, int nClockUnderLine,
	int nClockCenterSize, int nClockCenterColor, 
	int nMhrdotStype, int nMhrdotSize, int nMhrdotColor, 
	int nHrdotStype, int nHrdotSize, int nHrdotColor, 
	int nMindotStype,int nMindotSize, int nMindotColor,
	int nHrhandStype, int nHrhandSize, int nHrhandColor,
	int nMinhandStype, int nMinhandSize, int nMinhandColor,
	int nSechandStype,int nSechandSize, int nSechandColor,
	int nAutoSet, char* pTxtContent, char* pTxtFontName, 
	char* pTimeFontName, char* pWeekFontName, char* pClockFontName);
//END---------------------------------------------------------------------//


//BEGIN--------------------------------------------------------------------
//-Function: int GetScreenStatus
//-Input: 
//		-int nScreenNo: screen number (1....x)
//		-int nSendMode: method communicate with panel
//-return: integer
//------------------------------------------------------------------------
typedef int(__stdcall *GetScreenStatus) (int nScreenNo, int nSendMode);
//END----------------------------------------------------------------------//


//BEGIN--------------------------------------------------------------------
//-Function: int SendScreenInfo
//-Input: 
//		-int nScreenNo: screen number (1....x)
//		-int nSendMode: method communicate with panel
//		-int nSendCmd: command parameter
//		-int nOtherParam: other parameter
//-return: integer
//------------------------------------------------------------------------
typedef int(__stdcall *SendScreenInfo)(int nScreenNo,int nSendMode,int nSendCmd,int nOtherParam1);
//END----------------------------------------------------------------------//

class VMSLedCtrl
{
public:
	VMSLedCtrl();
	virtual ~VMSLedCtrl();

	void InitDLL()
	{
		hInst = NULL;
		hInst = LoadLibrary(_T("BX_IV.dll"));

		api_AddScreen=(AddScreen)GetProcAddress(hInst,"AddScreen");
		api_AddScreenProgram=(AddScreenProgram)GetProcAddress(hInst,"AddScreenProgram");
		api_AddScreenProgramBmpTextArea=(AddScreenProgramBmpTextArea)GetProcAddress(hInst,"AddScreenProgramBmpTextArea");
		api_AddScreenProgramAreaBmpTextFile=(AddScreenProgramAreaBmpTextFile)GetProcAddress(hInst,"AddScreenProgramAreaBmpTextFile");
		api_SendScreenInfo=(SendScreenInfo)GetProcAddress(hInst,"SendScreenInfo");

		api_GetScreenStatus=(GetScreenStatus)GetProcAddress(hInst,"GetScreenStatus");

		api_InitDLLResource=(InitDLLResource)GetProcAddress(hInst,"InitDLLResource");
		api_FreeDLLResource=(FreeDLLResource)GetProcAddress(hInst,"FreeDLLResource");
		api_SetScreenAdjustLight = (SetScreenAdjustLight)GetProcAddress(hInst, "SetScreenAdjustLight");
		api_SaveUsbCreenInfo = (SaveUSBScreenInfo)GetProcAddress(hInst, "SaveUSBScreenInfo");
		int nResult=api_InitDLLResource(NULL);	
		assert(nResult == 0);

	}

	int InitBoard(int nScreenNo, char* pIp, int nType, int nWidth, int nHeight, int nColor, int screenData );
	
	int SetImageFileToBoard(int nScreenNo, char* pFileBmp, int nStunt, int nRunSpeed, int nShowTime,
		int nX, int nY, int nWidth, int nHeight);

	int SetTextFileToBoard(int nScreenNo, char* pFileTxt, char* pFontName, int nFontSize, 
		int nBold, int nColor, int nStunt, int nRunSpeed, int nShowTime,
		int nX, int nY, int nWidth, int nHeight);

	int SetAjustLight(int nScreenNo, int nAdjustType, int nHandleLight,
		int nHour1, int nMinute1, int nLight1,
		int nHour2, int nMinute2, int nLight2,
		int nHour3, int nMinute3, int nLight3,
		int nHour4, int nMinute4, int nLight4);

	int SetContentToBoard(int nScreenNo, int nRow, 
		char* pFile1, int nX1, int nY1, int nHeight1, int nWidth1,
		char* pFontName1, int nFontSize1,  int nBold1, int nColor1, int nStunt1, int nRunSpeed1, int nShowTime1,
		char* pFile2, int nX2, int nY2, int nHeight2, int nWidth2,
		char* pFontName2, int nFontSize2,  int nBold2, int nColor2, int nStunt2, int nRunSpeed2, int nShowTime2);



	int DoDeleteScreen();

	void FreeDLL()
	{
		api_FreeDLLResource();
		FreeLibrary(hInst);
	}

public:          
	HINSTANCE hInst;

	AddScreen api_AddScreen;
	BOOL m_bSendBusy;//´Ë±äÁ¿ÔÚÊý¾Ý¸üÐÂÖÐ·Ç³£ÖØÒª£¬ÇëÎñ±Ø±£Áô¡£

	AddScreenProgram api_AddScreenProgram;
	AddScreenProgramBmpTextArea api_AddScreenProgramBmpTextArea;
	AddScreenProgramAreaBmpTextFile api_AddScreenProgramAreaBmpTextFile;
	SendScreenInfo api_SendScreenInfo;
	GetScreenStatus api_GetScreenStatus;
	SetScreenAdjustLight api_SetScreenAdjustLight;
	SaveUSBScreenInfo api_SaveUsbCreenInfo;
	InitDLLResource api_InitDLLResource;
	FreeDLLResource api_FreeDLLResource;  
	DeleteScreen api_DeleteScreen;
	DeleteScreenProgram api_DeleteScreenProgram;
	DeleteScreenProgramArea api_DeleteScreenProgramArea;
	
};


 #endif