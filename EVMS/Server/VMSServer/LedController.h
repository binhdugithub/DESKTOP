#pragma once
#include "DatabaseInterface.h"
#include "LedAPI.h"
#include <cpprest\json.h>
#include "Configuration.h"

using namespace web;

class LedController
{
public:
	DatabaseInterface *m_DBINF;
	VMSLedCtrl *m_LEDCTRL;

public:
	LedController(void);
	virtual ~LedController(void);
	bool UpdateImage(int p_id);
	int UpdateProgram(int p_id);
	bool Test(std::string p_file);
};

