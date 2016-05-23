// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: DBResult.h
 *Desc		: 
 *Version	: 1.0
 *Program	: Vic
 *Date		: 2016-4-25
 */
// --------------------------------------------------------
#ifndef _DBResult_h_
#define _DBResult_h_
// --------------------------------------------------------
struct PANDA_API DBResult{
	enum Type:int{
		REPLY_NONE,
		REPLY_STRING,
		REPLY_ARRAY,
		REPLY_INTEGER,
		REPLY_NIL,
		REPLY_STATUS,
		REPLY_ERROR,
	};

	Type					type;
	size_t					value;
	std::string				str;
	std::vector<DBResult>	arr;
	DBResult():type(Type::REPLY_NONE),value(0){}
};
// --------------------------------------------------------
#endif // _DBResult_h_
