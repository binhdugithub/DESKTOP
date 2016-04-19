//gsoap ns service name:	nvr - Elcom Network Video Recoder
//gsoap ns service protocol:	SOAP
//gsoap ns service style:	rpc
//gsoap ns service encoding:	encoded
//gsoap ns service namespace:	http://elcom.com.vn/its/nvr
//gsoap ns service location:	http://locahost:4000
//gsoap ns schema namespace:	urn:nvr

struct result_status {
	int		errorid;			// nvr_error
	char*	errordesc;
};

enum nvr_error {
	NVR_OK,				// Successfull
	NVR_SOURCE_NOT_FOUND,		// Source not exist
	NVR_SOURCE_EXIST,			// Source has existed
	NVR_OUT_OF_CAPACITY,			// NO MORE CAPACITY FOR WRITING
	NVR_SOURCE_INIT_FAILED			// 
};

//gsoap ns service method-documentation:
int ns__startrecord(
	char* videostreamid,
	char* videostreamurl,
	int recordmode,
	int duration,
	struct result_status *result
);

//gsoap ns service method-documentation:
int ns__stoprecord(
	char* videostreamid,
	struct result_status *result
);

//gsoap ns service method-documentation:
int ns__setWriterParam(
	int capacity,
	int writemode,
	struct result_status *result
);

//gsoap ns service method-documentation:
int ns__setBackup(
	int mode,
	int timevalue,
	int capacityvalue,
	struct result_status *result
);
