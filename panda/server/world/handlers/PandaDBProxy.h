// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: PandaDBProxy.h
 *Desc		: 
 *Version	: 1.0
 *Program	: Vic
 *Date		: 2016-4-25
 */
// --------------------------------------------------------
#ifndef _PandaDBProxy_h_
#define _PandaDBProxy_h_

enum eQid{
	CREATE_ACCOUNT=100,
	GET_ACCOUNT,
};
// --------------------------------------------------------
class PandaDBProxy:public IDBHandler{
public:
	virtual void	handle(int qid,DBResult* res=nullptr,void* privdata=nullptr);
private:
};

// --------------------------------------------------------
#endif // _PandaDBProxy_h_
