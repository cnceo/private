// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: statement.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#include "stdafx.h"
#include "game_fwd.h"

using namespace keye;

Statements_t stmts[STMT_MAX];
#define REG_STMT(N,H,S) \
	reg_stmt(N,#N,S,&ProxyHandler::##H)

static inline void reg_stmt(e_stmt p,const char* name,const char* sql,void (ProxyHandler::*handler)(mysql_resultset&)){
	stmts[p].name=name;
	stmts[p].sql=sql;
	stmts[p].handler=handler;
}

void reg_stmt(){
	memset(stmts,0,sizeof(stmts));
	REG_STMT(STMT_AUTH,handleAuth,"SELECT id FROM account WHERE username=\'%s\' and sessionkey=\'%s\'");
}
