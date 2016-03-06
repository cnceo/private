// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: protocol
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _WebSocketDelegate_h_
#define _WebSocketDelegate_h_

#ifdef _ALPHA_PRE_
	typedef cocos2d::extension::WebSocket	WebSocket_t;
#else
	typedef cocos2d::network::WebSocket		WebSocket_t;
#endif

class WebSocketDelegate:public WebSocket_t::Delegate{
public:
    virtual void onOpen(WebSocket_t* ws);
    virtual void onMessage(WebSocket_t* ws, const WebSocket_t::Data& data);
    virtual void onClose(WebSocket_t* ws);
    virtual void onError(WebSocket_t* ws, const WebSocket_t::ErrorCode& error);
};

#endif
