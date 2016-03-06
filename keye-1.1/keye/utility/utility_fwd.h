#ifndef _utility_fwd_h_
#define _utility_fwd_h_
// --------------------------------------------------------
#ifndef KEYE_API
#if(defined(_WIN32)||defined(_WIN64))&&_WINDLL
	#if KEYE_EXPORT
		#define KEYE_API __declspec(dllexport)
	#else
		#define KEYE_API __declspec(dllimport)
	#endif
#else
	#define KEYE_API
#endif
#endif //KEYE_API

#ifndef LOG
#	define LOG printf
#endif

#ifndef s_ptr
#	define s_ptr std::shared_ptr
#endif

#include <keye/utility/logger.h>
#include <keye/utility/conf_file.h>
// --------------------------------------------------------
#endif // _utility_fwd_h_