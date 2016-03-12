// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: player.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#include "stdafx.h"
#include "game/fwd.h"
#include "time.h"

#if defined(_USE_WEBSOCKETPP_)
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#endif

using namespace vl;

Player::Player(std::weak_ptr<void> sh)
:_wsppsh(sh)
,_sock_type(ST_WEBSOCKET){
    _client_id=(size_t)sh.lock().get();
    Game::instance()->connects().add(_client_id,this);
}
/*
void Player::handle(svc_handler&,const keye::packet_t& p){
	auto msg=(char*)&p;
	auto len=p.length;
	if(-1==client_onData(_client_id,msg,len,Game::instance()->getMysqlConn()))
		_sh->close();
}
*/
void Player::send(const void* buf,size_t len){
    typedef websocketpp::server<websocketpp::config::asio> server;
    server::connection_ptr con = websocketpp::lib::static_pointer_cast<server::connection_type>(_wsppsh.lock());
    con->send(buf,len);
    auto ptr=(short*)buf;
    LOG_INFO<<"send "<<*++ptr<<Endl;
}

int append_client(size_t clt_id, const char *data, size_t len)
{
    Player* p=Game::instance()->players().find(clt_id);
    if(!p)
        p=Game::instance()->connects().find(clt_id);
    if(p){
        p->send(data,len);
        //		LOG_INFO<<"debug: --- send message( client="<<(long long)clt_id<<",cmd="<<(int)*((const short*)data+1)<<endf;
        return (int)len;
    }else
        return 0;
}

void sendToOne(size_t client,void *pPak,size_t len)
{
    static char buffer[20480];
    memset(buffer,0,20480);
    //    char buffer[len+2];
    SetShort(1,len+2,buffer);
    memcpy(buffer+2,pPak,len);
    append_client(client,buffer,len+2);
}

bool is_sameday(time_t tm0,time_t tm1){
    tm *atm=localtime(&tm0);
    int y=atm->tm_year,
    m=atm->tm_mon,
    d=atm->tm_mday;
    atm=localtime(&tm1);
    return (atm->tm_year==y&&
            atm->tm_mon==m&&
            atm->tm_mday==d);
}

void Player::Send(const void* buf,size_t len){
	sendToOne(_client_id,(void*)buf,len);
}

void Player::update(){
}

void Player::update_Timer(){
}

void Player::close(){
    typedef websocketpp::server<websocketpp::config::asio> server;
    server::connection_ptr con = websocketpp::lib::static_pointer_cast<server::connection_type>(_wsppsh.lock());
    if(con)con->close(0,"");
}

Player::~Player(){
	logOut();
	if(_sock_type!=ST_WEBSOCKET)
		client_close(_client_id);
	Game::instance()->connects().remove(_client_id);
}

void Player::release(){
	if(_sock_type==ST_WEBSOCKET)
		delete this;
}

void Player::login(int uid){
//	_client_id=uid;	
	
	auto now=time(nullptr);
    struct userData *curr=spData.get();
	if(curr)curr->signal_flag=(is_sameday(now,time_signal))?1:0;

	//proc online time
	MYSQL* mysql=Game::instance()->getMysqlConn();
	char sql[128];
	if(!is_sameday(now,time_login)){
		//clear online time
		sprintf(sql,"UPDATE t_user SET time_online=0 WHERE user_id=%d;",uid);
//		sprintf(sql,"UPDATE t_user SET time_total=time_total+time_online,time_online=0 WHERE user_id=%d;",uid);
		exec(mysql,sql);
	}
	//update login time
	time_login=now;
	sprintf(sql,"UPDATE t_user SET time_login=%lld WHERE user_id=%d;",now,uid);
	exec(mysql,sql);

#ifdef CARD_NEW
	InitCheckGardGroup(uid);
	LoadCardGroup(uid);
#endif
}

void Player::logOut()
{
	if(!spData)return;

	//proc online time
	auto now=time(nullptr);
	auto uid=spData->user_id;
	MYSQL* mysql=Game::instance()->getMysqlConn();
    MYSQL_RES *res=nullptr;
    MYSQL_ROW row;
	char sql[128];
	const int AC_TIME=int(60.f*0.5f);	//0.5hour in minite
	int time_online=0,time_total=0,ac_day=0;
	//read time_online
	sprintf(sql,"SELECT time_online,ac_days FROM t_user WHERE user_id=%d;",uid);
    if(res=query(mysql,sql)){
        if(row=mysql_fetch_row(res)){
            time_online=row[0]?atoi(row[0]):0;
            ac_day=row[1]?atoi(row[1]):0;
		}
		FreeResult(res);
    }
	const time_t interval=(now-time_login);
	bool ac_flag=true;
	if(!is_sameday(now,time_login)){
		tm* atm=localtime(&time_login);
		int h0=atm->tm_hour,
			m0=atm->tm_min;
		atm=localtime(&now);
		int h1=atm->tm_hour,
			m1=atm->tm_min;
		//calc ac day before
		if(time_online<AC_TIME){
			if(h0<23||(time_online+60-m0)>AC_TIME)
				++ac_day;
		}

		int days=((interval/60-m1)/60-h1)/24;	//more than one day
		ac_day+=days;

		//calc ac day of today
		time_online=h1*60+m1;
		if(time_online>=AC_TIME)
			++ac_day;
		//update time_login on today
		time_login=now;
	}else{
		ac_flag=(time_online<AC_TIME);
		time_online+=interval/60;	//in minite
		//calc ac day of today
		if(ac_flag&&time_online>=AC_TIME)
			++ac_day;
	}
	time_total=(int)interval/60;
	sprintf(sql,"UPDATE t_user SET time_login=%lld,time_online=%d,time_total=time_total+%d,ac_days=%d WHERE user_id=%d;",
		time_login,time_online,time_total,ac_day,uid);
	exec(mysql,sql);
}

void Player::enter(){
}
// --------------------------------------------------------
void Players::add(size_t id,Player* r){
	if(!find(id)){
		_players.insert(std::make_pair(id,r));
	}
}

void Players::remove(size_t id){
	_players.erase(id);
}

void Players::update()
{	
	for(auto pp = _players.begin();pp!=_players.end() ; pp++)
		pp->second->update_Timer();
}

Player* Players::find(size_t id){
	auto i=_players.find(id);
	return i==_players.end()?nullptr:i->second;
}

