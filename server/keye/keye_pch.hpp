// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: core_pch.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-10-30
 */
// --------------------------------------------------------
#ifndef _core_pch_h_
#define _core_pch_h_

#ifndef NO_MYSQL
#define NO_MYSQL
#endif
/* This defined the latest Window platform.
	If you are compiling for the preversion of Windows platform,Please include <WinSDKVer.h>
	and define proper WIN32_WINNT,then include <SDKDDKVer.h>*/
#if(defined(_WIN32)||defined(_WIN64))
#include <SDKDDKVer.h>
#endif

#include "keye/utility/utility_pch.hpp"
#include "keye/htio/htio_pch.hpp"
#ifndef NO_MYSQL
#include <keye/mysql_proxy/mysql_proxy_pch.hpp>
#endif
// --------------------------------------------------------
#endif // _core_pch_h_
