// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: session.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _session_h_
#define _session_h_

class Player;
struct Packet{
	unsigned short	length,
					opcode;
	unsigned char	data[0];
};

class Session:public SessionBase<Alloc>{
public:
					Session(keye::svc_handler&,Alloc&);
					~Session();
	virtual void	handle(const keye::packet_t& p){_handle(*(Packet*)&p);}
	//
	Player*			player();
	void			handleAuth(Packet&);
private:
	void			_handle(Packet&);

	std::string		_name;
	Player*			_player;
};

struct OpcodeHandler{
	char const* name;
	void (Session::*handler)(Packet&);
};
extern OpcodeHandler handlers[NUM_MSG_TYPES];

#endif