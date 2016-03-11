#include "stdafx.h"
#include "game/fwd.h"
/*
#include "bsp_core.h"
#include "bsp.h"
*/
using namespace vl;

struct sMysql_t mysql_t;

int init_mysql(char *db,char *password,char *username,char *host)
{
	memset(mysql_t._db,0,sizeof(mysql_t._db));
	strcpy(mysql_t._db,db);
	memset(mysql_t._password,0,sizeof(mysql_t._password));
	strcpy(mysql_t._password,password);
	memset(mysql_t._username,0,sizeof(mysql_t._username));
	strcpy(mysql_t._username,username);
	memset(mysql_t._host,0,sizeof(mysql_t._host));
	strcpy(mysql_t._host,host);
	return 0;//RTN_SUCCESS;
}

int createOneConn(MYSQL *mysql,const char* db)
{
    mysql_init(mysql);
    if(!mysql_real_connect(mysql, mysql_t._host, mysql_t._username, mysql_t._password, db, 3306, NULL, CLIENT_MULTI_RESULTS|CLIENT_MULTI_STATEMENTS))
    {
		LOG_INFO<<"database: connect error!"<<mysql_t._host<<":"<<db<< "what: "<<mysql_error(mysql)<<endf;
		return -1;
    }
    if(mysql_set_server_option(mysql,MYSQL_OPTION_MULTI_STATEMENTS_ON)!=0)
	{
		LOG_INFO<<"database: set db option error!"<<endf;
		return -1;
	}
	ExecuteSql(mysql,"set names utf8");
	ExecuteSql(mysql,"set character set utf8");
	LOG_INFO<<"database: connected on "<<mysql_t._host<<":"<<db<<endf;
	return 0;
}
void close_mysql(MYSQL *mysql)
{
	mysql_close(mysql);
	
}
int ExecuteSql(MYSQL * mysql,const char *chSql)
{
	if(mysql&&mysql_real_query(mysql,chSql,strlen(chSql))==0)
	{
		do
		{
			 MYSQL_RES *myres=NULL;
			 myres=mysql_store_result(mysql);
			 mysql_free_result(myres);
		}while(!mysql_next_result(mysql));
		return 1;
	}
	else
	{
		return -1;
	}
}

int ExecuteStoreSql(MYSQL * mysql,const char *chSql,size_t len)
{
	if(mysql&&mysql_real_query(mysql,chSql,len)==0)
	{
		do
		{
			 MYSQL_RES *myres=NULL;
			 myres=mysql_store_result(mysql);
			 mysql_free_result(myres);
		}while(!mysql_next_result(mysql));
		return 1;
	}
	else
	{
		return -1;
	}
}


int exec(MYSQL * mysql,const char *chSql)
{
	if(mysql&&mysql_real_query(mysql,chSql,strlen(chSql))==0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}


MYSQL_RES *query(MYSQL * mysql,const char *sql)
{
	MYSQL_RES *rs = nullptr;
	if(mysql&&mysql_real_query(mysql,sql,strlen(sql))==0)
	{
		rs=mysql_store_result(mysql);
		if(mysql_affected_rows(mysql)==0)
		{
			return nullptr;
		}
		else
		{
			return rs;
		}
	}
	else
	{
		return nullptr;
	}
}

void FreeResult(MYSQL_RES *result)
{
	if(result)
		mysql_free_result(result);
}
