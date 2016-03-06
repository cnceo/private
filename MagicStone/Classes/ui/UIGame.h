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
#ifndef __popworld__UIGame__
#define __popworld__UIGame__

#include "cocos2d.h"
#include "cocos-ext.h"

class GameUnit;
class GamePlayer;
#ifdef _ALPHA_PRE_
	#define _TouchBegan ccTouchBegan
    #define _TouchMoved ccTouchMoved
    #define _TouchEnded ccTouchEnded   
#else
	#define _TouchBegan onTouchBegan
    #define _TouchMoved onTouchMoved
    #define _TouchEnded onTouchEnded   
#endif
// --------------------------------------------------------
class UIGame : public cocos2d::Layer{
public:
                    UIGame();
    static			cocos2d::TransitionScene*	scene(float);
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool    init();
 
	virtual bool	_TouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void	_TouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void	_TouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);    
	void			touchEvent(cocos2d::Ref *pSender,cocos2d::ui::Widget::TouchEventType type);

	void			shuffle (const std::vector<short>&,bool me=true);
    void            deal    (int count=1,bool me=true);
    void			play    (cocos2d::Node* =nullptr,bool me=true);
    void            select  (cocos2d::Node* =nullptr);  //if nullptr deselect all
    void			draw    (int count=1);
    void			discard ();
    void			reveal  (int count=1);
    void			resolve ();

    void			buttonCallback(cocos2d::Ref* pSender);

	CEventFunc(onDeal)
	CEventFunc(onPlay)
	// preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(UIGame);
private:
    void            onEnter() override;
    void            onEnterTransitionDidFinish() override;
    void            update(float) override;
    void			_setupBgTouch();
    void			_setupCardTouch(cocos2d::ui::Widget*);
	void			_hideLarge();
    void            _addCardToContainer(cocos2d::Node*,const std::vector<cocos2d::Node*>&,bool sort=false);
    void            _realignContainer(cocos2d::Node*,bool expand=false);

	cocos2d::Layer*			_uiLayer;
    cocos2d::ui::Widget     *_deck_me,*_deck_opp,*_hand_opp,*_hand_me,*_desk_me,*_desk_opp,
                            *_bench_me,*_bench_opp,*_reminder,
                            *_reveal,*_reveal_sv,*_reveal_pv,
                            *_menus;
    std::vector<cocos2d::Node*> _selection;
    cocos2d::ui::Button     *_btn_menu,*_btn_operation,*_btn_giveup,*_btn_exit;
    /*
	cocos2d::Node			*_cards,*_cards_hand,*_cards_desk_mine,*_cards_desk_his,
							*_text,
							*_selected,*_large;
	cocos2d::Size			_sz_hand,_sz_desk,_sz_chat;
	cocos2d::Point			_pos_hand,_pos_desk,_pos_chat;
     */
	GamePlayer*				_player;

    cocos2d::Point			_touchPoint;
    bool					_touched,_moved;
};
// --------------------------------------------------------
#endif /* defined(__popworld__GameScene__) */
