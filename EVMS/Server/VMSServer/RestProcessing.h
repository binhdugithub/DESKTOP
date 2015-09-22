#pragma once
#include <cpprest\http_client.h>
#include <cpprest\http_listener.h>
#include <cpprest\json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::http::experimental::listener;

#include <iostream>
#include <map>
#include <set>
#include <string>
#include "DatabaseInterface.h"
#include "LedController.h"

#define		LOGIN					1 	//Đăng nhập
#define		LOGOUT					2 	//Đăng xuất
#define		ADD_USER				20	//Thêm người dùng
#define		DELETE_USER				21	//Xóa	người dùng
#define		UPDATE_USER				22	//Sửa người dùng
#define		ADD_OBJECT					30	//Thêm VMS
#define		DELETE_OBJECT				31	//Xóa VMS
#define		UPDATE_OBJECT				32	//Sửa VMS
#define		ASSIGN_OBJECT				33	//Gán VMS
#define		ADD_PROGRAM				40	//Thêm chương trình
#define		UPDATE_PROGRAM			41	//Sửa  chương trình
#define		DELETE_PROGRAM			42	//Xóa  chương trình
#define		UPDATE_OBJECT_PROGRAM	50	//Cập nhật chương trình xuống VMS

using namespace std;

class RestProcessing
{
public:
	RestProcessing();
	virtual ~RestProcessing();
private:
	DatabaseInterface *m_DBInf;
	LedController *m_LEDCTRL;
public:
	json::value GenerateJsonCode(int pCode, std::string pDescription = std::string(""));
	json::value GenerateJsonCode(bool p_error, int p_status, std::string p_message = "", std::string p_description = "");
	bool IsHeaderJson(std::string p_header);

	void DontKnowRequest(http_request);
	void Login(http_request);
	void UpdateUser(http_request);
	void CreateUser(http_request);
	void GetListUser(http_request);

	void GetRole(http_request);

	void GetListObject(http_request);
	void AssignObject(http_request);
	void DeleteUser(http_request);
	void CreateObject(http_request);
	void DeleteObject(http_request);
	void UpdateObject(http_request);
	void UpdateObjectProgram(http_request p_request);

	void GetListProgram(http_request);
	void CreateProgram(http_request);
	void UpdateProgram(http_request);
	void DeleteProgram(http_request);
	void ShowHistory(http_request);

	void GetListDevice(http_request);
	void GetListMonitoring(http_request);
	void GetListImageResource(http_request);

	void GetListAction(http_request);
	void GetListHistory(http_request);

	//std::wstring  String2WString(std::string p_string)
	//{
	//	//cout << p_string << " (char *)" << endl;

	//	// newsize describes the length of the 
	//	// wchar_t string called wcstring in terms of the number 
	//	// of wide characters, not the number of bytes.
	//	size_t newsize = p_string.length() + 1;

	//	// The following creates a buffer large enough to contain 
	//	// the exact number of characters in the original string
	//	// in the new format. If you want to add more characters
	//	// to the end of the string, increase the value of newsize
	//	// to increase the size of the buffer.
	//	wchar_t * wcstring = new wchar_t[newsize];

	//	// Convert char* string to a wchar_t* string.
	//	size_t convertedChars = 0;
	//	mbstowcs_s(&convertedChars, wcstring, newsize, p_string.c_str(), _TRUNCATE);
	//	// Display the result and indicate the type of string that it is.

	//	std::wstring result_wstring(wcstring);

	//	//wcout << result_wstring << _T(" (wchar_t *)") << endl;

	//	return result_wstring;
	//}


	//std::string  WString2String(std::wstring p_wstring)
	//{
	//	//std::wcout << p_wstring << " (char *)" << endl;

	//	const size_t newsize = (p_wstring.length() + 1) * 2;
	//	char *result_string = new char[newsize];
	//	size_t convertedChars = 0;
	//	wcstombs_s(&convertedChars, result_string, newsize, p_wstring.c_str(), _TRUNCATE);

	//	//cout << std::string(result_string) << endl;

	//	return std::string(result_string);
	//}

};

