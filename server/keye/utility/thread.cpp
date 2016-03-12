// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: thread.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-09-09
 */
// --------------------------------------------------------
#include "stdafx.h"
#include <keye/utility/utility_fwd.h>
#include <mutex>

namespace keye{
// --------------------------------------------------------
typedef std::mutex Mutex;
//typedef boost::interprocess::named_mutex IPMutex;
class mutex_impl{
	friend class mutex_t;
				mutex_impl():_locked(false){}
	void		lock()	{if(!_locked){_m.lock();_locked=true;}}
	void		unlock(){if(_locked){_m.unlock();_locked=false;}}
	Mutex		_m;
	bool		_locked;
};
/*
class ip_mutex_impl{
	friend class ip_mutex_t;
				ip_mutex_impl(const char* n):_locked(false){
					try{
						//open first
						IPMutex::remove(n);
						_m.reset(new IPMutex(boost::interprocess::open_only,n));
					}catch(boost::interprocess::interprocess_exception& e){
						//then create
						try{
							_m.reset(new IPMutex(boost::interprocess::create_only,n));
						}catch(boost::interprocess::interprocess_exception& e){
							LOG("create named_mutex %s failed.%s\n",n,e.what());
						}
					}
				}
	void		lock()	{if(_m&&!_locked){_m->lock();_locked=true;}}
	void		unlock(){if(_m&&_locked){_m->unlock();_locked=false;}}
	std::shared_ptr<IPMutex>	_m;
	bool		_locked;
};
*/
mutex_t::mutex_t()		{_impl.reset(new mutex_impl);}
void mutex_t::lock()	{if(_impl)_impl->lock();}
void mutex_t::unlock()	{if(_impl)_impl->unlock();}
/*
ip_mutex_t::ip_mutex_t(const char* n){
	_impl.reset(new ip_mutex_impl(n));
}
void ip_mutex_t::lock()		{if(_impl)_impl->lock();}
void ip_mutex_t::unlock()	{if(_impl)_impl->unlock();}
*/
// --------------------------------------------------------
//a simple boost thread wrapper,template has void run() function
template<typename _Tx>
class thread_impl_t{
public:
	thread_impl_t(_Tx& t){
		_t.reset(new std::thread(boost::bind(&_Tx::run,&t)));
	}
	~thread_impl_t(){
		if(_t)_t->join();
	}
private:
	std::shared_ptr<std::thread>	_t;
};

class thread_impl{
	friend class thread_t;
	thread_impl(thread_t::T& t):_impl(t){}
	thread_impl_t<thread_t::T> _impl;
};

thread_t::thread_t(T& t){
	_impl.reset(new thread_impl(t));
}
// --------------------------------------------------------
};//namespace keye
