// test_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "pandadb_fwd.h"

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace keye;

RedisProxy::RedisProxy():context(nullptr){}

bool RedisProxy::connect(const char* hostname,unsigned short port,const char* auth,int tm){
	struct timeval timeout ={tm,0};
	context = redisConnectWithTimeout(hostname,port,timeout);
	if(context == nullptr || context->err) {
		if(context) {
			PDLOG<<"Connection error: "<<context->errstr<<"\n";
			redisFree(context);
		} else {
			PDLOG<<"Connection error: can't allocate redis context\n";
		}
		context=nullptr;
	} else{
		auto reply = (redisReply*)redisCommand(context,"AUTH %s",auth);
		auto ok=reply->type!=REDIS_REPLY_ERROR;
		freeReplyObject(reply);
		return ok;
	}
	return false;
}

void RedisProxy::close(){
	if(context)redisFree(context);
}
