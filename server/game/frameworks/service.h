// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: service.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _game_service_h_
#define _game_service_h_
// --------------------------------------------------------
class Service{
public:
				Service(SessionHandler& w,Alloc& a,size_t ios=1,size_t works=1,size_t rb_size=1460);
	void		add(size_t,Session*);
	Session*	find(size_t);
	void		remove(size_t);
	//current robot index
	size_t		index;
				service svc;
private:
	std::map<size_t,Session*>	_sessions;
};
#endif