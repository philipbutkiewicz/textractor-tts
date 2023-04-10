#pragma once

#include "Textractor.h"

#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>

#define _SAPI_VER 0x053 // Set the SAPI version to 5.3

#include <sapi.h>
#include <sphelper.h>

#include <list>

#include "GameFilter.h"
#include "GameFilterRewritePlus.h"

struct SKIP {};
inline void Skip() { throw SKIP(); }

bool Initialize();
bool InitializeVoice();
void InitializeGameFilters();
void UninitializeVoice();