// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: UIGame
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#include "AppFwd.h"
#include <math.h>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;
using namespace std;

/* comments
 card: ImageView;
 card id: tag of ImageView, set when shuffle; maybe attach
    Component contains card info to ImageView is better;
 card index in hand or desk: parent's(Node) index;
 card anchor: left,bottom(0,0);
 */
// --------------------------------------------------------
//enums
enum eGame{
	//both sides
	SIDE_ME,			//me
	SIDE_OP,			//opponent
	//card position
	/*≈∆µƒŒª÷√Œ™∂˛Œ¨:Œª÷√∫Õ’≈ ˝;∑≈»ÎNodeµƒTag¿Ô*/
	CARD_IN_HAND,
	CARD_IN_DESK,
	CARD_IN_DISCARD,
	CARD_IN_EXP,
	CARD_IN_EQUIP,
	CARD_IN_REVEAL,
};

//locate variables
//for cards
static int SELECT_Y=36;
static int EXPAND_SPACE=5;
static float TIME_ANIM_CARD=0.1f;
//static int CARD_ME_Y=0;
//for chat text
ImageView* UIUtils::bigCard=nullptr;
// --------------------------------------------------------
TransitionScene* UIGame::scene(float t){
    Scene *scene = Scene::create();
    auto layer = UIGame::create();
    scene->addChild(layer);

	return TransitionMoveInL::create(t,scene);
	/*
	TRANS(TransitionProgressHorizontal),	//ÀÆ∆Ω,¥π÷±æÌ¡±
    TRANS(TransitionProgressVertical),
    TRANS(PageTransitionForward),	//«∞∫Û∑≠“≥
    TRANS(PageTransitionBackward),
    TRANS(TransitionFade),		//µ≠≥ˆ
    TRANS(FadeWhiteTransition),
    TRANS(FlipXLeftOver),		//◊Û”“∑≠◊™
    TRANS(FlipXRightOver),
    TRANS(TransitionMoveInL),	//◊Û”““∆≥ˆ
    TRANS(TransitionMoveInR),
	*/
}

UIGame::UIGame()
:_player(nullptr)
,_touched(false)
,_moved(false)
,_uiLayer(nullptr)
/*
,_cards(nullptr)
,_cards_hand(nullptr)
,_cards_desk_mine(nullptr)
,_cards_desk_his(nullptr)
,_selected(nullptr)
,_large(nullptr)
,_text(nullptr)
*/
{
}

// on "init" you need to initialize your instance
bool UIGame::init(){
    // 1. super init first
    if (!Layer::init())
        return false;
	//custom events
	CEventSetup(UIGame,onDeal);
	CEventSetup(UIGame,onPlay);
    _setupBgTouch();
    auto size = Director::getInstance()->getWinSize();
    
    auto root = CSLoader::createNode("Main/Main.csb");
    addChild(root);
    
    std::pair<string,Widget**> vp[]={
        std::make_pair("deck_me",&_deck_me),
        std::make_pair("deck_opp",&_deck_opp),
        std::make_pair("hand_me",&_hand_me),
        std::make_pair("hand_opp",&_hand_opp),
        std::make_pair("desk_me",&_desk_me),
        std::make_pair("desk_opp",&_desk_opp),
        std::make_pair("bench_me",&_bench_me),
        std::make_pair("bench_opp",&_bench_opp),
        std::make_pair("reminder",&_reminder),
        std::make_pair("reveal",&_reveal),
        std::make_pair("reveal_sv",&_reveal_sv),
        std::make_pair("reveal_pv",&_reveal_pv),
        std::make_pair("menus",&_menus),
    };
    for(int i=0,ii=sizeof(vp)/sizeof(vp[0]);i<ii;++i)
        *vp[i].second=UIUtils::seekByName<Widget>(root,vp[i].first);
    
    std::pair<string,Button**> vb[]={
        std::make_pair("btn_menu",&_btn_menu),
        std::make_pair("btn_operation",&_btn_operation),
        std::make_pair("btn_giveup",&_btn_giveup),
        std::make_pair("btn_exit",&_btn_exit),
    };
    for(int i=0,ii=sizeof(vb)/sizeof(vb[0]);i<ii;++i){
        *vb[i].second=UIUtils::seekByName<Button>(root,vb[i].first);
        (*vb[i].second)->addClickEventListener(CC_CALLBACK_1(UIGame::buttonCallback,this));
    }
    
    _hand_me->removeAllChildren();
    _hand_opp->removeAllChildren();
    
    std::vector<short> cards(MAX_CARD);
    for(int i=0;i<MAX_CARD;++i)
        cards[i]=CARD_ID_BEGIN+(short)i;
    shuffle(cards);
    return true;
}

