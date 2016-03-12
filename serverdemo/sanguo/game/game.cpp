// --------------------------------------------------------
/*Copyright Keye Knew.All rights reserved.
 *
 *File		: game.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: Keye Knew
 *Date		: 2012-3-7
 */
// --------------------------------------------------------
#include "stdafx.h"
#include "game/fwd.h"
#include <signal.h>
#include <time.h>
#include "websocket_service.h"

#define _DEVELOP
#ifndef _DEVELOP
#if defined(WIN32)||defined(WIN64)
#define _DEVELOP
#endif
#endif

#if !(defined(WIN32)||defined(WIN64))
#include <unistd.h>	//fork
#include <fcntl.h>
#endif

using namespace vl;
using namespace std;

static void _platform_init();

// --------------------------------------------------------
INSTANCE_IMP(Game)
Game::~Game(){
}

int Game::run(int argc,char* argv[]){
	//config
	Overkill = 0;
	auto& cfg=config();
	cfg.load("server.ini");

	auto port=(unsigned short)(int)cfg.value("port");
	const char
		*db_host=cfg.value("mysql_host"),
		*db_user=cfg.value("mysql_user"),
		*db_pswd=cfg.value("mysql_pswd"),
		*db_name=cfg.value("mysql_db");
	//auto db_port=(unsigned short)(int)cfg.value("mysql_port");

	//override port
	if(argc>1&&argv){
		unsigned short n=atoi(argv[1]);
		if(n!=0)port=n;
	}

	//mysql
    init_mysql((char*)db_name,(char*)db_pswd,(char*)db_user,(char*)db_host);
    if(createOneConn(&_mysql,db_name))return -1;
	createOneConn(&_mysql_login,"web");

	//	proxy().connect(host,port,user,pswd,db);
	srand((int)time(nullptr));
	_platform_init();

	//networks
    websocket_service wspp;
    wspp.run(port+1,[](size_t cid,const void* buf,size_t len){
        if(-1==client_onData(cid,(char*)buf,len,Game::instance()->getMysqlConn()))
            printf("message error, exit");
    });
    LOG_INFO<<"websocket listen on "<<port<<Endl;

    InitCrc32Table();
    _running=true;
	while(_running||!stopped())
#ifdef WIN32
		Sleep(3000);
#else
		usleep(3000);
#endif
	/*
	switch(std::getchar()){
	case 'x':
		stop();
		exit=true;
		break;
	}
	*/
	return 0;
}

void Game::stop(){
//	if(_sx)_sx->close();
//    else
        _running=false;
}

bool Game::stopped(){
	return
    //_sx?_sx->closed():
    true;
}

Logger& Game::log(){
	if(!_log){
#ifdef _DEVELOP
		_log.reset(new Logger());
#else
		time_t t=time(NULL);
		tm* aTm=localtime(&t);
		char buf[32];
		sprintf(buf,"%02d-%02d-%02d.log",aTm->tm_mon+1,aTm->tm_mday,aTm->tm_hour);
		_log.reset(new Logger(buf));
#endif
	}
	return *_log;
}

MYSQL* Game::getMysqlConn(){
    return _mysql.host_info&&_mysql.user?&_mysql:nullptr;
}

MYSQL* Game::getMysqlLogin(){
    return _mysql_login.host_info&&_mysql_login.user?&_mysql_login:nullptr;
}

static void _sig_hup(int){};
static void _sig_int(int){
	Game::instance()->stop();
}

static void _inst_signal(){
#if !(defined(WIN32)||defined(WIN64))
	signal(SIGHUP,_sig_hup);
    signal(SIGQUIT,_sig_int);
    signal(SIGKILL,_sig_int);
    // Ignore SIGPIPE & SIGCLD
    struct sigaction *sa = (struct sigaction *) malloc(sizeof(struct sigaction));
    sa->sa_handler = SIG_IGN;
    sa->sa_flags = 0;
    signal(SIGPIPE, SIG_IGN);
    if (sigemptyset(&sa->sa_mask) == -1 || sigaction(SIGPIPE, sa, 0) == -1){
        fprintf(stderr, "Ignore SIGPIPE failed\n");
        exit(-1);
    }
#endif
	signal(SIGINT,_sig_int);
    signal(SIGTERM,_sig_int);
}

static void _daemonize(){
#ifndef _DEVELOP
	// Fork a new process
	switch(fork()){
	case -1 :
		return;
	case 0 :
		break;
	default :
		exit(1);
	}
	if (setsid() == -1)return;
	// Redirect standard IO to null device
	int fd = open("/dev/null", O_RDWR, 0);
	if (fd){
		(void) dup2(fd, STDIN_FILENO);
		(void) dup2(fd, STDOUT_FILENO);
		(void) dup2(fd, STDERR_FILENO);
		if (fd > STDERR_FILENO)
			(void) close(fd);
	}
#endif
}

static void _platform_init(){
	_daemonize();
	_inst_signal();
}

void Game::on_timer(size_t id){
    //time_t now=time(nullptr);
    if(FRAME_TIMER_ID==id){
    }
}

logger& Begl(logger& l){
    return l<<begl;
    time_t t=time(NULL);
    tm* aTm=localtime(&t);
    /* YYYY	year
     MM   month (2 digits 01-12)
     DD   day (2 digits 01-31)
     HH   hour (2 digits 00-23)
     MM   minutes (2 digits 00-59)
     SS   seconds (2 digits 00-59) */
    char buf[32];
    sprintf(buf,"%02d-%02d-%02d:%02d:%02d ",aTm->tm_mon+1,aTm->tm_mday,aTm->tm_hour,aTm->tm_min,aTm->tm_sec);
    return l<<(const char*)buf;
}
logger& Endl(logger& l){
    return l<<endf;
    l<<'\n';
    l.flush();
    return l;
}
