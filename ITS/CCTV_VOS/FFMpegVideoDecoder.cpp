
#include <fstream>
#include <stdio.h>
#include <stdarg.h>

using namespace std;

#include "FFMpegVideoDecoder.h"

#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h> // added by longnv
#ifdef __cplusplus
}
#endif /*__cplusplus*/
class AVInitializer {
public:
    AVInitializer() {
        av_register_all();
		//av_log_set_level(AV_LOG_DEBUG);
		//av_log_set_callback(cbAvLog);
	}
    ~AVInitializer() {
    }

	static void cbAvLog(void *ptr, int level, const char *fmt, va_list vargs);
	static ofstream logAv;
};

ofstream AVInitializer::logAv;

void AVInitializer::cbAvLog(void *ptr, int level, const char *fmt, va_list vargs)
{
	logAv.open ("d:\\cctv-ffmpeg-log.txt", ios_base::app);
	static char message[8192];   
   const char *module = NULL;

   // Comment back in to filter only "important" messages
   /*if (level > AV_LOG_WARNING)
      return;*/

   // Get module name
    if (ptr)
    {
        AVClass *avc = *(AVClass**) ptr;
        module = avc->item_name(ptr);
    }

   // Create the actual message
   // replace vsnprintf_s by vsnprintf
   // vsnprintf_s(message, sizeof(message), fmt, vargs);
   vsnprintf(message, sizeof(message), fmt, vargs);

   // Append the message to the logfile
   if (module)
   {
      logAv << module << " ********************" << endl;
   }
   logAv << "lvl: " << level << endl << "msg: " << message << endl;
   	logAv.close();
}

static AVInitializer sAVInit;

FFMpegVideoDecoder::FFMpegVideoDecoder(void)
{
	memset(&mOptions, 0, sizeof(mOptions));
	m_szTmpOutBuffer = 0;
	mConvertCtx = NULL;
	mRgb = NULL;
}


FFMpegVideoDecoder::~FFMpegVideoDecoder(void)
{
	try
	{
		if (mCodecCtx){
			avcodec_close(mCodecCtx);		
			av_free(mCodecCtx);
			mCodecCtx = NULL;
		}

		if (mFrame)
		{
			av_free(mFrame);
			mFrame = NULL;
		}

		if (m_szTmpOutBuffer) {
			delete [] m_szTmpOutBuffer;
			m_szTmpOutBuffer = 0;
		}
		if(mRgb)
			delete mRgb;
		//if(mConvertCtx)

	}
	catch(...)
	{
	}
}

int FFMpegVideoDecoder::Init(DecoderOptions* params)
{
	mOptions.callback_func = params->callback_func;
	mOptions.codec_type = params->codec_type;
	mOptions.user_data = params->user_data;
	mOptions.width = params->width;
	mOptions.height = params->height;

	mCodec = avcodec_find_decoder((AVCodecID)params->codec_type);
	if(!mCodec)
		goto failed;

	mCodecCtx = avcodec_alloc_context3(mCodec);
	if(!mCodecCtx)
		goto failed;

	//mCodecCtx->width = mOptions.width;
	//mCodecCtx->height = mOptions.height;


	mFrame= av_frame_alloc();
	if (!mFrame)
		goto failed;

    if(mCodec->capabilities&CODEC_CAP_TRUNCATED)
        mCodecCtx->flags|= CODEC_FLAG_TRUNCATED; 

	//if(avcodec_open(mCodecCtx,mCodec)<0) // change to avcodec_open2() in new ffmpeg version
    if(avcodec_open2(mCodecCtx,mCodec, NULL) < 0)
	{
		av_free(mFrame);
		av_free(mCodecCtx);
		mCodecCtx = NULL;
		mCodec = NULL;
		goto failed;
	}
	
	// [sonlt@videgw 03/03/2010] new decode
	//if (strcmp(m_pDecoderParam->config, "") != 0){
	//	if ((CodecID)m_pDecoderParam->nCodecID == CODEC_ID_MPEG4 
	//		|| (CodecID)m_pDecoderParam->nCodecID == CODEC_ID_AAC)
	//		MPEG4Config2Data(m_pDecoderParam->config, &ctx->extradata, &ctx->extradata_size);
	//	if ((CodecID)m_pDecoderParam->nCodecID == CODEC_ID_H264)
	//		H264Config2Data(m_pDecoderParam->config, &ctx->extradata, &ctx->extradata_size);
	//		//H264Config(m_pDecoderParam->config, ctx, picture);
	//}

	return 1;
failed:
	return -1;
}

