// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: proxy.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _proxy_h_
#define _proxy_h_

class Session;
/*
template typename<N=1>
class ProxyT:public mysql_proxy{
public:
					Proxy(unsigned char=N):mysql_proxy(N){}
};
typedef ProxyT<2> Proxy;
*/
class Proxy:public mysql_proxy{
public:
					Proxy();
	void			authorize(Session*,const char*,const char*);
};

class ProxyHandler:public mysql_handler{
public:
					ProxyHandler(Session*);
	virtual void	handle(mysql_resultset&);
	void			handleAuth(mysql_resultset&);

	Session*		session;
};

#endif