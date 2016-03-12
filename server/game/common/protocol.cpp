// --------------------------------------------------------
/*Copyright Keye Knew.All rights reserved.
 *
 *File		: protocal.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: Keye Knew
 *Date		: 2012-3-7
 */
// --------------------------------------------------------
#include "stdafx.h"
#include "game_fwd.h"

using namespace keye;
using namespace std;

#define REG_PROTOCOL(P,H) \
	reg_protocol(P,#P,&Session::##H)

static inline void reg_protocol(Opcodes p,const char* name,void (Session::*handler)(Packet&)){
	handlers[p].name=name;
	handlers[p].handler=handler;
}

void init_protocal(){
	memset(handlers,0,sizeof(handlers));
	REG_PROTOCOL(CMSG_AUTH_SESSION,handleAuth);
}
