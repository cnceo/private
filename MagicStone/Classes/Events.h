// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: events
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _events_h_
#define _events_h_
// --------------------------------------------------------
// events in game
// --------------------------------------------------------
//variable
#define CEventDef(E) \
	const static char* e_##E=#E;
//decl function
#define CEventFunc(F) \
	void F(cocos2d::EventCustom*);
//create listener
#define CEventListener(C,E) \
	EventListenerCustom::create(e_##E,std::bind(&C::E,this,std::placeholders::_1));
//setup listener
#define CEventSetup(C,E) \
	{ \
		auto listener = EventListenerCustom::create(e_##E,std::bind(&C::E,this,std::placeholders::_1)); \
		auto dispatcher = Director::getInstance()->getEventDispatcher(); \
		dispatcher->addEventListenerWithFixedPriority(listener,1); \
	}
//dispath
#define CEventDispatch(E,P) \
	{ \
		auto dispatcher = Director::getInstance()->getEventDispatcher(); \
		dispatcher->dispatchCustomEvent(e_##E,P); \
	}
// --------------------------------------------------------
//all events
CEventDef(onConnectErr)
CEventDef(onConnectClose)

CEventDef(doLogin)
CEventDef(onLogin)

CEventDef(onDeal)
CEventDef(onPlay)
// --------------------------------------------------------
#endif
