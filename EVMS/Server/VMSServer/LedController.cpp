#include "stdafx.h"
#include "LedController.h"
#include "Configuration.h"
#include "LogFile.h"
#include <ostream>
#include <boost\algorithm\string.hpp>



LedController::LedController(void)
{
	m_DBINF = new DatabaseInterface();
	m_LEDCTRL = new VMSLedCtrl();
}


LedController::~LedController(void)
{
	if(m_DBINF)
	{
		delete m_DBINF;
		m_DBINF = NULL;
	}

	if(m_LEDCTRL)
	{
		delete m_LEDCTRL;
		m_LEDCTRL;
	}
}

bool LedController::UpdateImage(int p_id)
{
	std::vector<std::string> l_object = m_DBINF->GetObjectDetail(p_id);
	if(l_object.size() > 0)
	{
		std::string vmsIP = l_object[2];
		int vmsPort = stoi(l_object[3]);
		double vmsWidth = stod(l_object[13]);
		double vmsHeight = stod(l_object[14]);
		std::string vmsControll = l_object[12];
		std::string nameImage = Configuration::GetSingleTon()->st_screenshot + std::string("/") + std::to_string(p_id) + std::string(".jpg");
		int id = 1;
		int type;// = 4694;//4694;//0x0452;//0x0052;
		int color;
		int screenData;
		int nStunt = 1;
		int nStuntSpeed = 1;
		int nTimeDisplay = 1;

		if(vmsControll.compare("BX_5M1")==0)  
		{
			type = 0x0052;
			color = 2;
			screenData = 0;
		}
		else if(vmsControll.compare("BX_5M4")==0)  
		{
			type = 0x0452;
			color = 2;
			screenData = 1;
		}
		else if(vmsControll.compare("BX_5Q2+")==0)  
		{
			color = 1;
			type = 4694;
			screenData = 0;
		}
		else  
		{
			LOG_ERROR("Don't support type this controll");
			return 2;
		}

		
		int rs = m_LEDCTRL->InitBoard(id, (char*)vmsIP.c_str(), type, vmsWidth, vmsHeight, color, screenData);
		if(rs)  
		{
			LOG_ERROR("Init Board ID="	<< p_id <<" error");
			std::cout << "Init Board ID = " << p_id << " error" << std::endl;
			return 2;
		}

		rs = m_LEDCTRL->SetImageFileToBoard(id, (char*)nameImage.c_str(), nStunt, 
			nStuntSpeed, nTimeDisplay, 0, 0, vmsWidth, vmsHeight);
		if(rs)  
		{
			LOG_ERROR("Set Image to Board ID="<<p_id<<" error");
			std::cout << "Set Image to Board ID=" << p_id << " error" << std::endl;
			return 2;
		}


		return true;
	}
	else
	{
		LOG_ERROR("Get object detail failed");
		std::cout << "Get object detail failed" << std::endl;
	}
	

	return false;
}


