// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: handler.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _handler_h_
#define _handler_h_

class SessionHandler:public SessionHandlerBase<Session,Alloc>{
	typedef SessionHandlerBase<Session,Alloc> _MyBase;
public:
					SessionHandler(Alloc& ax);
	virtual void	on_open(svc_handler& sh);
	virtual void	on_close(svc_handler& sh);
	virtual bool	on_timer(svc_handler& sh,size_t id,size_t milliseconds);
private:
	bool		_auto_client;
	char		_buf[WRITE_MAX];
};
#endif