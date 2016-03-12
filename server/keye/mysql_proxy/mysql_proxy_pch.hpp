#ifndef _proxy_pch_h_
#define _proxy_pch_h_
// --------------------------------------------------------
#if(defined(_WIN32)||defined(_WIN64))
#include <SDKDDKVer.h>
#endif

#include <vector>
#include <memory>
#include <map>
#include <list>
#include <string>
#include <memory>

#include <stdexcept>
#if(defined(_WIN32)||defined(_WIN64))
/*
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN     // Exclude rarely-used stuff from Windows headers
#endif
*/
#include <Windows.h>
#endif
// mysql
#include <mysql.h>
// --------------------------------------------------------
#endif // _proxy_pch_h_