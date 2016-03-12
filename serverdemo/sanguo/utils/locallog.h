//
//  locallog.h
//  sanguo
//
//  Created by Vic Liu on 9/12/15.
//  Copyright (c) 2015 Vic Liu. All rights reserved.
//

#ifndef __sanguo__locallog__
#define __sanguo__locallog__

namespace vl{
    // --------------------------------------------------------
    // logger
    // --------------------------------------------------------
    class logger_impl;
    class VL_API logger{
    public:
        logger(const char* =nullptr);
        logger&		operator<<(char v);
        logger&		operator<<(int v);
        logger&		operator<<(unsigned int v);
        logger&		operator<<(long long v);
        logger&		operator<<(unsigned long long v);
        logger&		operator<<(const char* v);
        logger&		operator<<(const std::string& v);
        logger&		operator<<(logger& (*)(logger&));
        void		flush();
    private:
        s_ptr<logger_impl>	_impl;
    };
    
    VL_API logger& begl(logger&);		//begin line with time stamp[MM-DD-HH:MM:SS]
    VL_API logger& endl(logger&);		//change line
    VL_API logger& endf(logger&);		//change line and flush
    VL_API logger& flush(logger&);	//flush log
    // --------------------------------------------------------
};// namespace

#endif /* defined(__sanguo__locallog__) */
