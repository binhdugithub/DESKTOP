#ifndef FFMPEG_VIDEO_DECODER_H
#define FFMPEG_VIDEO_DECODER_H

#include "Codec.h"
#include "MyUtil.h"

//#include "define.h"

struct AVCodecContext;
struct AVFrame;
struct AVCodec;
struct AVPicture;
class FFMpegVideoDecoder :	public Decoder
{
public:
	FFMpegVideoDecoder(void);
	virtual ~FFMpegVideoDecoder(void);

	int width();
    int height();
	int codec();

	virtual int Init(DecoderOptions* params);
	virtual int Decode(const unsigned char* data, unsigned int length, unsigned long timestamp);

private:
	bool RenderFrame(const AVFrame *pict,unsigned long timestamp);

protected:
	DecoderOptions mOptions;
	AVCodec*		mCodec;
	AVCodecContext *mCodecCtx; //set once and not change
	AVFrame *mFrame; //set once and not change

	unsigned char *m_szTmpOutBuffer;

	// added by Longnv
	void* mConvertCtx;
	AVPicture* mRgb;
};

#endif
