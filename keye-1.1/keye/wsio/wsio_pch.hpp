#ifndef _wsio_pch_h_
#define _wsio_pch_h_
// --------------------------------------------------------
#ifdef WIN32
#include <SDKDDKVer.h>
#endif

#define _WEBSOCKETPP_
#ifdef _WEBSOCKETPP_
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/common/thread.hpp>
#else
#include <libwebsocket/libwebsockets.h>
#endif

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