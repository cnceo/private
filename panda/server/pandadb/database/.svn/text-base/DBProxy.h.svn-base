// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: DBProxy.h
 *Desc		: 
 *Version	: 1.0
 *Program	: Vic
 *Date		: 2016-4-25
 */
// --------------------------------------------------------
#ifndef _DBProxy_h_
#define _DBProxy_h_

class RedisProxy;
class IDBHandler;
struct DBResult;

// --------------------------------------------------------
class PANDA_API DBProxy:public keye::mysql_handler{
public:
	static DBProxy& instance();
	bool			open(IDBHandler*);
	void			close();
	void			exec(const char* cmdRedis,const char* cmdDB,int qid,void* privdata=nullptr);
	static std::string	key(const char* db,const char* table,const char* uid=0,const char* field=nullptr);
private:
	virtual void	handle(keye::mysql_resultset&);
	void			copy(DBResult&,const redisReply&);
	void			copy(DBResult&,const keye::mysql_resultset&);
	void			parse(DBResult& d,void* data,keye::e_field ef);
	bool			is_modify_cmd(const char* cmdRedis,const char* cmdDB);

	std::shared_ptr<keye::mysql_proxy>	spmysql;
	std::shared_ptr<RedisProxy>			spredis;
	IDBHandler*							handler;
	static DBProxy*						_instance;
};
// --------------------------------------------------------
#endif // _DBProxy_h_