int FFMpegVideoDecoder::Decode(const unsigned char* data, unsigned int length, unsigned long timestamp)
{
	//return 0;
	if (length <= 0)
		return 0;

	if ((!mCodec)||(!mCodecCtx)||(!mFrame))
	{
		return -1;
	}
	
	AVPacket packet;
	av_init_packet(&packet);
	packet.data = (uint8_t*)data;
	packet.size = length;
	int got_pic;
	int len;
	int inbuf_size = length;
	int undecoded_size;

	while (packet.size > 0)
	{
		len = avcodec_decode_video2(mCodecCtx, mFrame, &got_pic, &packet);
		if (len < 0)
			return -1;
		undecoded_size = length - len;
		if (got_pic)
		{
			mOptions.width = mCodecCtx->width;
			mOptions.height = mCodecCtx->height;
			RenderFrame(mFrame, elc::GetTickCount()*90);
		}

		inbuf_size -= len;
		data += len;

		packet.size -= len;
        packet.data += len;
	}
	return 1;
}

int FFMpegVideoDecoder::width()
{
	return mOptions.width;
}

int FFMpegVideoDecoder::height()
{
	return mOptions.height;
}

int FFMpegVideoDecoder::codec()
{
//{	if (pict->linesize[0] == m_nFrameWidth*4)
//	mOptions.callback_func(pict->data[0], size*4, myTS, mOptions.user_data, 0, 0);
//else
//{
//	if (!m_szTmpOutBuffer) {
//		m_szTmpOutBuffer = new unsigned char[size*4];
//	}
//
//	for (int i = 0; i < m_nFrameHeight; i++) {
//		memcpy(m_szTmpOutBuffer + i*m_nFrameWidth*4, pict->data[0] + i*pict->linesize[0], m_nFrameWidth*4);
//	}
//
//	mOptions.callback_func(m_szTmpOutBuffer, size*4, myTS, mOptions.user_data, 0, 0);
//}
	return mOptions.codec_type;
}

