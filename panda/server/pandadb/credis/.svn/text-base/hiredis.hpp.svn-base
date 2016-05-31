/*
 * Copyright (c) 2009-2011, Salvatore Sanfilippo <antirez at gmail dot com>
 * Copyright (c) 2010-2011, Pieter Noordhuis <pcnoordhuis at gmail dot com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#if(defined(_WIN32)||defined(_WIN64))
#include <hiredis/hiredis_win32.h>
#include <condition_variable>
#include <thread>
#include <winsock.h>
#include <iterator>

typedef std::mutex pthread_rwlock_t;

inline int pthread_rwlock_rdlock(pthread_rwlock_t*){ return 0; }
inline int pthread_rwlock_wrlock(pthread_rwlock_t*){ return 0; }
inline int pthread_rwlock_tryrdlock(pthread_rwlock_t*){ return 0; }
inline int pthread_rwlock_trywrlock(pthread_rwlock_t*){ return 0; }
inline int pthread_rwlock_unlock(pthread_rwlock_t*){ return 0; }
inline int pthread_rwlock_init(pthread_rwlock_t*,void*){ return 0; }
inline int pthread_rwlock_destroy(pthread_rwlock_t*){ return 0; }

#else
#include <hiredis/hiredis.h>
#endif

#ifdef __HIREDIS_H___
#define __HIREDIS_H

#endif
