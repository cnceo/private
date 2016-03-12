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
#include <Windows.h>
#endif
// mysql
#include <mysql.h>
// --------------------------------------------------------
#endif // _proxy_pch_h_