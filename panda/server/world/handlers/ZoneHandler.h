// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
*
*File		: ZoneHandler.h
*Desc		:
*Version	: 1.0
*Program	: Vic
*Date		: 2016-4-25
*/
// --------------------------------------------------------
#ifndef _ZoneHandler_h_
#define _ZoneHandler_h_

class ZoneHandler{
public:
	void on_message(keye::svc_handler&,keye::PacketWrapper&);
	void on_open(keye::svc_handler& sh){}
	void on_close(keye::svc_handler& sh);
	bool on_timer(keye::svc_handler& sh,size_t id,size_t milliseconds){ return true; }
};
// --------------------------------------------------------
#endif // _ZoneHandler_h_
