///*
// * mpeg4encoder.cpp
// *
// *  Created on: Jul 21, 2014
// *      Author: xyz
// */
//
//#include "mpeg4encoder.h"
//
//const int vop_presets[] = {
//	/* quality 0 */
//	0,
//
//	/* quality 1 */
//	0,
//
//	/* quality 2 */
//	XVID_VOP_HALFPEL,
//
//	/* quality 3 */
//	XVID_VOP_HALFPEL | XVID_VOP_INTER4V,
//
//	/* quality 4 */
//	XVID_VOP_HALFPEL | XVID_VOP_INTER4V,
//
//	/* quality 5 */
//	XVID_VOP_HALFPEL | XVID_VOP_INTER4V |
//	XVID_VOP_TRELLISQUANT,
//
//	/* quality 6 */
//	XVID_VOP_HALFPEL | XVID_VOP_INTER4V |
//	XVID_VOP_TRELLISQUANT | XVID_VOP_HQACPRED,
//
//};
//
//
//const int motion_presets[] = {
//	/* quality 0 */
//	0,
//
//	/* quality 1 */
//	XVID_ME_ADVANCEDDIAMOND16,
//
//	/* quality 2 */
//	XVID_ME_ADVANCEDDIAMOND16 | XVID_ME_HALFPELREFINE16,
//
//	/* quality 3 */
//	XVID_ME_ADVANCEDDIAMOND16 | XVID_ME_HALFPELREFINE16 |
//	XVID_ME_ADVANCEDDIAMOND8 | XVID_ME_HALFPELREFINE8,
//
//	/* quality 4 */
//	XVID_ME_ADVANCEDDIAMOND16 | XVID_ME_HALFPELREFINE16 |
//	XVID_ME_ADVANCEDDIAMOND8 | XVID_ME_HALFPELREFINE8 |
//	XVID_ME_CHROMA_PVOP | XVID_ME_CHROMA_BVOP,
//
//	/* quality 5 */
//	XVID_ME_ADVANCEDDIAMOND16 | XVID_ME_HALFPELREFINE16 |
//	XVID_ME_ADVANCEDDIAMOND8 | XVID_ME_HALFPELREFINE8 |
//	XVID_ME_CHROMA_PVOP | XVID_ME_CHROMA_BVOP,
//
//	/* quality 6 */
//	XVID_ME_ADVANCEDDIAMOND16 | XVID_ME_HALFPELREFINE16 | XVID_ME_EXTSEARCH16 |
//	XVID_ME_ADVANCEDDIAMOND8 | XVID_ME_HALFPELREFINE8 | XVID_ME_EXTSEARCH8 |
//	XVID_ME_CHROMA_PVOP | XVID_ME_CHROMA_BVOP,
//
//};
//
//#define is_vop_start_code(a) ((a[0] == 0) && (a[1] == 0) && (a[2] == 1) && (a[3] == 182))
//#define get_vop_coding_type(a) (a[4]&0x03)
//
//Mpeg4Encoder::Mpeg4Encoder()
//{
//	m_bFastUpdate = false;
//	m_pOutput = new char[1024*1024];
//}
//
//Mpeg4Encoder::~Mpeg4Encoder()
//{
//
//}
//
//bool Mpeg4Encoder::initVideoEncoder(const VSS_SETTING& param)
//{
//	m_videoparam = param;
//	if(param.nColorSpace == VSS_COLOR_RGB24)
//	{
//		convertContext = sws_getContext(param.nWidth ,param.nHeight , PIX_FMT_RGB24,
//				param.nWidth, param.nHeight,PIX_FMT_YUV420P, SWS_FAST_BILINEAR, NULL, NULL, NULL);
//	}
//	if(param.nColorSpace == VSS_COLOR_RGB32)
//	{
//		convertContext = sws_getContext(param.nWidth ,param.nHeight , PIX_FMT_ARGB,
//				param.nWidth, param.nHeight,PIX_FMT_YUV420P, SWS_FAST_BILINEAR, NULL, NULL, NULL);
//	}
//
//	xvid_plugin_single_t single;
//	xvid_gbl_init_t xvid_gbl_init;
//	xvid_enc_create_t xvid_enc_create;
//
//	memset(&xvid_gbl_init, 0, sizeof(xvid_gbl_init));
//	xvid_gbl_init.version = XVID_VERSION;
//	xvid_gbl_init.debug = 0;
//	xvid_gbl_init.cpu_flags = 0;
//	xvid_global(NULL, XVID_GBL_INIT, &xvid_gbl_init, NULL);
//
//	/* Width and Height of input frames */
//	memset (&xvid_enc_create, 0, sizeof(xvid_enc_create));
//	xvid_enc_create.version = XVID_VERSION;
//	xvid_enc_create.width = param.nWidth;
//	xvid_enc_create.height = param.nHeight;
//	xvid_enc_create.profile = XVID_PROFILE_ARTS_L4;
//	xvid_enc_create.num_threads = 2; //in dual core
//
//	//setting bframe
//	xvid_enc_create.max_bframes = 2; //version 1.2 : support max 2 b frame
//	xvid_enc_create.bquant_ratio = 162;
//	xvid_enc_create.bquant_offset = 0;
//
//	memset(&single, 0, sizeof(xvid_plugin_single_t));
//	single.version = XVID_VERSION;
//	single.bitrate = (param.nBitrate)*1000;
//	single.reaction_delay_factor = 1;
//	single.averaging_period = 1;
//	single.buffer = 1;
//
//	xvid_enc_create.plugins = new xvid_enc_plugin_t;
//	xvid_enc_create.plugins->func = xvid_plugin_single;
//	xvid_enc_create.plugins->param = &single;
//	xvid_enc_create.num_plugins = 1;
//
//	int fps;
//	if (param.nColor == 0) //PAL
//	{
//		xvid_enc_create.fincr = 1001;
//		fps = (int) 25/param.nFrameRate;
//		xvid_enc_create.fbase = 1001*fps;
//	}
//	else
//	{
//		xvid_enc_create.fincr = 1001;
//		fps = (int) 30/param.nFrameRate;
//		xvid_enc_create.fbase = 1001*fps;
//	}
//
//	xvid_enc_create.max_key_interval = fps*10; //10s cho 1 frame I
//
//	int xerr = xvid_encore(NULL, XVID_ENC_CREATE, &xvid_enc_create, NULL);
//
//	if (xerr!=0)
//	{
//		return false;
//	}
//
//	m_hMpeg4 = xvid_enc_create.handle;
//
//	m_NumOfFrames = 0;
//
//	return true;
//}
//
//bool Mpeg4Encoder::closeVideoEncoder()
//{
//	int xerr = xvid_encore(m_hMpeg4, XVID_ENC_DESTROY, NULL, NULL);
//	if (NULL != m_pOutput)
//		delete[] m_pOutput;
//	return true;
//}
//
//int Mpeg4Encoder::encodeFrame(unsigned char* src, unsigned char* dst)
//{
////	if(m_videoparam.nColorSpace == VSS_COLOR_RGB24)
////	{
////		uint8_t* inData[1] = {src}; // RGB24 have one plane
////		int inLinesize[1] = {3*m_videoparam.nWidth}; // RGB stride
////		int outLinesize[1] = {3*m_videoparam.nWidth/2};
////		if(!m_yuvImage)
////		{
////			// alloc yuv_image
////		}
////		sws_scale(convertContext, inData, inLinesize, 0, m_videoparam.nHeight, m_yuvImage->data, outLinesize);
////	}
//	int ret = 0;
//	xvid_enc_frame_t xvid_enc_frame;
//	xvid_enc_stats_t xvid_enc_stats;
//
//	memset(&xvid_enc_frame, 0, sizeof(xvid_enc_frame));
//	xvid_enc_frame.version = XVID_VERSION;
//
//	memset(&xvid_enc_stats, 0, sizeof(xvid_enc_stats));
//	xvid_enc_stats.version = XVID_VERSION;
//
//	/* Bind output buffer */
//	xvid_enc_frame.bitstream = dst;
//	xvid_enc_frame.length = -1;
//
//	/* Initialize input image fields */
//	//xvid_enc_frame.input.plane[0] = src;
//	xvid_enc_frame.input.plane[0] = src;
//	//xvid_enc_frame.input.csp = XVID_CSP_YV12;//XVID_CSP_I420;//
//	xvid_enc_frame.input.csp = XVID_CSP_I420;//
//	xvid_enc_frame.input.stride[0] = m_videoparam.nWidth;
//
//	/* Set up core's general features */
//	xvid_enc_frame.vop_flags = vop_presets[3];
//
//	/* Frame type -- let core decide for us */
//	if (m_bFastUpdate)
//	{
//		xvid_enc_frame.type = XVID_TYPE_IVOP;
//		m_bFastUpdate = false;
//	}
//	else
//	{
//		xvid_enc_frame.type = XVID_TYPE_AUTO;
//	}
//
//	xvid_enc_frame.quant = 0;
//	xvid_enc_frame.motion = motion_presets[3];
//
//	ret = xvid_encore(m_hMpeg4, XVID_ENC_ENCODE, &xvid_enc_frame, &xvid_enc_stats);
//
//	return ret;
//}
//