void UIGame::shuffle(const std::vector<short>& cards,bool me){
    auto deck=(me?_deck_me:_deck_opp);
    deck->removeAllChildren();
    
    Point anchor(0.f,0.f);
    char str[32];
    ImageView* card=nullptr;
    for(auto iter=cards.begin(),iend=cards.end();iter!=iend;++iter){
        auto cid=*iter;
        UIUtils::getCardName(str,cid);
        card=ImageView::create();
        card->loadTexture(str);
        card->setContentSize(Size(CARD_W,CARD_H));
        card->setTag(cid);
        card->setAnchorPoint(anchor);
        deck->addChild(card);
    }
}

void UIGame::deal(int count,bool me){
    auto deck=(me?_deck_me:_deck_opp);
    if(deck->getChildrenCount()<count)return;
    
    auto hand=(me?_hand_me:_hand_opp);
    for(int i=0;i<count;++i){
        auto& children=deck->getChildren();
        auto card=(Widget*)children.front();
        UIUtils::reParent(card,hand);
        _setupCardTouch(card);
    }
    _realignContainer(hand);
}

void UIGame::select(cocos2d::Node* card){
    auto y=card->getPositionY();
    for(auto iter=_selection.begin(),iend=_selection.end();iter!=iend;++iter){
        if(card==*iter){
            //deselect
            card->setPositionY(y-SELECT_Y);
            _selection.erase(iter);
            return;
        }
    }
    card->setPositionY(y+SELECT_Y);
    _selection.push_back(card);
    
    //test
    //scheduleOnce(CC_SCHEDULE_SELECTOR(UIGame::update),1.f);
}

void UIGame::play(Node* card,bool me){
    if(card!=nullptr){
        vector<Node*> cards;
        cards.push_back(card);
        if(me){
            _addCardToContainer(_desk_me,cards);
            _realignContainer(_hand_me);
            _selection.clear();
            
            struct NPAK_CS_PLAY_CARD pk;
            pk.signal=CS_PLAY_CARD;
            pk.cardPos=0;
            pk.action_id=0;
            pk.ifChangeCard=0;
            SceneMan::instance()->send(pk);
        }else{
            _addCardToContainer(_desk_opp,cards);
            _realignContainer(_hand_opp);
        }
    }
}

void UIGame::draw(int count){
    deal(count);
}

void UIGame::discard(){
    int i=0,count=(int)_selection.size();
    auto parent=_bench_me;
    for(auto&& card:_selection){
        UIUtils::reParent(card,parent);
        auto delay=DelayTime::create((count-1-i++)*TIME_ANIM_CARD*0.9f);
        auto action=Sequence::createWithTwoActions(delay,MoveTo::create(TIME_ANIM_CARD,Vec2()));
        card->runAction(action);
        action=Sequence::createWithTwoActions(delay,ScaleTo::create(TIME_ANIM_CARD,0.f));
        card->runAction(action);
    }
    _selection.clear();
}

