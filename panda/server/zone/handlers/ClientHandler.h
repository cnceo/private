// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
*
*File		: ClientHandler.h
*Desc		:
*Version	: 1.0
*Program	: Vic
*Date		: 2016-4-25
*/
// --------------------------------------------------------
#ifndef _ClientHandler_h_
#define _ClientHandler_h_

class ClientHandler{
public:
	void on_message(keye::svc_handler&,keye::PacketWrapper&);
	void on_open(keye::svc_handler& sh){}
	void on_close(keye::svc_handler& sh);
	bool on_timer(keye::svc_handler& sh,size_t id,size_t milliseconds){ return true; }

public:
	void SyncPlayers(keye::svc_handler&);
};
// --------------------------------------------------------
#endif // _ClientHandler_h_
