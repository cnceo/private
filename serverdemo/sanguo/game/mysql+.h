#ifndef BSP_MYSQL_H

#define BSP_MYSQL_H                            1

#include <mysql/mysql.h>

struct sMysql_t
{
	char _host[20];
	char _db[20];
	char _password[20];
	char _username[20];
};

int init_mysql(char *,char *,char *,char *);
int createOneConn(MYSQL *,const char*);
MYSQL_RES *query(MYSQL *,const char *);
int ExecuteSql(MYSQL *,const char *);
int ExecuteStoreSql(MYSQL *,const char *,size_t);
int exec(MYSQL *,const char *);
void FreeResult(MYSQL_RES *);
void close_mysql(MYSQL *);

#endif  /* mysql+.h */
