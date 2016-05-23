// test_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "pandadb_fwd.h"
#include <algorithm>
#include <ctype.h>

using namespace std;
using namespace keye;

DBProxy* DBProxy::_instance=nullptr;
DBProxy& DBProxy::instance(){
	if(!_instance){
		_instance=new DBProxy;
		_instance->handler=nullptr;
	}
	return *_instance;
}

bool DBProxy::open(IDBHandler* h){
	handler=h;

	auto DBHost=(const char*)PandaNet::instance().config.value("DBHost");
	auto DBUser=(const char*)PandaNet::instance().config.value("DBUser");
	auto DBAuth=(const char*)PandaNet::instance().config.value("DBAuth");
	auto DBName=(const char*)PandaNet::instance().config.value("DBName");
	auto DBPort=(int)PandaNet::instance().config.value("DBPort");

	auto RedisHost=(const char*)PandaNet::instance().config.value("RedisHost");
	auto RedisAuth=(const char*)PandaNet::instance().config.value("RedisAuth");
	auto RedisPort=(int)PandaNet::instance().config.value("RedisPort");
	PDLOG<<"db="<<DBHost<<", port="<<DBPort<<", user="<<DBUser<<", auth="<<DBAuth<<", db="<<DBName
		<<"\nredis="<<RedisHost<<", port="<<RedisPort<<", auth="<<RedisAuth<<endf;

	//192.168.0.107:3306
	spmysql.reset(new mysql_proxy(1));
	if(spmysql->connect(DBHost,DBPort,DBUser,DBAuth,DBName)){
		PDLOG<<"connected to db.\n";
	} else{
		spmysql.reset();
		PDLOG<<"connected to db failed.\n";
	}

	//192.168.0.254:6379
	spredis.reset(new RedisProxy);
	if(spredis->connect(RedisHost,RedisPort,RedisAuth,5)){
		PDLOG<<"connected to redis.\n";
		return true;
	} else{
		spredis.reset();
		PDLOG<<"connected to redis failed.\n";
		return false;
	}
}

void DBProxy::close(){
	if(spredis)spredis->close();
	spmysql.reset();
	spredis.reset();
}

string DBProxy::key(const char* db,const char* table,const char* uid,const char* field){
	string k;
	if(db&&table&&uid){
		//panda:account:10000:name
		char buf[128];
		if(field)
			sprintf(buf,"%s:%s:%s:%s",db,table,uid,field);
		else
			sprintf(buf,"%s:%s:%s",db,table,uid);
		k=buf;
	}
	return k;
}
void DBProxy::copy(DBResult& d,const redisReply& s){
	d.type=(DBResult::Type)s.type;
	d.value=s.integer;
	if(s.str)d.str=s.str;
	for(size_t i=0;i<s.elements;++i){
		d.arr.push_back(DBResult());
		copy(d.arr.back(),*s.element[i]);
	}
}

void DBProxy::copy(DBResult& d,const keye::mysql_resultset& s){
	//only single line supported currently
	if(!s.error.empty())
		d.type=DBResult::Type::REPLY_ERROR;
	else if(s.rows.empty())
		d.type=DBResult::Type::REPLY_NIL;
	else{
		auto& row=s.rows[0];
		if(s.head.size()>1){
			d.type=DBResult::Type::REPLY_ARRAY;
			for(size_t i=0,ii=row.fields.size();i<ii;++i){
				d.arr.push_back(DBResult());
				parse(d.arr.back(),row.fields[i],s.head[i]);
			}
		} else{
			parse(d,row.fields[0],s.head[0]);
		}
	}
}

void DBProxy::parse(DBResult& d,void* data,e_field ef){
	d.type=DBResult::Type::REPLY_INTEGER;
	unsigned short field_len=0;
	switch(ef){
	case EF_BYTE:
		d.value=(size_t)*(unsigned char*)data;
		break;
	case EF_SHORT:
		d.value=(size_t)*(unsigned short*)data;
		break;
	case EF_INT:
		d.value=(size_t)*(unsigned*)data;
		break;
	case EF_LONGLONG:
		d.value=(size_t)*(unsigned long long*)data;
		break;
	case EF_STRING:
	case EF_BLOB:
		d.type=DBResult::Type::REPLY_STRING;
		buf_get(field_len,(const char**)&data);
		d.str.resize(field_len);
		memcpy((void*)d.str.data(),data,field_len);
		break;
	}
}

void DBProxy::handle(mysql_resultset& resultset){
	//resultset.debug_log();
	DBResult res;
	copy(res,resultset);
	if(handler)handler->handle((int)resultset.id,&res,resultset.privdata);
}

void DBProxy::exec(const char* cmdRedis,const char* cmdDB,int qid,void* privdata){
	DBResult res;
	if(spredis){
		if(cmdRedis){
			if(auto reply=(redisReply*)redisCommand(spredis->context,cmdRedis)){
				/*
				#define REDIS_REPLY_STRING 1
				#define REDIS_REPLY_ARRAY 2
				#define REDIS_REPLY_INTEGER 3
				#define REDIS_REPLY_NIL 4
				#define REDIS_REPLY_STATUS 5
				#define REDIS_REPLY_ERROR 6
				*/
				if(reply->type!=REDIS_REPLY_NIL&&reply->type!=REDIS_REPLY_ERROR)
					//query succeeded
					copy(res,*reply);
				freeReplyObject(reply);
			}
		}
		if(cmdDB&&(res.type==DBResult::Type::REPLY_NONE||
			res.type==DBResult::Type::REPLY_ARRAY&&res.arr.size()<=0||
			is_modify_cmd(cmdRedis,cmdDB))){
			//query failed OR modify
			if(spmysql){
				mysql_parameter param(0,qid,privdata);
				mysql_statement st(cmdDB);
				spmysql->execute(st,&param,this);
				return;
			}
		}
	}
	if(handler)handler->handle(qid,&res,privdata);
}

bool DBProxy::is_modify_cmd(const char* cmdRedis,const char* cmdDB){
	//get,select
	//set,insert,update
	const size_t N=10;
	if(cmdRedis){
		string str(cmdRedis);
		if(str.length()>N)str.resize(N);
		for(auto it=str.begin(),iend=str.end();it!=iend;++it)
			(*it)=toupper(*it);
		//transform(str.begin(),str.end(),str.begin(),toupper);
		if(str.find("GET")!=string::npos)
			return false;
	}
	if(cmdDB){
		string str(cmdDB);
		if(str.length()>N)str.resize(N);
                for(auto it=str.begin(),iend=str.end();it!=iend;++it)
                        (*it)=toupper(*it);
                //transform(str.begin(),str.end(),str.begin(),toupper);
		if(str.find("SELECT")!=string::npos)
			return false;
	}
	return true;
}
