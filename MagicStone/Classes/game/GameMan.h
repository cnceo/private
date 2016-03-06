//
//  GameMan.h
//  popworld
//
//  Created by Leo Keye on 13-8-8.
//
//

#ifndef __popworld__GameMan__
#define __popworld__GameMan__
/*
class GameManImpl;
namespace cocos2d{
	class Scene;
};
class GameMan{
public:
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::Scene*    scene();
private:
	static std::shared_ptr<GameManImpl>	_impl;
};
*/

class SceneMan{
public:
	typedef			std::function<cocos2d::TransitionScene*(float)> SceneFunc;
					SceneMan();
					~SceneMan();
	//the first scene
	cocos2d::Scene*	init();
	//registry scenes
	void			registry(int,SceneFunc);
	//do transition
	bool			transition(int);
	//network
	void			standalone(bool);		//standalone or online
	bool			standalone()const;
	bool			connect(const char*);	//http://ip:port
	void			send(void*,int);		//send raw data
	template<typename T>
	void			send(T& t){send(&t,sizeof(t));}

	void			createUser(user_t*);
	user_t&			userInfo();

	CEventFunc(onConnectErr)
	CEventFunc(onConnectClose)
	CEventFunc(doLogin)
private:
	std::map<int,std::pair<SceneFunc,cocos2d::TransitionScene*>>	_scenes;
	WebSocket_t*			_socket;
	std::shared_ptr<WebSocketDelegate>	_socketDelegate;
	bool					_standalone;

	std::shared_ptr<user_t>	_user;

	INSTANCE_DECL(SceneMan)
};

#endif /* defined(__popworld__GameMan__) */
