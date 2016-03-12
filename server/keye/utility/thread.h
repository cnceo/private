// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: thread
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-09-09
 */
// --------------------------------------------------------
#ifndef _thread_h_
#define _thread_h_

namespace keye{
// --------------------------------------------------------
// mutext
// --------------------------------------------------------
class mutex_impl;
class ip_mutex_impl;
//a fast mutex
class KEYE_API mutex_t{
public:
				mutex_t();
	void		lock();
	void		unlock();
private:
	std::shared_ptr<mutex_impl> _impl;
};

//an named interprocess mutex
class KEYE_API ip_mutex_t{
public:
				ip_mutex_t(const char*);
	void		lock();
	void		unlock();
private:
	std::shared_ptr<ip_mutex_impl> _impl;
};

//a scoped lock wrapper
template<typename _Mtx>
class KEYE_API scoped_lock_t{
public:
				scoped_lock_t(_Mtx& m):_m(m){
					_m.lock();
				}
				~scoped_lock_t(){
					_m.unlock();
				}
private:
	_Mtx&		_m;
};
// --------------------------------------------------------
// thread wrapper
// --------------------------------------------------------
class thread_impl;
class KEYE_API thread_t{
public:
	struct T{
				~T(){}
		virtual void run()=0;
	};
				thread_t(T&);
private:
	std::shared_ptr<thread_impl> _impl;
};
// --------------------------------------------------------
};//namespace keye
#endif//

