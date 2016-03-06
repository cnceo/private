// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: service.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-10-1
 */
// --------------------------------------------------------
#ifndef _service_h_
#define _service_h_

namespace keye{
// --------------------------------------------------------
/* service to process io,_W must be pass into,
	_W must derive from work_handler and it handles io event,
	_A must derice from htio_alloc and it allocate for service,
	io runs on io threads,events and timer run on work threads,
	threads are auto chosen */
// --------------------------------------------------------
class service_impl;
class KEYE_API service{
public:
	//ios:io threads;works:work threads;rb_size:read buffer max size
			service(work_handler& w,htio_alloc& a,size_t ios=1,size_t works=1,size_t rb_size=510);
	//run as server,we do not open accept while port was 0
	void	run(unsigned short port=0,const char* address=nullptr);
	//run as client and connect to server
	void	connect(const char* address,unsigned short port,unsigned short conns=1);
	void	close();
	bool	closed()const;
	//set up a timer on work thread,id is overlayable
	void	set_timer(size_t id,size_t milliseconds);
	void	unset_timer(size_t id);
	//post event to work thead
	void	post_event(void* buf,size_t length);
private:
	std::shared_ptr<service_impl>	_svc;
};
// --------------------------------------------------------
};
#endif // _service_h_