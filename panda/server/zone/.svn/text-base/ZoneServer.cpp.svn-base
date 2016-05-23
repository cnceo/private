// test_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ZoneServerFwd.h"
#include <keye/htio/htio_demo.h>

#ifdef WIN32
#include <conio.h>
#else
#include <curses.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace keye;
Server* Server::instance=nullptr;

int redis(int argc,char **argv);

int main(int argc, char* argv[]) {
	//return redis(argc,argv);

	Server server;
	PandaNet::instance().initialize("zone.ini");
	DBProxy::instance().open(&server.pandaDB);
	server.dp.initialize();

	auto zoneAPort=(int)PandaNet::instance().config.value("ZoneAPort");
	auto zoneCPort=(int)PandaNet::instance().config.value("ZoneCPort");
	PDLOG<<"zone started, client port="<<zoneCPort<<", arena port="<<zoneAPort<<endf;

	server.clientService.run((unsigned short)zoneCPort);
	server.arenaService.run((unsigned short)zoneAPort);
	server.gatewayConnection.handler.connect();
	server.worldConnection.handler.connect();

	_getch();

	return 0;
}

int redis(int argc,char **argv) {
	unsigned int j;
	redisContext *c;
	redisReply *reply;
	const char *hostname = (argc > 1) ? argv[1] : "192.168.0.254";//"127.0.0.1";
	int port = (argc > 2) ? atoi(argv[2]) : 6379;
	const char* auth="panda1";

	struct timeval timeout ={1,500000}; // 1.5 seconds
	c = redisConnectWithTimeout(hostname,port,timeout);
	if(c == NULL || c->err) {
		if(c) {
			printf("Connection error: %s\n",c->errstr);
			redisFree(c);
		} else {
			printf("Connection error: can't allocate redis context\n");
		}
		exit(1);
	}

	reply = (redisReply*)redisCommand(c,"AUTH %s",auth);
	freeReplyObject(reply);

	/* PING server */
	reply = (redisReply*)redisCommand(c,"PING");
	printf("PING: %s\n",reply->str);
	freeReplyObject(reply);

	/* Set a key */
	reply = (redisReply*)redisCommand(c,"SET %s %s","foo","hello world");
	printf("SET: %s\n",reply->str);
	freeReplyObject(reply);

	/* Set a key using binary safe API */
	reply = (redisReply*)redisCommand(c,"SET %b %b","bar",(size_t)3,"hello",(size_t)5);
	printf("SET (binary API): %s\n",reply->str);
	freeReplyObject(reply);

	/* Try a GET and two INCR */
	reply = (redisReply*)redisCommand(c,"GET foo");
	printf("GET foo: %s\n",reply->str);
	freeReplyObject(reply);

	reply = (redisReply*)redisCommand(c,"INCR counter");
	printf("INCR counter: %lld\n",reply->integer);
	freeReplyObject(reply);
	/* again ... */
	reply = (redisReply*)redisCommand(c,"INCR counter");
	printf("INCR counter: %lld\n",reply->integer);
	freeReplyObject(reply);

	/* Create a list of numbers, from 0 to 9 */
	reply = (redisReply*)redisCommand(c,"DEL mylist");
	freeReplyObject(reply);
	for(j = 0; j < 10; j++) {
		char buf[64];

		snprintf(buf,64,"%d",j);
		reply = (redisReply*)redisCommand(c,"LPUSH mylist element-%s",buf);
		freeReplyObject(reply);
	}

	/* Let's check what we have inside the list */
	reply = (redisReply*)redisCommand(c,"LRANGE mylist 0 -1");
	if(reply->type == REDIS_REPLY_ARRAY) {
		for(j = 0; j < reply->elements; j++) {
			printf("%u) %s\n",j,reply->element[j]->str);
		}
	}
	freeReplyObject(reply);

	/* Disconnects and frees the context */
	redisFree(c);

	_getch();

	return 0;
}
