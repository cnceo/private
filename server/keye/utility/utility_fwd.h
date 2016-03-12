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

#include <keye/utility/system.h>
#include <keye/utility/buffer.h>
#include <keye/utility/thread.h>
#include <keye/utility/logger.h>
#include <keye/utility/library.h>
#include <keye/utility/scheduler.h>
#include <keye/utility/joint.h>
#include <keye/utility/joint_scheduler.h>
#include <keye/utility/behavior.h>
#include <keye/utility/conf_file.h>
#include <keye/utility/security.h>
#include <keye/utility/md5_generate.h>
#include <keye/utility/guid_t.h>
// --------------------------------------------------------
#endif // _utility_fwd_h_