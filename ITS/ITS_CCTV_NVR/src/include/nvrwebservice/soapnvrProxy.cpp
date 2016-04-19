/* soapnvrProxy.cpp
   Generated by gSOAP 2.8.17r from nvrws.h

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#include "soapnvrProxy.h"

nvrProxy::nvrProxy()
{	nvrProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

nvrProxy::nvrProxy(const struct soap &_soap) : soap(_soap)
{ }

nvrProxy::nvrProxy(const char *url)
{	nvrProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
	soap_endpoint = url;
}

nvrProxy::nvrProxy(soap_mode iomode)
{	nvrProxy_init(iomode, iomode);
}

nvrProxy::nvrProxy(const char *url, soap_mode iomode)
{	nvrProxy_init(iomode, iomode);
	soap_endpoint = url;
}

nvrProxy::nvrProxy(soap_mode imode, soap_mode omode)
{	nvrProxy_init(imode, omode);
}

nvrProxy::~nvrProxy()
{ }

void nvrProxy::nvrProxy_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	soap_endpoint = NULL;
	static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns", "urn:nvr", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap_set_namespaces(this, namespaces);
}

void nvrProxy::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void nvrProxy::reset()
{	destroy();
	soap_done(this);
	soap_initialize(this);
	nvrProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

void nvrProxy::soap_noheader()
{	this->header = NULL;
}

const SOAP_ENV__Header *nvrProxy::soap_header()
{	return this->header;
}

const SOAP_ENV__Fault *nvrProxy::soap_fault()
{	return this->fault;
}

const char *nvrProxy::soap_fault_string()
{	return *soap_faultstring(this);
}

const char *nvrProxy::soap_fault_detail()
{	return *soap_faultdetail(this);
}

int nvrProxy::soap_close_socket()
{	return soap_closesock(this);
}

int nvrProxy::soap_force_close_socket()
{	return soap_force_closesock(this);
}

void nvrProxy::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void nvrProxy::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}
#endif

char *nvrProxy::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

int nvrProxy::startrecord(const char *endpoint, const char *soap_action, char *videostreamid, char *videostreamurl, int recordmode, int duration, struct result_status *result)
{	struct soap *soap = this;
	struct ns__startrecord soap_tmp_ns__startrecord;
	struct ns__startrecordResponse *soap_tmp_ns__startrecordResponse;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://locahost:4000";
	soap_begin(soap);
	soap->encodingStyle = "";
	soap_tmp_ns__startrecord.videostreamid = videostreamid;
	soap_tmp_ns__startrecord.videostreamurl = videostreamurl;
	soap_tmp_ns__startrecord.recordmode = recordmode;
	soap_tmp_ns__startrecord.duration = duration;
	soap_serializeheader(soap);
	soap_serialize_ns__startrecord(soap, &soap_tmp_ns__startrecord);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__startrecord(soap, &soap_tmp_ns__startrecord, "ns:startrecord", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__startrecord(soap, &soap_tmp_ns__startrecord, "ns:startrecord", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!result)
		return soap_closesock(soap);
	soap_default_result_status(soap, result);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__startrecordResponse = soap_get_ns__startrecordResponse(soap, NULL, "", "");
	if (!soap_tmp_ns__startrecordResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (result && soap_tmp_ns__startrecordResponse->result)
		*result = *soap_tmp_ns__startrecordResponse->result;
	return soap_closesock(soap);
}

int nvrProxy::stoprecord(const char *endpoint, const char *soap_action, char *videostreamid, struct result_status *result)
{	struct soap *soap = this;
	struct ns__stoprecord soap_tmp_ns__stoprecord;
	struct ns__stoprecordResponse *soap_tmp_ns__stoprecordResponse;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://locahost:4000";
	soap_begin(soap);
	soap->encodingStyle = "";
	soap_tmp_ns__stoprecord.videostreamid = videostreamid;
	soap_serializeheader(soap);
	soap_serialize_ns__stoprecord(soap, &soap_tmp_ns__stoprecord);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__stoprecord(soap, &soap_tmp_ns__stoprecord, "ns:stoprecord", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__stoprecord(soap, &soap_tmp_ns__stoprecord, "ns:stoprecord", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!result)
		return soap_closesock(soap);
	soap_default_result_status(soap, result);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__stoprecordResponse = soap_get_ns__stoprecordResponse(soap, NULL, "", "");
	if (!soap_tmp_ns__stoprecordResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (result && soap_tmp_ns__stoprecordResponse->result)
		*result = *soap_tmp_ns__stoprecordResponse->result;
	return soap_closesock(soap);
}

int nvrProxy::setWriterParam(const char *endpoint, const char *soap_action, int capacity, int writemode, struct result_status *result)
{	struct soap *soap = this;
	struct ns__setWriterParam soap_tmp_ns__setWriterParam;
	struct ns__setWriterParamResponse *soap_tmp_ns__setWriterParamResponse;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://locahost:4000";
	soap_begin(soap);
	soap->encodingStyle = "";
	soap_tmp_ns__setWriterParam.capacity = capacity;
	soap_tmp_ns__setWriterParam.writemode = writemode;
	soap_serializeheader(soap);
	soap_serialize_ns__setWriterParam(soap, &soap_tmp_ns__setWriterParam);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__setWriterParam(soap, &soap_tmp_ns__setWriterParam, "ns:setWriterParam", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__setWriterParam(soap, &soap_tmp_ns__setWriterParam, "ns:setWriterParam", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!result)
		return soap_closesock(soap);
	soap_default_result_status(soap, result);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__setWriterParamResponse = soap_get_ns__setWriterParamResponse(soap, NULL, "", "");
	if (!soap_tmp_ns__setWriterParamResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (result && soap_tmp_ns__setWriterParamResponse->result)
		*result = *soap_tmp_ns__setWriterParamResponse->result;
	return soap_closesock(soap);
}

int nvrProxy::setBackup(const char *endpoint, const char *soap_action, int mode, int timevalue, int capacityvalue, struct result_status *result)
{	struct soap *soap = this;
	struct ns__setBackup soap_tmp_ns__setBackup;
	struct ns__setBackupResponse *soap_tmp_ns__setBackupResponse;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://locahost:4000";
	soap_begin(soap);
	soap->encodingStyle = "";
	soap_tmp_ns__setBackup.mode = mode;
	soap_tmp_ns__setBackup.timevalue = timevalue;
	soap_tmp_ns__setBackup.capacityvalue = capacityvalue;
	soap_serializeheader(soap);
	soap_serialize_ns__setBackup(soap, &soap_tmp_ns__setBackup);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__setBackup(soap, &soap_tmp_ns__setBackup, "ns:setBackup", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__setBackup(soap, &soap_tmp_ns__setBackup, "ns:setBackup", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!result)
		return soap_closesock(soap);
	soap_default_result_status(soap, result);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__setBackupResponse = soap_get_ns__setBackupResponse(soap, NULL, "", "");
	if (!soap_tmp_ns__setBackupResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (result && soap_tmp_ns__setBackupResponse->result)
		*result = *soap_tmp_ns__setBackupResponse->result;
	return soap_closesock(soap);
}
/* End of client proxy code */
