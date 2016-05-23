// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: PandaService.h
 *Desc		: 
 *Version	: 1.0
 *Program	: Vic
 *Date		: 2016-4-25
 */
// --------------------------------------------------------
#ifndef _PandaService_h_
#define _PandaService_h_
// --------------------------------------------------------
// PandaService
// --------------------------------------------------------
class BaseSession;
template<typename SessionType=BaseSession,typename Handler=void>
class PandaService:public keye::service{
public:
	virtual void	on_open(keye::svc_handler& sh){
		auto session=pool.create();
		_sessions.insert(std::make_pair(sh.id(),session));
		session->on_open(sh);
		handler.on_open(sh);
	}
	virtual void	on_close(keye::svc_handler& sh){
		handler.on_close(sh);
		auto iter=_sessions.find(sh.id());
		if(iter!=_sessions.end()){
			pool.destroy(iter->second);
			_sessions.erase(iter);
		}
	}
	virtual void	on_read(keye::svc_handler& sh,void* buf,size_t sz){
		keye::PacketWrapper pw(buf,sz);
		unpacker<<pw;
		//split raw data
		while(true){
			unpacker>>pw;
			if(pw.length>0)
				//handle real splitted message
				handler.on_message(sh,pw);
			else break;
		}
	}

	virtual bool	on_timer(keye::svc_handler& sh,size_t id,size_t milliseconds){
		return handler.on_timer(sh,id,milliseconds);
	}

	SessionType*	find(size_t id){
		auto i=_sessions.find(id);
		return i==_sessions.end()?nullptr:i->second;
	}

	Handler			handler;
	std::map<size_t,SessionType*> _sessions;
protected:
	keye::HeadUnpacker	unpacker;
	ObjectPool<SessionType>	pool;
};
// --------------------------------------------------------
// BaseHandler
// --------------------------------------------------------
class PANDA_API BaseHandler{
public:
				BaseHandler():bLogin(false),keepAlive(true){}
	virtual 	~BaseHandler(){}

	virtual void on_open(keye::svc_handler& sh){
		shClient=sh();
		login();
	}

	virtual void on_close(keye::svc_handler& sh){
		if(keepAlive||!shClient)
			//connect error or connection lost
			connect();
		else if(shClient){
			shClient.reset();
		}
	}

	virtual void on_message(keye::svc_handler&,keye::PacketWrapper&)=0;
	virtual bool on_timer(keye::svc_handler& sh,size_t id,size_t milliseconds){ return true; }

	virtual void connect(){}
	virtual void login(){}

	bool bLogin,keepAlive;
	std::shared_ptr<keye::svc_handler>	shClient;
};
// --------------------------------------------------------
// PBHelper: protobuf helper
// --------------------------------------------------------
class PBHelper{
public:
	static const size_t send_buffer_size=2048;
	PBHelper(keye::PacketWrapper& pw):_pw(pw){}

	bool Parse(google::protobuf::MessageLite& msg){
		return msg.ParseFromArray(_pw.data,(int)_pw.length);
	}

	eMsg Id(){
		proto3::MsgBase mt;
		mt.ParseFromArray(_pw.data,4);
		return (eMsg)mt.mid();
	}

	static void Send(keye::svc_handler& sh,google::protobuf::MessageLite& msg){
		auto bytes=msg.ByteSize();
		assert(bytes<send_buffer_size);		//large message
		char buffer[send_buffer_size];
		if(msg.SerializeToArray(buffer,bytes)){
			proto3::MsgBase mr;
			if(mr.ParseFromArray(buffer,bytes)){
				assert(mr.mid()<=0);

				keye::HeadPacker packer;
				keye::PacketWrapper pw(buffer,bytes);
				packer<<pw;
				packer>>pw;
				sh.send(pw.data,pw.length);
				return;
			}
		}
		assert(false);
	}
	//make compiler happy
	void	on_message(keye::svc_handler&,keye::PacketWrapper&){}
private:
	keye::PacketWrapper& _pw;
};
// --------------------------------------------------------
#endif // _PandaService_h_