int LedController::UpdateProgram(int p_id)
{
	//return true;
	///Test("D:/PROJECTS/eVMS/www/text/13_0.txt");
	//return false;

	std::vector<std::string> l_object = m_DBINF->GetObjectDetail(p_id);
	if(l_object.size() > 0)
	{
		std::string l_vms_ip = l_object[2];
		int l_vms_port = stoi(l_object[3]);
		double l_vms_width = stod(l_object[13]);
		double l_vms_height = stod(l_object[14]);
		std::string l_vms_controll = l_object[12];
		int l_id = 1;
		int l_controller_type;
		int l_screen_type;
		int l_screen_no		 = SCREEN_NO;
		int l_screen_data_da = SCREEN_DATADA;
		int l_screen_data_oe = SCREEN_DATAOE;
		int l_screen_roworder = SCREEN_ROWORDER;
		int l_screen_preqpar =	 SCREEN_FREQPAR;
		int l_screen_baud =		SCREEN_BAUD_57600 ;
		int l_stunt = 1;
		int l_stunt_speed = 1;
		int l_time_display = 1;
		int l_pixel_mode = 1;
		int l_send_mode_net = 2;
		int l_send_cmd_paramater = 0xA1FF;
		int l_send_cmd_sendall_pgrogram  = 0xA1F0;
		int l_showsingle = 1;
		int l_program_ord = 0;
		int l_area_ord = 0;
		
		if(l_vms_controll.compare("BX-5M1")==0)  
		{
			l_controller_type = 0x0052;
			l_screen_type = SCREEN_TYPE_DOUBLE;
			l_screen_data_da = 0;
		}
		else if(l_vms_controll.compare("BX_5M4")==0)  
		{
			l_controller_type = CONTROLLER_BX_5M4;
			l_screen_type =		SCREEN_TYPE_DOUBLE ;
			l_screen_data_da = SCREEN_DATADA; 
			l_pixel_mode = SCREEN_PIXEL_MODE; 
			l_screen_data_oe = 0; 
			l_screen_roworder = 0;
		}
		else if(l_vms_controll.compare("BX_5Q2+")==0)  
		{
			l_controller_type =	CONTROLLER_BX_5Q2P;
			l_screen_type =		SCREEN_TYPE_FULL;
			l_screen_data_da =	SCREEN_DATADA;
			l_screen_no		 =	SCREEN_NO;
			l_screen_data_da =	SCREEN_DATADA;
			l_screen_data_oe =	SCREEN_DATAOE;
			l_screen_roworder =	SCREEN_ROWORDER;
			l_screen_preqpar =	SCREEN_FREQPAR;
			l_screen_baud =		SCREEN_BAUD_57600 ;
		}
		else  
		{
			LOG_ERROR("Don't support type this controll");

			return 2;
		}

		std::string l_program = l_object[7];
		json::value l_json_program = json::value::parse(utility::conversions::to_string_t(l_program));
		if(!l_json_program.is_null())
		{
			json::value l_json_program_image = l_json_program[L"image"];
			json::value l_json_program_text = l_json_program[L"text"];

			m_LEDCTRL->InitDLL();
				
			/*int nResult = m_LEDCTRL->api_AddScreen(l_type, l_screen_no, l_vms_width
				, l_vms_height, l_color, 1,l_screen_data_da, l_screen_data_oe
			, SCREEN_ROWORDER, SCREEN_FREQPAR,SCREEN_COMM
			, SCREEN_BAUD,(char*)l_vms_ip.c_str(), l_vms_port, "ScreenStatus.ini");*/

			int nResult = m_LEDCTRL->api_AddScreen(l_controller_type, l_screen_no, l_vms_width
				, l_vms_height, l_screen_type, l_pixel_mode ,l_screen_data_da, l_screen_data_oe
			, l_screen_roworder, l_screen_preqpar,SCREEN_COMM
			, l_screen_baud,(char*)l_vms_ip.c_str(), l_vms_port, "ScreenStatus.ini");
			
			if(nResult == 248)
			{
				std::cout << "Screen info have already" << std::endl;
				nResult = m_LEDCTRL->api_DeleteScreen(l_screen_no);
				if(nResult !=0)
				{

					m_LEDCTRL->FreeDLL();
					return nResult;
				}
				
				nResult = m_LEDCTRL->api_AddScreen(l_controller_type, l_screen_no, l_vms_width
				, l_vms_height, l_screen_type, l_pixel_mode ,l_screen_data_da, l_screen_data_oe
				, l_screen_roworder, l_screen_preqpar,SCREEN_COMM
				, l_screen_baud,(char*)l_vms_ip.c_str(), l_vms_port, "ScreenStatus.ini");

				if(nResult !=0)
				{

					m_LEDCTRL->FreeDLL();
					return nResult;
				}
			}
			else
			{
				if(nResult !=0)
				{

					m_LEDCTRL->FreeDLL();
					return nResult;
				}

			}

		/*	int nResult = m_LEDCTRL->api_AddScreen(CONTROLLER_TYPE_5M4, SCREEN_NO, SCREEN_WIDTH
			, SCREEN_HEIGHT, SCREEN_TYPE, 1,SCREEN_DATADA, SCREEN_DATAOE
			, SCREEN_ROWORDER, SCREEN_FREQPAR,SCREEN_COMM
			, SCREEN_BAUD,SCREEN_SOCKETIP, SCREEN_SOCKETPORT, "ScreenStatus.ini");
			FAIL_FUNC(nResult);*/

			//if (m_bSendBusy==FALSE)
			{
				//m_bSendBusy=TRUE;
				//nResult = m_LEDCTRL->api_SendScreenInfo(l_screen_no, l_send_mode_net, l_send_cmd_paramater, 0);
				nResult = m_LEDCTRL->api_SendScreenInfo(l_screen_no, SEND_MODE_NET, SEND_CMD_PARAMETER, 0);
				if(nResult !=0)
				{

					m_LEDCTRL->FreeDLL();
					return nResult;
				}
				//m_bSendBusy=FALSE;
			}
	
			//nResult = m_LEDCTRL->api_AddScreenProgram(l_screen_no, 0, 0, 65535, 12, 3, 2015, 11, 26, 1, 1, 1, 1, 1, 1, 1, 8, 0, 18, 0);
			nResult = m_LEDCTRL->api_AddScreenProgram(l_screen_no, 0, 0, 65535, 12, 3, 2011, 11, 26, 1, 1, 1, 1, 1, 1, 1, 8, 0, 18, 0);
			if(nResult !=0)
			{

				m_LEDCTRL->FreeDLL();
				return nResult;
			}

			if(l_json_program_text.size() > 0)
			{
				for(int i = 0; i < l_json_program_text.size(); i++)
				{
					json::value l_json_temp = l_json_program_text[i];
					std::string content = utility::conversions::to_utf8string(l_json_temp.at(L"content").as_string());
					int x = l_json_temp.at(L"x").as_integer();
					int y = l_json_temp.at(L"y").as_integer();
					double width = 0;
					double height = 0;
					if(l_json_temp.has_field(L"width"))
					{
						if(l_json_temp.at(L"width").is_double())
						{
							width =l_json_temp.at(L"width").as_double();
						}
						else if(l_json_temp.at(L"width").is_string())
						{
							std::string test = utility::conversions::to_utf8string(l_json_temp.at(L"width").as_string());
							width = stod(test);
						}
						else if(l_json_temp.at(L"width").is_integer())
						{
							width = l_json_temp.at(L"width").as_integer();
						}
					}

					if(l_json_temp.has_field(L"height"))
					{
						if(l_json_temp.at(L"height").is_double())
						{
							height =l_json_temp.at(L"height").as_double();
						}
						else if(l_json_temp.at(L"height").is_string())
						{
							std::string test = utility::conversions::to_utf8string(l_json_temp.at(L"height").as_string());
							height = stod(test);
						}
						else if(l_json_temp.at(L"height").is_integer())
						{
							height = l_json_temp.at(L"height").as_integer();
						}
					}
					
					std::string fontname = utility::conversions::to_utf8string(l_json_temp.at(L"font").as_string());
					//fontname = std::string("Tahoma");
					int fontsize = INT_MAX;
					if(l_json_temp.has_field(L"fontsize"))
					{
						if(l_json_temp.at(L"fontsize").is_integer())
							fontsize = l_json_temp.at(L"fontsize").as_integer();
						else if(l_json_temp.at(L"fontsize").is_string())
							fontsize = stoi(utility::conversions::to_utf8string(l_json_temp.at(L"fontsize").as_string()));
					}

					

					std::string filename = Configuration::GetSingleTon()->st_text + std::string("/")  + std::to_string(p_id) + std::string("_")  + std::to_string(i) + std::string(".txt");
					FILE *file;
					file = fopen(filename.c_str(), "w");
					if(file)
					{
						fwrite((const void*)content.c_str(), sizeof(char), content.length(), file);
						fclose(file);
					}
							
					int l_bold = 0;
					int l_fontcolor = 1;
					std::string l_str_fontcolor = std::string("");
					if(l_json_temp.has_field(L"colortext"))
					{
						if(l_json_temp.at(L"colortext").is_string())
							l_str_fontcolor = utility::conversions::to_utf8string(l_json_temp.at(L"colortext").as_string());
					}

					//var rgb    : int = 0xFFFFFF & argb;
					//var alpha : int = (argb>>24)&0xFF;

					if(l_str_fontcolor.length() > 0)
					{
						boost::algorithm::to_lower(l_str_fontcolor);
						if(l_str_fontcolor.compare("#ff000000") == 0)
						{
							l_fontcolor = BLACK;
						}else if(l_str_fontcolor.compare("#ffff0000") == 0)
						{
							l_fontcolor = RED;
						}else if(l_str_fontcolor.compare("#ff00ff00") == 0)
						{
							l_fontcolor = GREEN;
						}else if(l_str_fontcolor.compare("#ffffff00") == 0)
						{
							l_fontcolor = YELLOW;
						}else if(l_str_fontcolor.compare("#ff0000ff") == 0)
						{
							l_fontcolor = BLUE;
						}else if(l_str_fontcolor.compare("#ff0f0f00") == 0)
						{
							l_fontcolor = MAUVE;
						}else if(l_str_fontcolor.compare("#ff0ff000") == 0)
						{
							l_fontcolor = LIGHT_GREEN;
						}else if(l_str_fontcolor.compare("#ffffffff") == 0)
						{
							l_fontcolor = WHITE;
						}
					}
					else
					{
						l_fontcolor = RED;
					}

					//l_fontcolor = 1;

					nResult = m_LEDCTRL->api_AddScreenProgramBmpTextArea(l_screen_no , 0, x, y, width, height);
					if(nResult !=0)
					{
						m_LEDCTRL->FreeDLL();
						return nResult;
					}
					//fontname = ".VnTime";
					//fontsize = 8;
					
					nResult = m_LEDCTRL->api_AddScreenProgramAreaBmpTextFile(l_screen_no, l_program_ord, l_area_ord++,(char*)filename.c_str(), l_showsingle, (char*)fontname.c_str(), fontsize, l_bold, l_fontcolor, 2, 60, 0);
					if(nResult !=0)
					{
						m_LEDCTRL->FreeDLL();
						return nResult;
					}

				}

			}


			if(l_json_program_image.size() > 0)
			{
				for(int i = 0; i < l_json_program_image.size(); i++)
				{
					json::value l_json_temp = l_json_program_image[i];
					int x = l_json_temp.at(L"x").as_integer();
					int y = l_json_temp.at(L"y").as_integer();
					double width = 0;
					double height = 0;
					if(l_json_temp.has_field(L"width"))
					{
						if(l_json_temp.at(L"width").is_double())
						{
							width =l_json_temp.at(L"width").as_double();
						}
						else if(l_json_temp.at(L"width").is_string())
						{
							std::string test = utility::conversions::to_utf8string(l_json_temp.at(L"width").as_string());
							width = stod(test);
						}
						else if(l_json_temp.at(L"width").is_integer())
						{
							width = l_json_temp.at(L"width").as_integer();
						}
					}

					if(l_json_temp.has_field(L"height"))
					{
						if(l_json_temp.at(L"height").is_double())
						{
							height =l_json_temp.at(L"height").as_double();
						}
						else if(l_json_temp.at(L"height").is_string())
						{
							std::string test = utility::conversions::to_utf8string(l_json_temp.at(L"height").as_string());
							height = stod(test);
						}
						else if(l_json_temp.at(L"height").is_integer())
						{
							height = l_json_temp.at(L"height").as_integer();
						}
					}

					string l_link = "";
					if(l_json_temp.has_field(L"link"))
					{
						if(l_json_temp.at(L"link").is_string())
						{
							l_link = utility::conversions::to_utf8string(l_json_temp.at(L"link").as_string());
						}
					}


					int l_index = l_link.find_last_of("/");
					std::string l_filename = l_link.substr(l_index + 1);
					std::string l_physical_link = Configuration::GetSingleTon()->st_imageresource + "/" + l_filename;

					nResult = m_LEDCTRL->api_AddScreenProgramBmpTextArea(l_screen_no , 0, x, y, width, height);
					if(nResult !=0)
					{

						m_LEDCTRL->FreeDLL();
						return nResult;
					}
					
					nResult = m_LEDCTRL->api_AddScreenProgramAreaBmpTextFile(l_screen_no, l_program_ord, l_area_ord++,(char*)l_physical_link.c_str(), l_showsingle, "", 8, 0, 1, 2, 60, 0);
					if(nResult !=0)
					{

						m_LEDCTRL->FreeDLL();
						return nResult;
					}

				}
			}


			//nResult = m_LEDCTRL->api_SendScreenInfo(l_screen_no, l_send_mode_net, l_send_cmd_sendall_pgrogram, 0);
			nResult = m_LEDCTRL->api_SendScreenInfo(SCREEN_NO, SEND_MODE_NET, SEND_CMD_SENDALLPROGRAM, 0);
			if(nResult !=0)
			{

				m_LEDCTRL->FreeDLL();
				return nResult;
			}
		}

	}
	else
	{
		return 1;
	}

	m_LEDCTRL->FreeDLL();
	return 0;
};


