// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: BaseSession.h
 *Desc		: 
 *Version	: 1.0
 *Program	: Vic
 *Date		: 2016-4-25
 */
// --------------------------------------------------------
#ifndef _BaseSession_h_
#define _BaseSession_h_
// --------------------------------------------------------
class PANDA_API BaseSession{
public:
	virtual ~BaseSession(){}
	virtual void on_open(keye::svc_handler& sh){
		this->sh=sh();
	}

	size_t	sid;
	std::shared_ptr<keye::svc_handler>	sh;
};
// --------------------------------------------------------
#endif // _BaseSession_h_
