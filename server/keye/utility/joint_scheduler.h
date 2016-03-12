// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: joint_scheduler.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-10-30
 */
// --------------------------------------------------------
#ifndef _joint_scheduler_h_
#define _joint_scheduler_h_

namespace keye{
// --------------------------------------------------------
//joint_scheduler
// --------------------------------------------------------
class KEYE_API joint_scheduler{
public:
				joint_scheduler(){
					_root.reset(joint::create(0xfff));
				}
	joint&		root(){return *_root.get();}
	void		start_update(){
					root().print();
					root().update(*this);
				}
	void		stop_update(){
				}
	//schedule visit joint
	void		schedule(joint* n){n->update(*this);}
private:
	//only for composition
	s_ptr<joint>	_root;
};
// --------------------------------------------------------
};
#endif