bool LedController::Test(std::string p_file)
{
	bool m_bSendBusy = FALSE;
	m_LEDCTRL->InitDLL();

	int nResult = m_LEDCTRL->api_AddScreen(CONTROLLER_BX_5M4, SCREEN_NO, SCREEN_WIDTH
		, SCREEN_HEIGHT, SCREEN_TYPE_DOUBLE, 1,SCREEN_DATADA, SCREEN_DATAOE
		, SCREEN_ROWORDER, SCREEN_FREQPAR,SCREEN_COMM
		, SCREEN_BAUD_57600,SCREEN_SOCKETIP, SCREEN_SOCKETPORT, "ScreenStatus.ini");
	FAIL_FUNC(nResult);

	if (m_bSendBusy==FALSE)
	{
		m_bSendBusy=TRUE;
		nResult = m_LEDCTRL->api_SendScreenInfo(SCREEN_NO, SEND_MODE_NET, SEND_CMD_PARAMETER, 0);
		assert(nResult == 0);
		m_bSendBusy=FALSE;
	}
	
	nResult = m_LEDCTRL->api_AddScreenProgram(SCREEN_NO, 0, 0, 65535, 12, 3, 2011, 11, 26, 1, 1, 1, 1, 1, 1, 1, 8, 0, 18, 0);
	assert(nResult == 0);
	
	//dong 1
	nResult = m_LEDCTRL->api_AddScreenProgramBmpTextArea(SCREEN_NO , 0, 0, 0, SCREEN_WIDTH, 20);
	assert(nResult == 0);
	
	//dong 2
	nResult = m_LEDCTRL->api_AddScreenProgramBmpTextArea(SCREEN_NO, 0, 0, 20, SCREEN_WIDTH, 20);
	assert(nResult == 0);

	//dong 3
	nResult = m_LEDCTRL->api_AddScreenProgramBmpTextArea(SCREEN_NO, 0, 0, 40, SCREEN_WIDTH, 20);
	assert(nResult == 0);

	std::string strFileName = "test.txt";
	
	//dong 3: text
	nResult = m_LEDCTRL->api_AddScreenProgramAreaBmpTextFile(SCREEN_NO, 0, 0, (char*)strFileName.c_str(), 1, ".VnTime", 8, 0, 1, 2, 60, 0);
	assert(nResult == 0);

	//dong 3: text
	nResult = m_LEDCTRL->api_AddScreenProgramAreaBmpTextFile(SCREEN_NO, 0, 1, "test.txt", 1, ".VnTime", 8, 0, 1, 2, 60, 0);
	assert(nResult == 0);

	//dong 3: image
	nResult = m_LEDCTRL->api_AddScreenProgramAreaBmpTextFile(SCREEN_NO, 0, 2, "test.bmp", 1, "", 8, 0, 1, 2, 60, 0);
	assert(nResult == 0);


	if (m_bSendBusy==FALSE)
	{
		m_bSendBusy=TRUE;
		int nResult = m_LEDCTRL->api_SendScreenInfo(SCREEN_NO, SEND_MODE_NET, SEND_CMD_SENDALLPROGRAM, 0);
		assert(nResult == 0);
		m_LEDCTRL->api_FreeDLLResource();
		FreeLibrary(m_LEDCTRL->hInst);
		m_bSendBusy=FALSE;
	}

	//m_LEDCTRL->api_FreeDLLResource();
	//FreeLibrary(m_LEDCTRL->hInst);
	m_bSendBusy= FALSE;

	return false;
}