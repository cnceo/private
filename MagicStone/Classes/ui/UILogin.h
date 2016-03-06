// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: GameMan
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef __popworld__UILogin__
#define __popworld__UILogin__

#include "cocos2d.h"
#include "cocos-ext.h"

class UILogin: public cocos2d::Layer{
public:
					CREATE_FUNC(UILogin);
    static			cocos2d::TransitionScene*	scene(float);

    virtual bool    init();

	void			touchEvent(cocos2d::Ref *pSender,cocos2d::ui::Widget::TouchEventType type);
    void			textFieldEvent(cocos2d::Ref *pSender,cocos2d::ui::TextField::EventType type);

	CEventFunc(onLogin)
private:
	cocos2d::ui::TextField		*t_name,*t_pswd;
};
// --------------------------------------------------------
#endif /* defined(__popworld__UILogin__) */
