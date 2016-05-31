// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: ClientSession.h
 *Desc		: 
 *Version	: 1.0
 *Program	: Vic
 *Date		: 2016-4-25
 */
// --------------------------------------------------------
#ifndef _ClientSession_h_
#define _ClientSession_h_
// --------------------------------------------------------
class PANDA_API ClientSession:public BaseSession{
public:
	proto3::PlayerInfo	player;
};
// --------------------------------------------------------
#endif // _ClientSession_h_
