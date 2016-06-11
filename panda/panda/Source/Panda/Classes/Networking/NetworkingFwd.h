// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: NetworkingFwd.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-10-1
 */
// --------------------------------------------------------
#ifndef _NetworkingFwd_h_
#define _NetworkingFwd_h_

#include <memory>
#include <vector>
#include <map>
#include <string>
#include <string.h>

#if PLATFORM_WINDOWS
#include "AllowWindowsPlatformTypes.h"
#endif

#include <pandanet_fwd.h>

#if PLATFORM_WINDOWS
#include "HideWindowsPlatformTypes.h"
#endif

//fix undef from google/protobuf/stubs/type_traits.h
#if DO_CHECK && !defined(check)
#define check(expr)				{ if(UNLIKELY(!(expr))) { FDebug::LogAssertFailedMessage( #expr, __FILE__, __LINE__ ); _DebugBreakAndPromptForRemote(); FDebug::AssertFailed( #expr, __FILE__, __LINE__ ); CA_ASSUME(expr); } }
#endif

#include <Networking.h>

//#define UNREAL_SOCKET
#define KEYE_API
#include "Networking/PandaHandler.h"
#include "Networking/PandaNetProxy.h"
// --------------------------------------------------------
#endif // _NetworkingFwd_h_