void UIGame::reveal(int count){
    int num=(int)_deck_me->getChildrenCount();
    if(count==-1||count>num)count=num;
    
    _reveal->setVisible(true);
    _reveal_pv->setVisible(false);
    auto sz=Size((count-1)*(CARD_W+EXPAND_SPACE)+CARD_W,_reveal_pv->getContentSize().height);
    static_cast<cocos2d::ui::ScrollView*>(_reveal_sv)->setInnerContainerSize(sz);
    for(int i=0;i<count;++i)
        UIUtils::reParent((Widget*)_deck_me->getChildren().front(),_reveal_sv);
    _realignContainer(_reveal_sv,true);
}

void UIGame::resolve(){
}

void UIGame::_addCardToContainer(Node* parent,const vector<Node*>& cards,bool sort){
    //attach
    for(auto &&card:cards)
        UIUtils::reParent(card,parent);
    
    //realign
    _realignContainer(parent);
}

void UIGame::_realignContainer(Node* parent,bool expand){
    int count=(int)parent->getChildrenCount();
    int width=parent->getContentSize().width;
    float startx=0.f,dx=0.f;
    float starty=0.f;
    if(width>count*CARD_W){
        startx=(width-count*CARD_W)/(count+1);
        dx=startx+CARD_W;
    }else if(expand){
        dx=CARD_W+EXPAND_SPACE;
    }else //overlapped
        dx=(count==1?0:(width-CARD_W)/(count-1));
    for(int i=0;i<count;++i){
        auto& children=parent->getChildren();
        auto card=children.at(i);
        auto action=Sequence::createWithTwoActions(DelayTime::create((count-1-i)*TIME_ANIM_CARD*0.9f),
                                                   MoveTo::create(TIME_ANIM_CARD,Vec2(startx+i*dx,starty)));
        card->runAction(action);
    }
}

void UIGame::update(float t){
    //Layer::update(t);
    //test
    //discard();
}

void UIGame::onEnter(){
    Layer::onEnter();
}

void UIGame::onEnterTransitionDidFinish(){
    Layer::onEnterTransitionDidFinish();
    //scheduleUpdate();
}

void UIGame::_hideLarge(){
    /*
	if(_large){
		_large->removeFromParent();
		_large=nullptr;
	}
     */
}

void UIGame::_setupBgTouch(){
    //event on bg
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    //listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(UIGame::_TouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(UIGame::_TouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(UIGame::_TouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener,this);  //node
}

void UIGame::_setupCardTouch(cocos2d::ui::Widget* widget){
    // Register Touch Event
    widget->setTouchEnabled(true);
    widget->addTouchEventListener(CC_CALLBACK_2(UIGame::touchEvent,this));
}

void UIGame::touchEvent(Ref *pSender, Widget::TouchEventType type){
	//auto chat=dynamic_cast<Text*>(_text);
	char dbg[256];
	switch (type){
        case Widget::TouchEventType::BEGAN:
        {
            if(auto card=dynamic_cast<Widget*>(pSender)){
                _touchPoint=card->getPosition();
                //_selected=card;
                sprintf(dbg,"Touch begin %d",card->getTag());
                //if(chat)chat->setString(dbg);
            }
            break;
        }
        case Widget::TouchEventType::MOVED:
        {
            _moved=true;
            if(auto card=dynamic_cast<Widget*>(pSender)){
                auto& p0=card->getTouchBeganPosition();
                auto& p1=card->getTouchMovePosition();
                card->setPosition(p1-(p0-_touchPoint));
                sprintf(dbg,"Touch moved %d",card->getTag());
                //if(chat)chat->setString(dbg);
            }
            break;
        }
        case Widget::TouchEventType::ENDED:
        {
            if(auto card=dynamic_cast<Widget*>(pSender)){
                sprintf(dbg,"Touch end %d",card->getTag());
                //if(chat)chat->setString(dbg);
                if(_moved){
                    //move
                    auto& p0=card->getTouchBeganPosition();
                    auto& p1=card->getTouchMovePosition();
                    if(p1.y-p0.y>SELECT_Y){
                        //play
                        /*∑¢œ˚œ¢µΩGameLogic,∑˛ŒÒ∆˜∑µªÿ∫Û»Áπ˚ ß∞‹‘Ú‘Ÿ¥”◊¿…œ∑≈ªÿ;
                         ui∫Õlogic”¶ÕÍ»´∏Ùø™,ΩˆÕ®π˝œ˚œ¢¡¨Ω”*/
                        play(card);
                        //card->setPositionY(CARD_ME_Y);
                    }else//cancel
                        card->setPosition(_touchPoint);
                }else{
                    //selection
                    select(card);
                    //zoom
                    /*
                    auto size=Director::getInstance()->getWinSize();
                    _hideLarge();
                    _large=card->clone();
                    float sy=size.height/(CARD_H/_large->getScaleY());
                    if(sy>1.f)sy=1.f;
                    _large->setPositionX(size.width/2.f);
                    _large->setPositionY(size.height/2.f);
                    _large->setScale(sy);
                    _cards->addChild(_large);
                    */
                }
            }
            _moved=false;
            break;
        }
        default:
            break;
    }
}

