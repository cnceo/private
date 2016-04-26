// test_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <keye/htio/htio_demo.h>
#include "../protocol.h"

#ifdef WIN32
#include <conio.h>
#else
#include <curses.h>
#endif

using namespace keye;

// --------------------------------------------------------
// SessionServer
// --------------------------------------------------------
class Player{
public:
	int id;
};

class Server:public SessionServer<Player>{
	PackHelper<svc_handler> packer;
public:
	virtual void	on_read(svc_handler& sh,void* buf,size_t sz){
		std::vector<std::shared_ptr<void>> packets;
		packer.on_read(packets,buf,sz);
		MsgRaw* msgRaw=nullptr;
		for each (auto& spw in packets){
			auto data=spw.get();
			auto mid=(eMsg)*(unsigned short*)data;
			switch(mid){
			case MSG_RAW:
				if(msgRaw=(MsgRaw*)data)
					printf("mid=%d,msg=%s\n",(int)msgRaw->mid,msgRaw->message);
				break;
			case MSG_GAME:
				break;
			case MSG_LOGIN:
				break;
			case MSG_LOGINREP:
				break;
			default:
				break;
			}
		}
		printf("bravo\n");
	}
};

int main(int argc, char* argv[]) {
	unsigned short port = 8899;
	//myserver(port, 4, 4);
	Server server;
	server.run(port);

	printf("press any key to continue ...\n");
	_getch();

	return 0;
}
