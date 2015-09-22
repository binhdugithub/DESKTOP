
/* 
   base64.cpp and base64.h

   Copyright (C) 2004-2008 René Nyffenegger

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   René Nyffenegger rene.nyffenegger@adp-gmbh.ch

*/

#pragma once
#include <ostream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>

using namespace std;

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};

static char *decoding_table = NULL;
static int mod_table[] = {0, 2, 1};
/* aaaack but it's fast and const should make it shared text page. */
static const char basis_64[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const unsigned char pr2six[256] =
{
    /* ASCII table */
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
    64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
    64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};


class Base64
{
public:
	Base64(void);
	virtual ~Base64(void);

	static inline bool is_base64(unsigned char c) 
	{
	  bool true_false = (isalnum(c) || (c == '+') || (c == '/'));
	  if(true_false)
		 printf("true");
	  else
		  printf("false");

	  return true_false;
	}

	static std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
	static std::string base64_decode(std::string const& encoded_string);

	static char *base64_encode_2(const unsigned char *data,
						size_t input_length,
						size_t *output_length) 
	{

		*output_length = 4 * ((input_length + 2) / 3);

		char *encoded_data = (char*)malloc(*output_length);
		if (encoded_data == NULL) return NULL;

		for (int i = 0, j = 0; i < input_length;)
		{

			uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
			uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
			uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

			uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

			encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
			encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
			encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
			encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
		}

		for (int i = 0; i < mod_table[input_length % 3]; i++)
			encoded_data[*output_length - 1 - i] = '=';

		return encoded_data;
	}


	static unsigned char *base64_decode_2(const char *data,
								 size_t input_length,
								 size_t *output_length)
	{

		if (decoding_table == NULL) 
			build_decoding_table();

		if (input_length % 4 != 0) return NULL;

		*output_length = input_length / 4 * 3;
		if (data[input_length - 1] == '=') (*output_length)--;
		if (data[input_length - 2] == '=') (*output_length)--;

		unsigned char *decoded_data = (unsigned char*)malloc(*output_length);
		if (decoded_data == NULL) return NULL;

		for (int i = 0, j = 0; i < input_length;)
		{

			uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
			uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
			uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
			uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

			uint32_t triple = (sextet_a << 3 * 6)
			+ (sextet_b << 2 * 6)
			+ (sextet_c << 1 * 6)
			+ (sextet_d << 0 * 6);

			if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
			if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
			if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
		}

		return decoded_data;
	}


	static void build_decoding_table() 
	{

		decoding_table = (char*)malloc(256);

		for (int i = 0; i < 64; i++)
			decoding_table[(unsigned char) encoding_table[i]] = i;
	}



	static int Base64decode_len(const char *bufcoded)
	{
		int nbytesdecoded;
		register const unsigned char *bufin;
		register int nprbytes;

		bufin = (const unsigned char *) bufcoded;
		while (pr2six[*(bufin++)] <= 63);

		nprbytes = (bufin - (const unsigned char *) bufcoded) - 1;
		nbytesdecoded = ((nprbytes + 3) / 4) * 3;

		return nbytesdecoded + 1;
	}

	static int Base64decode(char *bufplain, const char *bufcoded)
	{
		int nbytesdecoded;
		register const unsigned char *bufin;
		register unsigned char *bufout;
		register int nprbytes;

		bufin = (const unsigned char *) bufcoded;
		while (pr2six[*(bufin++)] <= 63);
		nprbytes = (bufin - (const unsigned char *) bufcoded) - 1;
		nbytesdecoded = ((nprbytes + 3) / 4) * 3;

		bufout = (unsigned char *) bufplain;
		bufin = (const unsigned char *) bufcoded;

		while (nprbytes > 4) 
		{
			*(bufout++) =
				(unsigned char) (pr2six[*bufin] << 2 | pr2six[bufin[1]] >> 4);
			*(bufout++) =
				(unsigned char) (pr2six[bufin[1]] << 4 | pr2six[bufin[2]] >> 2);
			*(bufout++) =
				(unsigned char) (pr2six[bufin[2]] << 6 | pr2six[bufin[3]]);
			bufin += 4;
			nprbytes -= 4;
		}

		/* Note: (nprbytes == 1) would be an error, so just ingore that case */
		if (nprbytes > 1) {
		*(bufout++) =
			(unsigned char) (pr2six[*bufin] << 2 | pr2six[bufin[1]] >> 4);
		}
		if (nprbytes > 2) {
		*(bufout++) =
			(unsigned char) (pr2six[bufin[1]] << 4 | pr2six[bufin[2]] >> 2);
		}
		if (nprbytes > 3) {
		*(bufout++) =
			(unsigned char) (pr2six[bufin[2]] << 6 | pr2six[bufin[3]]);
		}

		*(bufout++) = '\0';
		nbytesdecoded -= (4 - nprbytes) & 3;
		return nbytesdecoded;
	}



	static int Base64encode_len(int len)
	{
		return ((len + 2) / 3 * 4) + 1;
	}

	static int Base64encode(char *encoded, const char *string, int len)
	{
		int i;
		char *p;

		p = encoded;
		for (i = 0; i < len - 2; i += 3) {
		*p++ = basis_64[(string[i] >> 2) & 0x3F];
		*p++ = basis_64[((string[i] & 0x3) << 4) |
						((int) (string[i + 1] & 0xF0) >> 4)];
		*p++ = basis_64[((string[i + 1] & 0xF) << 2) |
						((int) (string[i + 2] & 0xC0) >> 6)];
		*p++ = basis_64[string[i + 2] & 0x3F];
		}
		if (i < len) {
		*p++ = basis_64[(string[i] >> 2) & 0x3F];
		if (i == (len - 1)) {
			*p++ = basis_64[((string[i] & 0x3) << 4)];
			*p++ = '=';
		}
		else {
			*p++ = basis_64[((string[i] & 0x3) << 4) |
							((int) (string[i + 1] & 0xF0) >> 4)];
			*p++ = basis_64[((string[i + 1] & 0xF) << 2)];
		}
		*p++ = '=';
		}

		*p++ = '\0';
		return p - encoded;
	}

};

