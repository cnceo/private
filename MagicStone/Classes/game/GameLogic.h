// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: GameLogic
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _GameLogic_h_
#define _GameLogic_h_

typedef userData			user_t;
typedef NPAK_SC_TABLE_DATA	game_t;

class GameLogic{
public:
						GameLogic();
						~GameLogic();
	game_t&				gameInfo();
	short				mySeat()const;

	void				onUpdate(game_t&);
	void				onPlayCard(NPAK_SC_PLAY_CARD&);
	CEventFunc(doLogin)
private:
	std::shared_ptr<game_t>	_game;
	short					_mySeat;

	INSTANCE_DECL(GameLogic)
};

#endif
