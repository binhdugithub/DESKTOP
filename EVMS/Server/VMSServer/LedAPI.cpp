#include "stdafx.h"
#include "LedAPI.h"
#include <Windows.h>
#include <iostream>



VMSLedCtrl::VMSLedCtrl()
{
	hInst = NULL;
	/*hInst = LoadLibrary(_T("BX_IV.dll"));

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

	api_DeleteScreen=(DeleteScreen)GetProcAddress(hInst, "DeleteScreen");
	api_DeleteScreenProgram=(DeleteScreenProgram)GetProcAddress(hInst, "DeleteScreenProgram");
	api_DeleteScreenProgramArea=(DeleteScreenProgramArea)GetProcAddress(hInst, "DeleteScreenProgramArea");

	int nResult=api_InitDLLResource(NULL);	
	assert(!nResult);*/
}

VMSLedCtrl::~VMSLedCtrl()
{

}

int VMSLedCtrl::InitBoard( int nScreenNo, char* pIp, int nType, int nWidth, int nHeight, int nColor, int screenData  )
{
	int nResult = 0;

	nResult = api_AddScreen(nType, nScreenNo, nWidth, nHeight
		, nColor, SCREEN_PIXEL_MODE, screenData, SCREEN_DATAOE
		, SCREEN_ROWORDER, SCREEN_FREQPAR,SCREEN_COMM
		, SCREEN_BAUD_57600, pIp, SCREEN_SOCKETPORT, "ScreenStatus.ini");
	
	if(nResult == 248)
	{
		nResult = api_DeleteScreen(nScreenNo);
		FAIL_FUNC(nResult);

		nResult = api_AddScreen(nType, nScreenNo, nWidth, nHeight
		, nColor, SCREEN_PIXEL_MODE, screenData, SCREEN_DATAOE
		, SCREEN_ROWORDER, SCREEN_FREQPAR,SCREEN_COMM
		, SCREEN_BAUD_57600, pIp, SCREEN_SOCKETPORT, "ScreenStatus.ini");
	}
	
	return nResult;
}

int VMSLedCtrl::SetAjustLight(int nScreenNo, int nAdjustType, int nHandleLight, int nHour1, int nMinute1, int nLight1, int nHour2, int nMinute2, int nLight2, int nHour3, int nMinute3, int nLight3, int nHour4, int nMinute4, int nLight4 )
{
	int nResult = 0;
	
	nResult = api_SetScreenAdjustLight(nScreenNo, nAdjustType, nHandleLight,
		nHour1, nMinute1, nLight1,
		nHour2, nMinute2, nLight2,
		nHour3, nMinute3, nLight3,
		nHour4, nMinute4, nLight4);
	FAIL_FUNC(nResult);

	nResult = api_SendScreenInfo(nScreenNo, SEND_MODE_NET, SEND_CMD_ADJUSTLIGHT, 0);
	FAIL_FUNC(nResult);

	return nResult;
}

int VMSLedCtrl::DoDeleteScreen()
{
	int nResult = 0;
	return nResult;
}

int VMSLedCtrl::SetTextFileToBoard( int nScreenNo, char* pFileTxt, char* pFontName, int nFontSize, 
	int nBold, int nColor, int nStunt, int nRunSpeed, int nShowTime,
	int nX, int nY, int nWidth, int nHeight)
{
	int nResult = 0;

	nResult = api_SendScreenInfo(nScreenNo, SEND_MODE_NET, SEND_CMD_PARAMETER, 0);
	FAIL_FUNC(nResult);

	nResult = api_AddScreenProgram(nScreenNo, 0, 0, 65535, 1, 11, 2015, 11, 26, 1, 1, 1, 1, 1, 1, 1, 8, 0, 18, 0);
	FAIL_FUNC(nResult);

	nResult = api_AddScreenProgramBmpTextArea(nScreenNo, 0, nX, nY, nWidth, nHeight);
	FAIL_FUNC(nResult);

	nResult = api_AddScreenProgramAreaBmpTextFile(nScreenNo, 0, 0, pFileTxt,
		SHOW_SINGLE_LINE, pFontName, nFontSize, nBold, nColor, nStunt, nRunSpeed, nShowTime);
	FAIL_FUNC(nResult);

	nResult = api_SendScreenInfo(nScreenNo, SEND_MODE_NET, SEND_CMD_SENDALLPROGRAM, 0);
	FAIL_FUNC(nResult);

	return nResult;
}

