//
//  utilfwd.h
//  sanguo
//
//  Created by Vic Liu on 9/12/15.
//  Copyright (c) 2015 Vic Liu. All rights reserved.
//

#ifndef _utilfwd_h
#define _utilfwd_h

// --------------------------------------------------------
#ifndef VL_API
#   if(defined(_WIN32)||defined(_WIN64))&&_WINDLL
#       if VL_EXPORT
#           define VL_API __declspec(dllexport)
#       else
#           define VL_API __declspec(dllimport)
#       endif
#   else
#       define VL_API
#   endif
#endif //VL_API

#ifndef LOG
#	define LOG printf
#endif

#ifndef s_ptr
#	define s_ptr std::shared_ptr
#endif

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "utils.h"
#include "fileutil.h"
#include "locallog.h"

#endif