bool UIGame::_TouchBegan(Touch* touch, Event* event){
	_hideLarge();
	_moved=false;
    return true;
}

void UIGame::_TouchMoved(Touch* touch, Event* event){
	_moved=true;
	static float delta=1.05f;
    if(false&&_touched){
		//record direction
        Director* director=Director::getInstance();
        Point pos=touch->getLocationInView();
        pos=director->convertToGL(pos);
        Point dir=pos-_touchPoint;
		if(_player){
            dir.normalize();
            _player->direction=dir;
			_player->speed*=delta;
		}
		//move card
		//if(_selected)
		//	_selected->setPosition(pos);
    }
}

void UIGame::_TouchEnded(Touch* touch, Event* event){
	//let's fire
	if(false&&&_player&&!_moved){
		//the fire direction
		Director* director=Director::getInstance();
		const Point& pt=_player->getPosition();
		Point dir=touch->getLocationInView();
		dir=director->convertToGL(dir);
        dir-=pt;
        dir.normalize();
	}
}

void UIGame::buttonCallback(cocos2d::Ref* pSender){
    if(pSender==_btn_menu)
        _menus->setVisible(!_menus->isVisible());
    else if(pSender==_btn_giveup)
        SceneMan::instance()->transition(UI_LOGIN);
    else if(pSender==_btn_operation)
        reveal(10);
    else if(pSender==_btn_exit){
        Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }
}

void UIGame::onDeal(cocos2d::EventCustom*){
    auto& gameInfo=GameLogic::instance()->gameInfo();
    if(gameInfo.sCurrentTurnPlayer>=0){
        //shuffle if online
        auto myseat=GameLogic::instance()->mySeat();
        if(!SceneMan::instance()->standalone()){
            for(short i=0;i<MAX_PLAYER;++i){
                std::vector<short> v;
                auto hands=gameInfo.m_PlayerData[i].HandCards;
                for(int j=0,jj=20;j<jj;++j)
                    if(hands[j])v.push_back(hands[j]);
                shuffle(v,i==myseat);
            }
        }
        
        deal(INIT_HAND_CARD);
        deal(INIT_HAND_CARD,false);
        /*
         //	if(_cards_hand->getChildrenCount()>0)return;
         auto& pd=gameInfo.m_PlayerData[myseat];
         std::vector<short> cards;
         for(int i=0;i<INIT_HAND_CARD;++i){
         auto cid=pd.HandCards[i];
         if(cid>0)cards.push_back(cid);
         }
         deal(INIT_HAND_CARD);
         */
    }
}

void UIGame::onPlay(cocos2d::EventCustom* e){
    if(e){
        auto& pk=*(NPAK_SC_PLAY_CARD*)e->getUserData();
        if(pk.nError==0&&pk.nSeatIndex!=GameLogic::instance()->mySeat()){
            //opponent play
            auto& children=_hand_opp->getChildren();
            if(pk.cardPos<children.size()){
                auto card=children.at(pk.cardPos);
                play(card,false);
            }
        }
    }
}
