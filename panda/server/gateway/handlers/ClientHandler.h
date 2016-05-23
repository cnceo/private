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

class ClientHandler:public BaseHandler{
public:
	void on_message(keye::svc_handler&,keye::PacketWrapper&);
};
// --------------------------------------------------------
#endif // _ClientHandler_h_
