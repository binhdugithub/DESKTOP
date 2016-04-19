/*
r * Recorder.cpp
 *
 *  Created on: Dec 2, 2015
 *      Author: root
 */

#include "Recorder.h"
#include "commondef.h"

#define AV_INPUT_BUFFER_PADDING_SIZE 32

Recorder::Recorder()
{
	// TODO Auto-generated constructor stub
	m_HMainThread	= 0;
	m_IsRunningFlag = false;
	m_Status  		= STOPRECORD;
	m_Camera 		= NULL;
	m_AVInput 		= NULL;
	m_AVOutput 		= NULL;
	m_InputStream  	= NULL;
	m_OutputStream 	= NULL;
}

Recorder::Recorder(std::string p_id, std::string p_ip, std::string p_url, int p_leng, int p_mode, int p_status)
{
	m_Camera = new Camera(p_id, p_ip, p_url,p_leng, p_mode);
	if(m_Camera)
	{
		std::cout << "Create cam OK: " << std::endl;
		std::cout << "      ID:" << m_Camera->m_Id << std::endl;
		std::cout << "      IP:" << m_Camera->m_Ip << std::endl;
		std::cout << "      URL:" << m_Camera->m_Url << std::endl;
		std::cout << "      Leng:" << m_Camera->m_Length << std::endl;
		std::cout << "      Mode:" << m_Camera->m_Mode << std::endl;
	}

	m_Status = p_status;
	m_IsRunningFlag = false;
	m_HMainThread	= 0;
	m_AVInput 		= NULL;
	m_AVOutput 		= NULL;
	m_InputStream  	= NULL;
	m_OutputStream 	= NULL;
}

Recorder::~Recorder()
{
	// TODO Auto-generated destructor stub
	std::cout << "Discontructor of cam: " << m_Camera->m_Id << std::endl;
	LOG_INFO("Discontructor of cam: " << m_Camera->m_Id);

	if(m_HMainThread && m_IsRunningFlag == true)
	{
		std::cout << "Cam " << m_Camera->m_Id << " in thread recording" << std::endl;
		LOG_INFO("Cam " << m_Camera->m_Id << " in thread recording");

		m_IsRunningFlag = false;
		m_HMainThread->join();

		delete m_HMainThread;
		m_HMainThread = 0;
	}
	else
	{
		std::cout << "Cam " << m_Camera->m_Id << " not in thread recording" << std::endl;
		LOG_INFO("Cam " << m_Camera->m_Id << " not in thread recording");
		std::cout <<"thread:" << m_HMainThread << " flag:" << m_IsRunningFlag << std::endl;

		if (m_HMainThread)
		{
			delete m_HMainThread;
			m_HMainThread = 0;
		}
	}

	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = NULL;
	}

	if(m_AVInput)
	{
		CloseCamera();
	}
	else
	{
		std::cout << "m_AVInput is null" << std::endl;
		LOG_INFO("m_AVInput is null");
	}

	std::cout <<" set Input Stream is null" << std::endl;
	m_InputStream = NULL;
	m_OutputStream = NULL;

}

