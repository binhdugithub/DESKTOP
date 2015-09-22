/* soapvideooverlayService.cpp
   Generated by gSOAP 2.8.17r from videooverlayws.h

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#include "soapvideooverlayService.h"

videooverlayService::videooverlayService()
{	videooverlayService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

videooverlayService::videooverlayService(const struct soap &_soap) : soap(_soap)
{ }

videooverlayService::videooverlayService(soap_mode iomode)
{	videooverlayService_init(iomode, iomode);
}

videooverlayService::videooverlayService(soap_mode imode, soap_mode omode)
{	videooverlayService_init(imode, omode);
}

videooverlayService::~videooverlayService()
{ }

void videooverlayService::videooverlayService_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns", "urn:voverlay", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap_set_namespaces(this, namespaces);
}

void videooverlayService::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void videooverlayService::reset()
{	destroy();
	soap_done(this);
	soap_initialize(this);
	videooverlayService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

#ifndef WITH_PURE_VIRTUAL
videooverlayService *videooverlayService::copy()
{	videooverlayService *dup = SOAP_NEW_COPY(videooverlayService(*(struct soap*)this));
	return dup;
}
#endif

int videooverlayService::soap_close_socket()
{	return soap_closesock(this);
}

int videooverlayService::soap_force_close_socket()
{	return soap_force_closesock(this);
}

int videooverlayService::soap_senderfault(const char *string, const char *detailXML)
{	return ::soap_sender_fault(this, string, detailXML);
}

int videooverlayService::soap_senderfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_sender_fault_subcode(this, subcodeQName, string, detailXML);
}

int videooverlayService::soap_receiverfault(const char *string, const char *detailXML)
{	return ::soap_receiver_fault(this, string, detailXML);
}

int videooverlayService::soap_receiverfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_receiver_fault_subcode(this, subcodeQName, string, detailXML);
}

void videooverlayService::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void videooverlayService::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}
#endif

char *videooverlayService::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

void videooverlayService::soap_noheader()
{	this->header = NULL;
}

const SOAP_ENV__Header *videooverlayService::soap_header()
{	return this->header;
}

int videooverlayService::run(int port)
{	if (soap_valid_socket(this->master) || soap_valid_socket(bind(NULL, port, 100)))
	{	for (;;)
		{	if (!soap_valid_socket(accept()) || serve())
				return this->error;
			soap_destroy(this);
			soap_end(this);
		}
	}
	else
		return this->error;
	return SOAP_OK;
}

SOAP_SOCKET videooverlayService::bind(const char *host, int port, int backlog)
{	return soap_bind(this, host, port, backlog);
}

SOAP_SOCKET videooverlayService::accept()
{	return soap_accept(this);
}

#if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
int videooverlayService::ssl_accept()
{	return soap_ssl_accept(this);
}
#endif

int videooverlayService::serve()
{
#ifndef WITH_FASTCGI
	unsigned int k = this->max_keep_alive;
#endif
	do
	{

#ifndef WITH_FASTCGI
		if (this->max_keep_alive > 0 && !--k)
			this->keep_alive = 0;
#endif

		if (soap_begin_serve(this))
		{	if (this->error >= SOAP_STOP)
				continue;
			return this->error;
		}
		if (dispatch() || (this->fserveloop && this->fserveloop(this)))
		{
#ifdef WITH_FASTCGI
			soap_send_fault(this);
#else
			return soap_send_fault(this);
#endif
		}

#ifdef WITH_FASTCGI
		soap_destroy(this);
		soap_end(this);
	} while (1);
#else
	} while (this->keep_alive);
#endif
	return SOAP_OK;
}

static int serve_ns__addsource(videooverlayService*);
static int serve_ns__delsource(videooverlayService*);
static int serve_ns__runsource(videooverlayService*);
static int serve_ns__runserver(videooverlayService*);
static int serve_ns__settextposition(videooverlayService*);

int videooverlayService::dispatch()
{	soap_peek_element(this);
	if (!soap_match_tag(this, this->tag, "ns:addsource"))
		return serve_ns__addsource(this);
	if (!soap_match_tag(this, this->tag, "ns:delsource"))
		return serve_ns__delsource(this);
	if (!soap_match_tag(this, this->tag, "ns:runsource"))
		return serve_ns__runsource(this);
	if (!soap_match_tag(this, this->tag, "ns:runserver"))
		return serve_ns__runserver(this);
	if (!soap_match_tag(this, this->tag, "ns:settextposition"))
		return serve_ns__settextposition(this);
	return this->error = SOAP_NO_METHOD;
}

static int serve_ns__addsource(videooverlayService *soap)
{	struct ns__addsource soap_tmp_ns__addsource;
	struct ns__addsourceResponse soap_tmp_ns__addsourceResponse;
	struct voverlay_add_source_result soap_tmp_voverlay_add_source_result;
	soap_default_ns__addsourceResponse(soap, &soap_tmp_ns__addsourceResponse);
	soap_default_voverlay_add_source_result(soap, &soap_tmp_voverlay_add_source_result);
	soap_tmp_ns__addsourceResponse.result = &soap_tmp_voverlay_add_source_result;
	soap_default_ns__addsource(soap, &soap_tmp_ns__addsource);
	if (!soap_get_ns__addsource(soap, &soap_tmp_ns__addsource, "ns:addsource", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->addsource(soap_tmp_ns__addsource.sourceurl, soap_tmp_ns__addsource.sourcename, soap_tmp_ns__addsourceResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = "";
	soap_serializeheader(soap);
	soap_serialize_ns__addsourceResponse(soap, &soap_tmp_ns__addsourceResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__addsourceResponse(soap, &soap_tmp_ns__addsourceResponse, "ns:addsourceResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__addsourceResponse(soap, &soap_tmp_ns__addsourceResponse, "ns:addsourceResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns__delsource(videooverlayService *soap)
{	struct ns__delsource soap_tmp_ns__delsource;
	struct ns__delsourceResponse soap_tmp_ns__delsourceResponse;
	struct soap_overlay_status soap_tmp_soap_overlay_status;
	soap_default_ns__delsourceResponse(soap, &soap_tmp_ns__delsourceResponse);
	soap_default_soap_overlay_status(soap, &soap_tmp_soap_overlay_status);
	soap_tmp_ns__delsourceResponse.result = &soap_tmp_soap_overlay_status;
	soap_default_ns__delsource(soap, &soap_tmp_ns__delsource);
	if (!soap_get_ns__delsource(soap, &soap_tmp_ns__delsource, "ns:delsource", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->delsource(soap_tmp_ns__delsource.sourceurl, soap_tmp_ns__delsourceResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = "";
	soap_serializeheader(soap);
	soap_serialize_ns__delsourceResponse(soap, &soap_tmp_ns__delsourceResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__delsourceResponse(soap, &soap_tmp_ns__delsourceResponse, "ns:delsourceResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__delsourceResponse(soap, &soap_tmp_ns__delsourceResponse, "ns:delsourceResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns__runsource(videooverlayService *soap)
{	struct ns__runsource soap_tmp_ns__runsource;
	struct ns__runsourceResponse soap_tmp_ns__runsourceResponse;
	struct soap_overlay_status soap_tmp_soap_overlay_status;
	soap_default_ns__runsourceResponse(soap, &soap_tmp_ns__runsourceResponse);
	soap_default_soap_overlay_status(soap, &soap_tmp_soap_overlay_status);
	soap_tmp_ns__runsourceResponse.result = &soap_tmp_soap_overlay_status;
	soap_default_ns__runsource(soap, &soap_tmp_ns__runsource);
	if (!soap_get_ns__runsource(soap, &soap_tmp_ns__runsource, "ns:runsource", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->runsource(soap_tmp_ns__runsource.command, soap_tmp_ns__runsource.sourceurl, soap_tmp_ns__runsourceResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = "";
	soap_serializeheader(soap);
	soap_serialize_ns__runsourceResponse(soap, &soap_tmp_ns__runsourceResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__runsourceResponse(soap, &soap_tmp_ns__runsourceResponse, "ns:runsourceResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__runsourceResponse(soap, &soap_tmp_ns__runsourceResponse, "ns:runsourceResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns__runserver(videooverlayService *soap)
{	struct ns__runserver soap_tmp_ns__runserver;
	struct ns__runserverResponse soap_tmp_ns__runserverResponse;
	struct soap_overlay_status soap_tmp_soap_overlay_status;
	soap_default_ns__runserverResponse(soap, &soap_tmp_ns__runserverResponse);
	soap_default_soap_overlay_status(soap, &soap_tmp_soap_overlay_status);
	soap_tmp_ns__runserverResponse.result = &soap_tmp_soap_overlay_status;
	soap_default_ns__runserver(soap, &soap_tmp_ns__runserver);
	if (!soap_get_ns__runserver(soap, &soap_tmp_ns__runserver, "ns:runserver", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->runserver(soap_tmp_ns__runserver.command, soap_tmp_ns__runserverResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = "";
	soap_serializeheader(soap);
	soap_serialize_ns__runserverResponse(soap, &soap_tmp_ns__runserverResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__runserverResponse(soap, &soap_tmp_ns__runserverResponse, "ns:runserverResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__runserverResponse(soap, &soap_tmp_ns__runserverResponse, "ns:runserverResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns__settextposition(videooverlayService *soap)
{	struct ns__settextposition soap_tmp_ns__settextposition;
	struct ns__settextpositionResponse soap_tmp_ns__settextpositionResponse;
	struct soap_overlay_status soap_tmp_soap_overlay_status;
	soap_default_ns__settextpositionResponse(soap, &soap_tmp_ns__settextpositionResponse);
	soap_default_soap_overlay_status(soap, &soap_tmp_soap_overlay_status);
	soap_tmp_ns__settextpositionResponse.result = &soap_tmp_soap_overlay_status;
	soap_default_ns__settextposition(soap, &soap_tmp_ns__settextposition);
	if (!soap_get_ns__settextposition(soap, &soap_tmp_ns__settextposition, "ns:settextposition", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->settextposition(soap_tmp_ns__settextposition.lanepos, soap_tmp_ns__settextposition.staffpos, soap_tmp_ns__settextposition.classpos, soap_tmp_ns__settextposition.licensenumberpos, soap_tmp_ns__settextposition.pricepos, soap_tmp_ns__settextposition.timestamppos, soap_tmp_ns__settextpositionResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = "";
	soap_serializeheader(soap);
	soap_serialize_ns__settextpositionResponse(soap, &soap_tmp_ns__settextpositionResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__settextpositionResponse(soap, &soap_tmp_ns__settextpositionResponse, "ns:settextpositionResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__settextpositionResponse(soap, &soap_tmp_ns__settextpositionResponse, "ns:settextpositionResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}
/* End of server object code */