bool FFMpegVideoDecoder::RenderFrame(const AVFrame *pict,unsigned long timestamp)
{
	int m_nFrameWidth = mOptions.width;
	int m_nFrameHeight = mOptions.height;
	unsigned long myTS =  elc::GetTickCount()*90; //pict->pkt_pts;
	int size = m_nFrameWidth * m_nFrameHeight;

//=============================Case using RGB24========================================
	//Edited by Longnv --  convert to rgb
	if ( mOptions.callback_func )
	{
		if(!mConvertCtx)
		{
			mConvertCtx = sws_getContext(mOptions.width, mOptions.height,
					AV_PIX_FMT_YUV420P, mOptions.width, mOptions.height,
					AV_PIX_FMT_RGB24, 0, 0, 0, 0);
		}
		if(!mRgb)
		{
			mRgb = new AVPicture();
			mRgb->linesize[0] = mOptions.width * 3;
			mRgb->data[0]     = (uint8_t*)malloc( mRgb->linesize[0] * mOptions.height);
		}

		sws_scale((SwsContext*)mConvertCtx, pict->data, pict->linesize, 0, mOptions.height, mRgb->data, mRgb->linesize);
		//mOptions.callback_func(m_szTmpOutBuffer, size*3/2, myTS, mOptions.user_data, 0, 0);
		mOptions.callback_func(mRgb->data[0], size*3, myTS, mOptions.user_data, 0, 0);
		return 1;
	}

return 0;


// ============================== Case using YUV420P======================================
//	if (av_frame_get_colorspace(pict) == AV_PIX_FMT_RGBA) {
//		cout << "Get pic with color space = RGBA" << endl;
//		if (pict->linesize[0] == m_nFrameWidth*4)
//			mOptions.callback_func(pict->data[0], size*4, myTS, mOptions.user_data, 0, 0);
//		else
//		{
//			if (!m_szTmpOutBuffer) {
//				m_szTmpOutBuffer = new unsigned char[size*4];
//			}
//
//			for (int i = 0; i < m_nFrameHeight; i++) {
//				memcpy(m_szTmpOutBuffer + i*m_nFrameWidth*4, pict->data[0] + i*pict->linesize[0], m_nFrameWidth*4);
//			}
//
//			mOptions.callback_func(m_szTmpOutBuffer, size*4, myTS, mOptions.user_data, 0, 0);
//		}
//	} else { // call swscale
//
//	}
//	return 1;
//
//	if (pict->data[1] == pict->data[0] + size
//		&& pict->data[2] == pict->data[1] + (size >> 2)){
//			if ( mOptions.callback_func ){
//				mOptions.callback_func(pict->data[0],
//									(mOptions.width*mOptions.height*3)/2,
//									myTS, mOptions.user_data, 0, 0);
//				return 1;
//			}
//	}
//
//	if (!m_szTmpOutBuffer) {
//		m_szTmpOutBuffer = new unsigned char[size*3/2];
//	}
//	unsigned char *dst = m_szTmpOutBuffer;
//	unsigned char *src;
//	for (int i=0; i<3; i ++)
//	{
//		src = pict->data[i];
//
//		int dst_stride = i ? m_nFrameWidth >> 1 : m_nFrameWidth;
//		int src_stride = pict->linesize[i];
//		int h = i ? m_nFrameHeight >> 1 : m_nFrameHeight;
//
//		if (src_stride==dst_stride)
//		{
//			memcpy(dst, src, dst_stride*h);
//			dst += dst_stride*h;
//		}
//		else
//		{
//			while (h--)
//			{
//				try{
//					memcpy(dst, src, dst_stride);
//					dst += dst_stride;
//					src += src_stride;
//				}
//				catch(...){
//					return 0;
//				}
//			}
//		}
//	}
//
//	if ( mOptions.callback_func )
//	{
//		if(!mConvertCtx)
//		{
//			mConvertCtx = sws_getContext(mOptions.width, mOptions.height,
//					AV_PIX_FMT_YUV420P, mOptions.width, mOptions.height,
//					AV_PIX_FMT_RGB24, 0, 0, 0, 0);
//		}
//		AVPicture mRgb;
//		mRgb.linesize[0] = mOptions.width * 3;
//		mRgb.data[0]     = (uint8_t*)malloc( mRgb.linesize[0] * mOptions.height);
//		unsigned char* const* yuvData = (unsigned char* const*)m_szTmpOutBuffer;
//		int mSize = mOptions.width;
//		sws_scale((SwsContext*)mConvertCtx, yuvData, &mSize, 0, mOptions.height, mRgb.data, mRgb.linesize);
//
//		//mOptions.callback_func(m_szTmpOutBuffer, size*3/2, myTS, mOptions.user_data, 0, 0);
//		mOptions.callback_func(m_szTmpOutBuffer, size*3, myTS, mOptions.user_data, 0, 0);
//		return 1;
//	}
//
//	return 0;

	// FOR TEST ENCODER

//	int m_nFrameWidth = mOptions.width;
//	int m_nFrameHeight = mOptions.height;
//	unsigned long myTS =  elc::GetTickCount()*90; //pict->pkt_pts;
//	int size = m_nFrameWidth * m_nFrameHeight;
//
//	if (pict->data[1] == pict->data[0] + size
//		&& pict->data[2] == pict->data[1] + (size >> 2)){
//			if ( mOptions.callback_func ){
//				mOptions.callback_func(pict->data[0],
//									(mOptions.width*mOptions.height*3)/2,
//									myTS, mOptions.user_data, 0, 0);
//				return 1;
//			}
//	}
//
//	if (!m_szTmpOutBuffer) {
//		m_szTmpOutBuffer = new unsigned char[size*3/2];
//	}
//	unsigned char *dst = m_szTmpOutBuffer;
//	unsigned char *src;
//	for (int i=0; i<3; i ++)
//	{
//		src = pict->data[i];
//
//		int dst_stride = i ? m_nFrameWidth >> 1 : m_nFrameWidth;
//		int src_stride = pict->linesize[i];
//		int h = i ? m_nFrameHeight >> 1 : m_nFrameHeight;
//
//		if (src_stride==dst_stride)
//		{
//			memcpy(dst, src, dst_stride*h);
//			dst += dst_stride*h;
//		}
//		else
//		{
//			while (h--)
//			{
//				try{
//					memcpy(dst, src, dst_stride);
//					dst += dst_stride;
//					src += src_stride;
//				}
//				catch(...){
//					return 0;
//				}
//			}
//		}
//	}
//
//	if ( mOptions.callback_func ){
//		mOptions.callback_func(m_szTmpOutBuffer, size*3/2, myTS, mOptions.user_data, 0, 0);
//		return 1;
//	}
//
//	return 0;

}