bool Recorder::InitInput()
{
	int l_camMode = m_Camera->m_Mode;
	if(l_camMode == 1)
	{
		LOG_ERROR("Cam " << m_Camera->m_Id.c_str() << " is recording");
		return false;
	}
	else
	{
		if(m_AVInput)
		{
			avformat_close_input(&m_AVInput);
		}

		std::string l_fileName = m_Camera->m_Url;
		//int ret = avformat_open_input(&input, "http://root:admin@172.30.1.2/axis-cgi/mjpg/video.cgi?date=1&clock=1", NULL, NULL);
		//int ret = avformat_open_input(&input, "http://root:admin@172.30.1.2/axis-cgi/h264/video.cgi", NULL, NULL);
		//int ret = avformat_open_input(&input, "rtsp://root:admin@172.30.1.2/axis-media/media.amp", NULL, NULL);

		AVDictionary *options = NULL;
		av_dict_set(&options, "stimeout", "5000000", 0); // 5 seconds in microseconds
		int ret = avformat_open_input(&m_AVInput, l_fileName.c_str(), NULL, &options);
		av_dict_free(&options);

		if (ret < 0)
		{
			LOG_ERROR("Cam " << m_Camera->m_Id.c_str() << " avformat_open_input fail");
			return false;
		}

		ret = avformat_find_stream_info(m_AVInput, NULL);
		if(ret < 0)
		{
			avformat_close_input(&m_AVInput);

			LOG_ERROR("Cam " << m_Camera->m_Id.c_str() << " avformat_find_stream_info fail");
			return false;
		}


		for(int i = 0; i < m_AVInput->nb_streams; i++)
		{
			if(m_AVInput->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
			{
				m_InputStream = m_AVInput->streams[i];
				break;
			}
		}

	}

	if (m_InputStream)
		return true;
	else
		return false;
}

void Recorder::StartRecord()
{
	bool l_true_false = InitInput();

	if(!l_true_false)
	{
		return;
	}

	m_Status = RECORDING;
	m_IsRunningFlag = true;

	std::cout << "Create thread to recor for cam: " << m_Camera->m_Id << std::endl;
	m_HMainThread = new std::thread(MainThread, this);
}

bool Recorder::InitOutput(std::string p_file, AVStream *p_videoStream)
{
	//
	//Create file
	//
	if(m_AVOutput)
	{
		avformat_free_context(m_AVOutput);
		return false;
	}

	int ret = avformat_alloc_output_context2(&m_AVOutput, NULL, NULL, p_file.c_str());
	//ret = avformat_alloc_output_context2(&output, NULL, NULL, "dump.mjpeg");

	if (ret < 0)
	{
		avformat_close_input(&m_AVInput);
		return false;
	}


	AVCodec* codec = avcodec_find_encoder(p_videoStream->codec->codec_id);
	if (!codec)
	{
		avformat_free_context(m_AVOutput);
		avformat_close_input(&m_AVInput);
		return false;
	}

	m_OutputStream = avformat_new_stream(m_AVOutput, codec);
	if (!m_OutputStream)
	{
		avformat_free_context(m_AVOutput);
		avformat_close_input(&m_AVInput);
		return false;
	}

	m_OutputStream->codec->width = p_videoStream->codec->width;
	m_OutputStream->codec->height = p_videoStream->codec->height;
	m_OutputStream->codec->coded_width = p_videoStream->codec->coded_width;
	m_OutputStream->codec->coded_height = p_videoStream->codec->coded_height;
	m_OutputStream->codec->max_b_frames = p_videoStream->codec->max_b_frames;
	//m_Stream->codec->bit_rate = 640000;
	m_OutputStream->codec->framerate = p_videoStream->codec->framerate;
	m_OutputStream->codec->pix_fmt = p_videoStream->codec->pix_fmt;

	if (!m_OutputStream->codec->extradata_size && p_videoStream->codec->extradata_size)
	{
		m_OutputStream->codec->extradata = (uint8_t*)av_mallocz(p_videoStream->codec->extradata_size + AV_INPUT_BUFFER_PADDING_SIZE);
		if (m_OutputStream->codec->extradata)
		{
			memcpy(m_OutputStream->codec->extradata, p_videoStream->codec->extradata, p_videoStream->codec->extradata_size);
			m_OutputStream->codec->extradata_size = p_videoStream->codec->extradata_size;
		}
	}

	m_OutputStream->codec->time_base = p_videoStream->codec->time_base;//av_inv_q(framerate);
	m_OutputStream->time_base = p_videoStream->time_base;
	//m_Stream->codec->time_base = m_Stream->time_base = av_inv_q(framerate);

	if((m_AVOutput->oformat->flags & AVFMT_GLOBALHEADER) || (p_videoStream->codec->codec_id == AV_CODEC_ID_H264))
		m_OutputStream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;


	ret = avio_open(&m_AVOutput->pb, m_AVOutput->filename, AVIO_FLAG_WRITE);
	if (ret < 0)
	{
		avformat_free_context(m_AVOutput);
		avformat_close_input(&m_AVInput);
		return false;
	}

	ret = avformat_write_header(m_AVOutput, NULL);
	if (ret < 0)
	{
		avformat_free_context(m_AVOutput);
		avformat_close_input(&m_AVInput);
		return false;
	}


	return true;
}

void Recorder::CloseFile()
{
	//close file
	if(m_AVOutput)
	{
		av_write_trailer(m_AVOutput);
		avio_close(m_AVOutput->pb);
		avformat_free_context(m_AVOutput);
		m_AVOutput = NULL;
	}
}

void Recorder::CloseCamera()
{
	std::cout << "Close Camera: " << m_Camera->m_Id << std::endl;
	LOG_INFO("Close Camera: " << m_Camera->m_Id);

	CloseFile();
	//end close file
	if(m_AVInput)
	{
		avformat_close_input(&m_AVInput);
		m_AVInput = NULL;
	}
}



void Recorder::CreatFolderFile()
{
	std::string filePath = Configuration::GetSingleton()->getFilePath();

	struct timespec tv;
	clock_gettime( CLOCK_REALTIME, &tv);
	struct tm tm = *localtime(&tv.tv_sec);

	//Create file directory
	std::ostringstream szDateDir, szIpDir;
	struct stat sb;
	// modify URL
	while(m_Camera->m_Id.find("/")!=-1)
	{
		m_Camera->m_Id.replace(m_Camera->m_Id.find("/"), 1, "_");
	}

	std::string mon, day, h, m, s;

    if((tm.tm_mon + 1)<10)
    	mon = "0" + std::to_string(tm.tm_mon + 1);
    else
    	mon = std::to_string(tm.tm_mon + 1);
    if(tm.tm_mday<10)
    	day = "0" + std::to_string(tm.tm_mday);
    else
    	day = std::to_string(tm.tm_mday);
    if(tm.tm_hour<10)
        h = "0" + std::to_string(tm.tm_hour);
    else
        h = std::to_string(tm.tm_hour);
    if(tm.tm_min<10)
        m = "0" + std::to_string(tm.tm_min);
    else
        m = std::to_string(tm.tm_min);
    if(tm.tm_sec<10)
        s = "0" + std::to_string(tm.tm_sec);
    else
        s = std::to_string(tm.tm_sec);

	szDateDir <<filePath<<"/"<<m_Camera->m_Id<<"/"<<tm.tm_year + 1900<<"/"<< mon<<"/"<< day<<"/"<<h;
	//std::cout<<"szDateDir "<<szDateDir.str()<<std::endl;
	if (stat(szDateDir.str().c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		///std::cout << "CIncoming::createIncoming " << szDateDir << " exist \n"<<std::endl;
	}
	else
	{
		std::ostringstream szCommand;
		szCommand << "mkdir -p " << szDateDir.str().c_str();
		system(szCommand.str().c_str());
	}



	std::ostringstream l_FileName("");
	std::ostringstream l_FilePath("");
	std::ostringstream l_StartTime("");

	m_TimeStart = tm;
	l_StartTime<<tm.tm_year + 1900 << "-" << mon << "-" << day<<" "<<h<<":"<<m<<":"<<s;
	l_FileName<<m_Camera->m_Id<<"-"<<tm.tm_year + 1900<< mon <<day<<"-"<<h<<m<<s<<".mp4";
	//std::cout<<"mFileName = "<<l_FileName.str().c_str()<<std::endl;
	l_FilePath<<szDateDir.str().c_str()<<"/"<<l_FileName.str();
	//std::cout<<"mFilePath"<<mFilePath.str().c_str()<<std::endl;

	m_StartTimeRecording = l_StartTime.str();
	m_RecordPath = l_FilePath.str();
	m_RecordFile = l_FileName.str();

}


void Recorder::GetFileInfo()
{
	m_LengTimeFile = GetDeltaTime(m_TimeStart);
	m_SizeFile =  GetSizeOfRecoredFile(m_RecordPath);
}
void Recorder::MainThread(void *p_param)
{

	Recorder *MyClass = (Recorder*)p_param;

	MyClass->CreatFolderFile();
	if(!MyClass->InitOutput(MyClass->m_RecordPath, MyClass->m_InputStream))
	{
		return;
	}

	MyClass->m_Camera->m_Mode = 1;
	MyClass->m_Status = RECORDING;
	std::string l_query3 = "UPDATE its_cam SET recordmode = 1 WHERE id = '" + MyClass->m_Camera->m_Id + "' ;";
	insertFirstDBQueue(l_query3);

	int64_t l_dts = MyClass->m_InputStream->avg_frame_rate.num ? - MyClass->m_InputStream->codec->has_b_frames * AV_TIME_BASE / av_q2d(MyClass->m_InputStream->avg_frame_rate) : 0;

	int64_t ost_tb_start_time = av_rescale_q(0, AV_TIME_BASE_Q, MyClass->m_OutputStream->time_base);
	int64_t l_SplitDTS = av_rescale_q(MyClass->m_Camera->m_Length * AV_TIME_BASE,AV_TIME_BASE_Q,MyClass->m_InputStream->time_base);

	AVPacket l_pkg, l_opkg;
	AVPacket* l_ppkg = NULL;
	av_init_packet(&l_opkg);

	int l_Ret = -1;
	bool l_BeginRecording = false;
	int64_t l_TempDTS = -1;
	while(MyClass->m_IsRunningFlag)
	{
		l_Ret = av_read_frame(MyClass->m_AVInput, &l_pkg);

		if (l_Ret != 0 && l_Ret == AVERROR(EAGAIN))//read again (cam don't return packet)
		{
			av_usleep(10000);
			std::cout << "Read again" << std::endl;
			LOG_INFO("Read again frame");
			continue;
		}
		else if(l_Ret != 0) // network is error
		{
			MyClass->m_Status = RETRYRECORD;
			break;
		}
		else
		{
			l_ppkg = &l_pkg;
			if(l_pkg.stream_index == MyClass->m_InputStream->id)
			{
				if((l_BeginRecording == false) && (l_pkg.flags & AV_PKT_FLAG_KEY))
				{
					l_BeginRecording = true;
					std::string l_query1 = "INSERT INTO its_nvr_videostorage (id, filename, starttime) VALUE ('" + MyClass->m_Camera->m_Id
											+ "' ,'" + MyClass->m_RecordFile + "', '"+ MyClass->m_StartTimeRecording + "' );";

					pushDBQueue(l_query1);

				} //check for sure start recording

				if(l_BeginRecording)
				{
					if (l_TempDTS < 0)
					{
						l_dts = MyClass->m_InputStream->avg_frame_rate.num ? - MyClass->m_InputStream->codec->has_b_frames * AV_TIME_BASE / av_q2d(MyClass->m_InputStream->avg_frame_rate) : 0;
						if (l_ppkg && l_ppkg->pts != AV_NOPTS_VALUE)
						{
							l_dts += av_rescale_q(l_ppkg->pts, MyClass->m_InputStream->time_base, AV_TIME_BASE_Q);
						}
					} // end if check reset dts

					if (l_ppkg->pts != AV_NOPTS_VALUE)
						l_opkg.pts = av_rescale_q(l_ppkg->pts, MyClass->m_InputStream->time_base, MyClass->m_OutputStream->time_base) - ost_tb_start_time;
					else
						l_opkg.pts = av_rescale_q(l_dts, AV_TIME_BASE_Q, MyClass->m_OutputStream->time_base);

					if (l_ppkg->dts == AV_NOPTS_VALUE)
						l_opkg.dts = av_rescale_q(l_dts, AV_TIME_BASE_Q, MyClass->m_OutputStream->time_base);
					else
						l_opkg.dts = av_rescale_q(l_ppkg->dts, MyClass->m_InputStream->time_base,MyClass->m_OutputStream->time_base);

					l_opkg.dts -= ost_tb_start_time;

					//save the dts of first frame
					if(l_TempDTS < 0)
						l_TempDTS = l_opkg.dts;

					if((l_opkg.dts - l_TempDTS >= l_SplitDTS)
						&& (l_pkg.flags & AV_PKT_FLAG_KEY))
					{
						//std::cout << "Cut file: " << MyClass->m_Camera->m_Id << std::endl;
						MyClass->CloseFile();

						MyClass->GetFileInfo();
						std::string l_query = "UPDATE its_nvr_videostorage SET duration ='" + MyClass->m_LengTimeFile + "', filesize = " + MyClass->m_SizeFile + " WHERE filename = '" + MyClass->m_RecordFile + "';";
						insertFirstDBQueue(l_query);

						MyClass->CreatFolderFile();

						if(!MyClass->InitOutput(MyClass->m_RecordPath, MyClass->m_InputStream))
						{
							MyClass->m_Status = RETRYRECORD;
							break;
						}

						l_query = "INSERT INTO its_nvr_videostorage (id, filename, starttime) VALUE ('" + MyClass->m_Camera->m_Id
															+ "' ,'" + MyClass->m_RecordFile + "', '"+ MyClass->m_StartTimeRecording + "' );";
						pushDBQueue(l_query);

						ost_tb_start_time = av_rescale_q(l_ppkg->dts, MyClass->m_InputStream->time_base, MyClass->m_OutputStream->time_base);
						l_dts = MyClass->m_InputStream->avg_frame_rate.num ? - MyClass->m_InputStream->codec->has_b_frames * AV_TIME_BASE / av_q2d(MyClass->m_InputStream->avg_frame_rate) : 0;
						if (l_ppkg && l_ppkg->pts != AV_NOPTS_VALUE)
						{
							l_dts += av_rescale_q(l_ppkg->pts, MyClass->m_InputStream->time_base, AV_TIME_BASE_Q);
						}

						if (l_ppkg->pts != AV_NOPTS_VALUE)
							l_opkg.pts = av_rescale_q(l_ppkg->pts, MyClass->m_InputStream->time_base, MyClass->m_OutputStream->time_base) - ost_tb_start_time;
						else
							l_opkg.pts = av_rescale_q(l_dts, AV_TIME_BASE_Q, MyClass->m_OutputStream->time_base);

						if (l_ppkg->dts == AV_NOPTS_VALUE)
							l_opkg.dts = av_rescale_q(l_dts, AV_TIME_BASE_Q, MyClass->m_OutputStream->time_base);
						else
							l_opkg.dts = av_rescale_q(l_ppkg->dts, MyClass->m_InputStream->time_base,MyClass->m_OutputStream->time_base);

						l_opkg.dts -= ost_tb_start_time;
						//l_BeginRecording = true;
						l_TempDTS = l_opkg.dts;
					} // end if over time record

					l_opkg.duration = av_rescale_q(l_ppkg->duration, MyClass->m_InputStream->time_base, MyClass->m_OutputStream->time_base);
					l_opkg.flags    = l_ppkg->flags;

					// FIXME remove the following 2 lines they shall be replaced by the bitstream filters
					l_opkg.data = l_ppkg->data;
					l_opkg.size = l_ppkg->size;
					av_copy_packet_side_data(&l_opkg, l_ppkg);

					l_Ret = av_interleaved_write_frame(MyClass->m_AVOutput, &l_opkg);

					if(l_Ret <0)
					{
						std::cout << "write frame error" << std::endl;
						LOG_ERROR("Write frame error:" << l_Ret);
					}
				} // end if allow record
			} // end if id = stream record

			if(l_ppkg)
			{
				av_packet_unref(l_ppkg);
				l_ppkg = NULL;
			}
		} // end got frame
	} // end while

	//close camera
	MyClass->CloseCamera();

	//if soap request stop record
//	if(MyClass->m_Status == STOPRECORD)
//	{
//		std::cout << "++++++Stop cam " << MyClass->m_Camera->m_Id << std::endl;
//		LOG_INFO("++++++Stop cam " << MyClass->m_Camera->m_Id);
//
//		MyClass->m_IsRunningFlag = false;
//		MyClass->m_Camera->m_Mode = 0;
//		std::string l_query = "UPDATE its_cam SET recordmode = 0 WHERE id = '" + MyClass->m_Camera->m_Id + "' ;";
//		insertFirstDBQueue(l_query);
//	}
//	//if network error
//	else
	if(MyClass->m_Status == RETRYRECORD)
	{
		std::cout << "+++++Error read cam " << MyClass->m_Camera->m_Id << std::endl;
		LOG_INFO("+++++Error read cam " << MyClass->m_Camera->m_Id);

		MyClass->m_IsRunningFlag = false;
		MyClass->m_Camera->m_Mode = 2;
		std::string l_query = "UPDATE its_cam SET recordmode = 2 WHERE id = '" + MyClass->m_Camera->m_Id + "' ;";
		insertFirstDBQueue(l_query);
	}


	MyClass->GetFileInfo();
	std::string l_query = "UPDATE its_nvr_videostorage SET duration ='" + MyClass->m_LengTimeFile + "', filesize = " + MyClass->m_SizeFile + " WHERE filename = '" + MyClass->m_RecordFile + "';";
	insertFirstDBQueue(l_query);
}
