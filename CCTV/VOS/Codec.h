#ifndef AVCODECS_CODEC_H__
#define AVCODECS_CODEC_H__

#include <string>

typedef struct EncoderOptions
{
	// for common
	void (*callback_func)(const unsigned char* data, unsigned int length, unsigned long timestamp, void* user_data);
	void *user_data;
	unsigned int kbps;
	unsigned int rtp_payload_size; // optional
	// for audio
	unsigned int samplerate;
	unsigned int channels;
	unsigned int bitpersample;
	// for video
	unsigned int width;
	unsigned int height;
	unsigned int gop_size;
	unsigned int framerate_num;
	unsigned int framerate_den;
	unsigned int level;
	unsigned int profile;

}EncoderOptions;

typedef struct DecoderOptions
{
	// for common
	void (*callback_func)(const unsigned char* samples, unsigned int length, unsigned long timestamp, void* user_data, unsigned long reserved1, unsigned long reserved2);
	void *user_data;
	// for video
	unsigned int width;
	unsigned int height;
	int codec_type;
	// for SDP options
	char* optional_parameters;

}DecoderOptions;

class Encoder
{
public:
	virtual int Init(EncoderOptions* params) = 0;
	virtual int Encode(const unsigned char* samples, unsigned int length, unsigned long timestamp) = 0;
	virtual void FastUpdate() = 0;
	virtual int ChangeBitrate(int newKbps) = 0;
};

class Decoder
{
public:
	Decoder() {}
	virtual ~Decoder() {}

	virtual int Init(DecoderOptions* params) = 0;
	virtual int Decode(const unsigned char* data, unsigned int length, unsigned long timestamp) = 0;
	virtual void flush() {};
};
#endif//AVCODECS_CODEC_H__