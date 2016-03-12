#ifndef _stdafx_h_
#define _stdafx_h_

#if(defined(_WIN32)||defined(_WIN64))
#include <SDKDDKVer.h>
#endif

#include <vector>
#include <memory>
#include <map>
#include <list>
#include <string>
#include <memory>
#include <string.h>

#include <stdexcept>
#if(defined(_WIN32)||defined(_WIN64))
#include <Windows.h>
#endif

#include <keye/keye_fwd.h>
#include "common/htio_fx.h"

#endif // _stdafx_h_