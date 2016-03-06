// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: http_client.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _http_client_h_
#define _http_client_h_

namespace keye{
class KEYE_API http_responser{
public:
	virtual void	handle(const std::string&)=0;
};

class http_client_impl;
class KEYE_API http_client{
public:
					http_client(htio_alloc&);
	bool			connect(const char*,unsigned short=80);
	int				request(const char* =nullptr);
	void			set_responser(http_responser*);
/*
	//special for ACE
	int				OnSocketOpen(HttpSocket*);
	void			QueuePack(WorldPacket*);
	void			Update(uint32);
*/
private:
	std::shared_ptr<http_client_impl>	_impl;
};};
#endif
