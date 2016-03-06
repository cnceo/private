#ifndef _wsio_pch_h_
#define _wsio_pch_h_
// --------------------------------------------------------
#ifdef WIN32
#include <SDKDDKVer.h>
#endif

#include <libwebsocket/libwebsockets.h>

#include <functional>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
// --------------------------------------------------------
#endif // _wsio_pch_h_