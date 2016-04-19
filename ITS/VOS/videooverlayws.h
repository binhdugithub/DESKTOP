//gsoap ns service name:	videooverlay - Elcom ITS Video Overlay
//gsoap ns service protocol:	SOAP
//gsoap ns service style:	rpc
//gsoap ns service encoding:	encoded
//gsoap ns service namespace:	http://elcom.com.vn/its/voverlay
//gsoap ns service location:	http://locahost:port
//gsoap ns schema namespace:	urn:voverlay

struct soap_overlay_status {
	int		errorid;			// voverlay_error
	char*	errordesc;
};
/*
enum voverlay_error {
	VOVERLAY_OK,				// Successfull
	VOVERLAY_SOURCE_NOT_FOUND,		// Source not exist
	VOVERLAY_SOURCE_EXIST,			// Source has existed
	VOVERLAY_FULLHD_NOT_SUPPORT,	// Dont support HD1080 resolution
	VOVERLAY_OVERLOAD,				// Server is out of load
	VOVERLAY_URL_INVALID,			// Url input is invalid
	VOVERLAY_INIT_FAILED			// Server init failed: decoder, encoder, multicast receiver
};
*/
struct voverlay_add_source_result {
	struct soap_overlay_status state;
	char* output_url;	
};

//gsoap ns service method-documentation:
int ns__addsource(
	char* sourceurl,		// URL of camera source
	char* sourcename, 		// Friendly name of source
	struct voverlay_add_source_result *result
);

//gsoap ns service method-documentation:
int ns__delsource(
	char* sourceurl,
	struct soap_overlay_status *result
);

//gsoap ns service method-documentation:
int ns__runsource(
	int command,	// 0=stop, 1=start, 2=restart
	char* sourceurl,
	struct soap_overlay_status *result
);

//gsoap ns service method-documentation:
int ns__runserver(
	int command,	// 0=stop, 1=start, 2=restart
	struct soap_overlay_status *result
);

//gsoap ns service method-documentation:
int ns__settextposition(
	int lanepos,
	int staffpos,
	int classpos,
	int licensenumberpos,
	int pricepos,
	int timestamppos,
	struct soap_overlay_status *result
);
