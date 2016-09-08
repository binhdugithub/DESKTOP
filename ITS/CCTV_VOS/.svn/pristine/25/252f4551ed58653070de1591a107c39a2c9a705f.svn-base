
//#include "Mp4Encode.h"
//#include <string.h>
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
//CMp4Encoder* CMp4Encoder::m_pInstance = NULL;
//
//CMp4Encoder* CMp4Encoder::getInstance()
//{
//	if(!m_pInstance)
//		m_pInstance = new CMp4Encoder;
//
//	return m_pInstance;
//}
//
//void CMp4Encoder::removeInstance()
//{
//	if(m_pInstance)
//	{
//		m_pInstance->Exit();
//		delete m_pInstance;
//		m_pInstance = NULL;
//	}
//}
//
//CMp4Encoder::CMp4Encoder(void) :
//	CEncoder()
//{
//	m_bFastUpdate = false;
//	m_pOutput = new unsigned char[1024*1024];
//	getDefaultParam(&m_videoparam);
//}
//
//CMp4Encoder::~CMp4Encoder(void)
//{
//
//}
//
//
//int CMp4Encoder::enc_init()
//{
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
//	xvid_enc_create.width = m_videoparam.nWidth;
//	xvid_enc_create.height = m_videoparam.nHeight;
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
//	single.bitrate = (m_videoparam.nBitrate)*1000;
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
//	if (m_videoparam.nColor == 0) //PAL
//	{
//		xvid_enc_create.fincr = 1001;
//		fps = (int) 25/m_videoparam.nFrameRate;
//		xvid_enc_create.fbase = 1001*fps;
//	}
//	else
//	{
//		xvid_enc_create.fincr = 1001;
//		fps = (int) 30/m_videoparam.nFrameRate;
//		xvid_enc_create.fbase = 1001*fps;
//	}
//
//	xvid_enc_create.max_key_interval = fps*10; //10s cho 1 frame I
//
//	int xerr = xvid_encore(NULL, XVID_ENC_CREATE, &xvid_enc_create, NULL);
//
//	if (xerr!=0)
//	{
//		//// PTRACE(1, "CMp4Encoder::enc_init: call xvid_encore got error " << xerr);
//		return xerr;
//	}
//
//	m_hMpeg4 = xvid_enc_create.handle;
//
//	m_NumOfFrames = 0;
//
//	return 0;
//}
//
//int CMp4Encoder::enc_main(unsigned char *image, unsigned char *bitstream)
//{
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
//	xvid_enc_frame.bitstream = bitstream;
//	xvid_enc_frame.length = -1;
//
//	/* Initialize input image fields */
//	xvid_enc_frame.input.plane[0] = image;
//	xvid_enc_frame.input.csp = XVID_CSP_YV12;//XVID_CSP_I420;//
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
//
//		//// PTRACE(1, "enc_main. xvid_enc_frame.type = XVID_TYPE_IVOP");
//	}
//	else
//	{
//		xvid_enc_frame.type = XVID_TYPE_AUTO;
//	}
//
//	xvid_enc_frame.quant = 0;
//	xvid_enc_frame.motion = motion_presets[3];
//
//	int ret = xvid_encore(m_hMpeg4, XVID_ENC_ENCODE, &xvid_enc_frame, &xvid_enc_stats);
//
//	return ret;
//}
//
//int CMp4Encoder::Init()
//{
//	// PTRACE(1, "Enter CMp4Encoder::init. width = " << m_videoparam.nWidth \
//		<< " height = " << m_videoparam.nHeight \
//		<< " bitrate = " << m_videoparam.nBitrate);
//
//	int nRet=enc_init();
//
//	return nRet;
//}
//
//
//int CMp4Encoder::setting(void* pParam)
//{
//	memcpy(&m_videoparam, pParam, sizeof(VSS_SETTING));
//	return 0;
//}
//
//
//int CMp4Encoder::getVideoSetting(void* pParam)
//{
//	memcpy(pParam, &m_videoparam, sizeof(VSS_SETTING));
//	return 0;
//}
//
//
//int CMp4Encoder::encode(unsigned char* pDataIn, unsigned long dwSize, unsigned long dwTS)
//{
//	int sizeout = 0;
//	try
//	{
//		sizeout = enc_main(pDataIn, m_pOutput);
//
//		if (sizeout < 0)
//		{
//			// PTRACE(1, "CMp4Encoder::encode. call enc_main got error");
//			return -1;
//		}
//		else
//		{
//			// PTRACE(5, "CMp4Encoder::encode success. Sizeout = " << sizeout);
//			/*if (is_vop_start_code(m_pOutput))
//			{
//				Log(1,"CMp4Encoder::encode coding 2 bit cuoi = %d.  2 bit dau =%d original = %d",get_vop_coding_type(m_pOutput),m_pOutput[4]&0xC0,m_pOutput[4]);
//
//			}
//			*/
//
//			//OnEncodedData(m_pOutput, sizeout, dwTS);
//			outSize = sizeout;
//			timesptamp = dwTS;
//			return sizeout;
//		}
//	}
//	catch(...)
//	{
//		// PTRACE(1, "CMp4Encoder::encode exeption while encode data");
//		return -1;
//	}
//}
//
//void CMp4Encoder::getEncodeData(unsigned char* pDataOut, unsigned long& dwSize, unsigned long& dwTS)
//{
//	pDataOut = m_pOutput;
//	dwSize = outSize;
//	dwTS = timesptamp;
//}
//
//
//void CMp4Encoder::OnEncodedData(unsigned char* pData, int nSize, unsigned long dwTS)
//{
//	//if (m_pEncodedCallback != NULL)
//		//m_pEncodedCallback(pData, nSize, dwTS*90, 1, m_pUser);
//	//else
//		// PTRACE(1, "CMp4Encoder::OnEncodedData():\tm_pEncodedCallback = NULL");
//}
//
//void CMp4Encoder::getDefaultParam(VSS_SETTING* pSetting)
//{
//	pSetting->nProfile = VSS_BALINE_PROFILE;
//	pSetting->nLevel = 30;
//
//	pSetting->nEntropyMode = VSS_ENTROPY_CAVLC;
//	pSetting->nFrameRate = VSS_FRAME_RATE_FULL;
//	pSetting->nColor = 1;//VSS_COLOR_PAL;
//	pSetting->nBitrate = 512;
//
//	pSetting->nWidth = 1024;
//	pSetting->nHeight = 768;
//	pSetting->nSenceDectect = 1;
//	pSetting->nRateControlMode = VSS_RATE_CONTROL_CBR;
//	pSetting->nIdrPicture = 33;
//
//	pSetting->nContentEncoder = 0;
//}
//
//int CMp4Encoder::Exit()
//{
//
//	int xerr = xvid_encore(m_hMpeg4, XVID_ENC_DESTROY, NULL, NULL);
//
//	if (NULL != m_pOutput)
//		delete[] m_pOutput;
//
//	// PTRACE(1, "Call destroy mpeg4 encoder. return " << xerr);
//	return 0;
//}
//
//int CMp4Encoder::changeBitrate(int nNewBitrate)
//{
//	// PTRACE(1, "Enter CMp4Encoder::changeBitrate. New bitrate = " << nNewBitrate);
//
//	if (m_videoparam.nBitrate == nNewBitrate)
//	{
//		// PTRACE(1, "CMp4Encoder::changeBitrate new bitrate = old bitrate = " << nNewBitrate);
//		return 0;
//	}
//
//	m_videoparam.nBitrate = nNewBitrate;
//
//	int xerr = xvid_encore(m_hMpeg4, XVID_ENC_DESTROY, NULL, NULL);
//	int nRet=enc_init();
//
//
//	// PTRACE(1, "Leave CMp4Encoder::changeBitrate");
//
//	return 0;
//}
//int CMp4Encoder::fastUpdate()
//{
//	// PTRACE(1, "CMp4Encoder::fastUpdate()");
//	m_bFastUpdate = true;
//
//	return 0;
//}
//
//void CMp4Encoder::SetFormat(int nColor,int nFrameRate)
//{
//	// PTRACE(1,"Enter CMp4Encoder::SetFormat: nColor = " << nColor << " nFrameRate = " << nFrameRate);
//	m_videoparam.nColor = nColor;
//	m_videoparam.nFrameRate = nFrameRate;
//	int xerr = xvid_encore(m_hMpeg4, XVID_ENC_DESTROY, NULL, NULL);
//	int nRet=enc_init();
//	// PTRACE(1,"Leave CMp4Encoder::SetFormat: nColor = " << nColor << " nFrameRate = " << nFrameRate);
//}
