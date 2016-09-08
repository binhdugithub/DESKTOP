/* soapnvrProxy.h
   Generated by gSOAP 2.8.17r from nvrws.h

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapnvrProxy_H
#define soapnvrProxy_H
#include "soapH.h"

class SOAP_CMAC nvrProxy : public soap
{ public:
	/// Endpoint URL of service 'nvrProxy' (change as needed)
	const char *soap_endpoint;
	/// Constructor
	nvrProxy();
	/// Construct from another engine state
	nvrProxy(const struct soap&);
	/// Constructor with endpoint URL
	nvrProxy(const char *url);
	/// Constructor with engine input+output mode control
	nvrProxy(soap_mode iomode);
	/// Constructor with URL and input+output mode control
	nvrProxy(const char *url, soap_mode iomode);
	/// Constructor with engine input and output mode control
	nvrProxy(soap_mode imode, soap_mode omode);
	/// Destructor frees deserialized data
	virtual	~nvrProxy();
	/// Initializer used by constructors
	virtual	void nvrProxy_init(soap_mode imode, soap_mode omode);
	/// Delete all deserialized data (with soap_destroy and soap_end)
	virtual	void destroy();
	/// Delete all deserialized data and reset to default
	virtual	void reset();
	/// Disables and removes SOAP Header from message
	virtual	void soap_noheader();
	/// Get SOAP Header structure (NULL when absent)
	virtual	const SOAP_ENV__Header *soap_header();
	/// Get SOAP Fault structure (NULL when absent)
	virtual	const SOAP_ENV__Fault *soap_fault();
	/// Get SOAP Fault string (NULL when absent)
	virtual	const char *soap_fault_string();
	/// Get SOAP Fault detail as string (NULL when absent)
	virtual	const char *soap_fault_detail();
	/// Close connection (normally automatic, except for send_X ops)
	virtual	int soap_close_socket();
	/// Force close connection (can kill a thread blocked on IO)
	virtual	int soap_force_close_socket();
	/// Print fault
	virtual	void soap_print_fault(FILE*);
#ifndef WITH_LEAN
	/// Print fault to stream
#ifndef WITH_COMPAT
	virtual	void soap_stream_fault(std::ostream&);
#endif

	/// Put fault into buffer
	virtual	char *soap_sprint_fault(char *buf, size_t len);
#endif

	/// Web service operation 'startrecord' (returns error code or SOAP_OK)
	virtual	int startrecord(char *videostreamid, char *videostreamurl, int recordmode, int duration, struct result_status *result) { return this->startrecord(NULL, NULL, videostreamid, videostreamurl, recordmode, duration, result); }
	virtual	int startrecord(const char *endpoint, const char *soap_action, char *videostreamid, char *videostreamurl, int recordmode, int duration, struct result_status *result);

	/// Web service operation 'stoprecord' (returns error code or SOAP_OK)
	virtual	int stoprecord(char *videostreamid, struct result_status *result) { return this->stoprecord(NULL, NULL, videostreamid, result); }
	virtual	int stoprecord(const char *endpoint, const char *soap_action, char *videostreamid, struct result_status *result);

	/// Web service operation 'setWriterParam' (returns error code or SOAP_OK)
	virtual	int setWriterParam(int capacity, int writemode, struct result_status *result) { return this->setWriterParam(NULL, NULL, capacity, writemode, result); }
	virtual	int setWriterParam(const char *endpoint, const char *soap_action, int capacity, int writemode, struct result_status *result);

	/// Web service operation 'setBackup' (returns error code or SOAP_OK)
	virtual	int setBackup(int mode, int timevalue, int capacityvalue, struct result_status *result) { return this->setBackup(NULL, NULL, mode, timevalue, capacityvalue, result); }
	virtual	int setBackup(const char *endpoint, const char *soap_action, int mode, int timevalue, int capacityvalue, struct result_status *result);
};
#endif