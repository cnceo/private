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
#include "AppFwd.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;
// --------------------------------------------------------
TransitionScene* UILogin::scene(float t){
    Scene *scene = Scene::create();
    auto layer = UILogin::create();
    scene->addChild(layer);

	return TransitionMoveInL::create(t,scene);
}

TextField* patchTextField(Widget* parent,const char* name){
	TextField* textField=nullptr;
	if(auto src=static_cast<TextField*>(parent->getChildByName(name))){
		// Create the textfield
		textField = TextField::create();
		textField->setName(src->getName());
		textField->setTag(src->getTag());
		textField->setTouchEnabled(true);
		textField->setPlaceHolder("input");
		textField->setPasswordEnabled(src->isPasswordEnabled());
		textField->setPosition(src->getPosition());
		textField->setContentSize(src->getContentSize());

		parent->removeChild(src);
		parent->addChild(textField);
	}
	return textField;
}

bool UILogin::init(){
    // 1. super init first
    if ( !Layer::init())
        return false;

	auto size = Director::getInstance()->getWinSize();

	Layer* uiLayer=Layer::create();
	addChild(uiLayer);//,UILAYER,UILAYER);

    auto widget = CSLoader::createNode("Login/Login.csb");
    uiLayer->addChild(widget);

	//controls
    t_name = UIUtils::seekByName<TextField>(widget,"txt_name");
    t_pswd = UIUtils::seekByName<TextField>(widget,"txt_pswd");
	t_name->setPlaceHolder("name");
	t_pswd->setPlaceHolder("password");
	t_name->setTouchEnabled(true);
	t_pswd->setTouchEnabled(true);
	t_name->setMaxLength(8);
	t_pswd->setMaxLength(8);
	t_name->setMaxLengthEnabled(true);
	t_pswd->setMaxLengthEnabled(true);
    t_name->addEventListener(CC_CALLBACK_2(UILogin::textFieldEvent, this));
    t_pswd->addEventListener(CC_CALLBACK_2(UILogin::textFieldEvent, this));

	Button* button = UIUtils::seekByName<Button>(widget,"btn_ok");
	button->setTouchEnabled(true);
    button->addTouchEventListener(CC_CALLBACK_2(UILogin::touchEvent, this));
	//button->addTouchEventListener(this, toucheventselector(UILogin::touchEvent));
	
	scheduleUpdateWithPriority(0);

	//custom events
	CEventSetup(UILogin,onLogin);
	return true;
}

void UILogin::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
    case Widget::TouchEventType::ENDED:
	{
		auto& name=t_name->getString();
		//auto& pswd=t_pswd->getString();
		//char strname[32];
		
		CEventDispatch(doLogin,(void*)name.c_str())
		break;
	}
	default:
		break;
	}
}

void UILogin::textFieldEvent(Ref *pSender, TextField::EventType type)
{
    switch (type)
    {
        case TextField::EventType::ATTACH_WITH_IME:
        {
            //TextField* textField = dynamic_cast<TextField*>(pSender);
            Size screenSize = CCDirector::getInstance()->getWinSize();
//            textField->runAction(CCMoveTo::create(0.225f,Point(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2.0f)));
        }
            break;
        case TextField::EventType::DETACH_WITH_IME:
        {
            //TextField* textField = dynamic_cast<TextField*>(pSender);
            Size screenSize = CCDirector::getInstance()->getWinSize();
//            textField->runAction(CCMoveTo::create(0.175f, Point(screenSize.width / 2.0f, screenSize.height / 2.0f)));
        }
            break;
        case TextField::EventType::INSERT_TEXT:
//            _displayValueLabel->setText(String::createWithFormat("insert words")->getCString());
            break;
        case TextField::EventType::DELETE_BACKWARD:
//            _displayValueLabel->setText(String::createWithFormat("delete word")->getCString());
            break;
        default:
            break;
    }
}

void UILogin::onLogin(cocos2d::EventCustom* e){
	auto user=(user_t*)e->getUserData();
	SceneMan::instance()->createUser(user);
	SceneMan::instance()->transition(UI_GAME);
/*
	//top ranks
	const int TOP_RANKS=10;
	user_base_t ranks[TOP_RANKS];
*/
}
