// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: statement.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _statement_h_
#define _statement_h_

#ifndef NO_MYSQL
enum e_stmt:unsigned short{
	STMT_AUTH,
	STMT_MAX
};
struct Statements_t{
	const char* name;
	const char* sql;
	void (ProxyHandler::*handler)(mysql_resultset&);
};

extern Statements_t stmts[STMT_MAX];
void reg_stmt();

#endif
#endif