int VMSLedCtrl::SetImageFileToBoard( int nScreenNo, char* pFileBmp, int nStunt, int nRunSpeed, int nShowTime,
	int nX , int nY, int nWidth, int nHeight)
{
	int nResult = 0;

	nResult = api_SendScreenInfo(nScreenNo, SEND_MODE_NET, SEND_CMD_PARAMETER, 0);
	std::cout<<"error : "<<nResult<<std::endl;
	FAIL_FUNC(nResult);

	nResult = api_AddScreenProgram(nScreenNo, 0, 0, 65535, 1, 11, 2013, 11, 26, 1, 1, 1, 1, 1, 1, 1, 8, 0, 18, 0);
	FAIL_FUNC(nResult);

	nResult = api_AddScreenProgramBmpTextArea(nScreenNo, 0, nX, nY, nWidth, nHeight);
	FAIL_FUNC(nResult);
	//12, 0, 65535, 4, 64, 0  //0, 1, 3, nStunt, nRunSpeed, nShowTime
	nResult = api_AddScreenProgramAreaBmpTextFile(nScreenNo, 0, 0, pFileBmp, 1, "", 0, 1, 3, nStunt, nRunSpeed, nShowTime);
	FAIL_FUNC(nResult);

	nResult = api_SendScreenInfo(nScreenNo, SEND_MODE_NET, SEND_CMD_SENDALLPROGRAM, 0);
	FAIL_FUNC(nResult);

	return nResult;
}


int VMSLedCtrl::SetContentToBoard( int nScreenNo, int nRow, char* pFile1, int nX1, int nY1, int nHeight1, int nWidth1, char* pFontName1, int nFontSize1, int nBold1, int nColor1, int nStunt1, int nRunSpeed1, int nShowTime1, char* pFile2, int nX2, int nY2, int nHeight2, int nWidth2, char* pFontName2, int nFontSize2, int nBold2, int nColor2, int nStunt2, int nRunSpeed2, int nShowTime2 )
{
	int nResult = 0;
	
	nResult = api_SendScreenInfo(nScreenNo, SEND_MODE_NET, SEND_CMD_PARAMETER, 0);
	FAIL_FUNC(nResult);

	nResult = api_AddScreenProgram(nScreenNo, 0, 0, 65535, 1, 11, 2013, 11, 26, 1, 1, 1, 1, 1, 1, 1, 8, 0, 18, 0);
	FAIL_FUNC(nResult);

	if(nRow == 1)
	{
		nResult = api_AddScreenProgramBmpTextArea(nScreenNo, 0, nX1, nY1, nWidth1, nHeight1);
		FAIL_FUNC(nResult);
		
		nResult = api_AddScreenProgramAreaBmpTextFile(nScreenNo, 0, 0, pFile1, 1, pFontName1, nFontSize1,
			nBold1, nColor1, nStunt1, nRunSpeed1, nShowTime1);
		FAIL_FUNC(nResult);
	}
	else
	{
		nResult = api_AddScreenProgramBmpTextArea(nScreenNo, 0, nX1, nY1, nWidth1, nHeight1);
		FAIL_FUNC(nResult);

		nResult = api_AddScreenProgramBmpTextArea(nScreenNo, 0, nX2, nY2, nWidth2, nHeight2);
		FAIL_FUNC(nResult);

		nResult = api_AddScreenProgramAreaBmpTextFile(nScreenNo, 0, 0, pFile1, 1, pFontName1, nFontSize1,
			nBold1, nColor1, nStunt1, nRunSpeed1, nShowTime1);
		FAIL_FUNC(nResult);

		nResult = api_AddScreenProgramAreaBmpTextFile(nScreenNo, 0, 1, pFile2, 1, pFontName2, nFontSize2,
			nBold2, nColor2, nStunt2, nRunSpeed2, nShowTime2);
		FAIL_FUNC(nResult);
	}

	nResult = api_SendScreenInfo(nScreenNo, SEND_MODE_NET, SEND_CMD_SENDALLPROGRAM, 0);
	FAIL_FUNC(nResult);
	
	return nResult;
}
