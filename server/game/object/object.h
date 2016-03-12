// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: object.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _object_h_
#define _object_h_
// --------------------------------------------------------
/* Object----Creature-----Player
			|			|--Pet
			|			|--NPC
			|			|--Monster-----Boss
			|-Item
	*/
// --------------------------------------------------------
// ObjectMap
// --------------------------------------------------------
class Object{
public:
	enum _t:unsigned char{
		CREATURE	=0x40,
		ITEM		=0x80,
		PLAYER		=CREATURE,
		PET			=CREATURE+1,
		NPC			=CREATURE+2,
		MONSTER		=CREATURE+3,
		BOSS		=CREATURE+4,
		UNKNOWN		=(unsigned char)~0
	};
	_t				type()const	{return _type;}
	size_t			sid()const	{return _sid;}
protected:
	_t				_type;
					Object():_type(UNKNOWN),_sid(~0){}
	virtual			~Object(){}
private:
	friend class	ObjectMap;

	size_t			_sid;
};

class Creature:public Object{
	friend class	ObjectMap;
protected:
					Creature(){_type=CREATURE;}
	virtual			~Creature(){}
};

#endif