// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: pandanet_pch.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-10-30
 */
// --------------------------------------------------------
#ifndef _pandanet_pch_h_
#define _pandanet_pch_h_

//#define _USE_LIBWEBSOCKET_
/* This defined the latest Window platform.
	If you are compiling for the preversion of Windows platform,Please include <WinSDKVer.h>
	and define proper WIN32_WINNT,then include <SDKDDKVer.h>*/
#ifdef WIN32
#include <SDKDDKVer.h>
#endif

#include <memory>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <string.h>

// --------------------------------------------------------
#endif // _pandanet_pch_h_
