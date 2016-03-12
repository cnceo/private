// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: behavior.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-10-30
 */
// --------------------------------------------------------
#ifndef _behavior_h_
#define _behavior_h_

namespace keye{
class bh_precondition;
class bh_signal;
// --------------------------------------------------------
// behavior
// --------------------------------------------------------
class KEYE_API behavior{
public:
	virtual			~behavior(){}
	//install precond
	void			set_precond(s_ptr<bh_precondition>);
protected:
	//drive owner real action
	virtual void	_action()=0;
	//shared precond,signal
	s_ptr<bh_precondition>	_precond;
private:
	friend class bh_signal;
	//trigger by signal
	void			operator()();
};
// --------------------------------------------------------
// behavior signal,precondition
// --------------------------------------------------------
class KEYE_API bh_signal{
public:
					bh_signal(s_ptr<behavior>* =nullptr,bool=true);
	void			install(s_ptr<behavior>);
	void			uninstall(s_ptr<behavior>);
	//signal
	void			operator()();
private:
	std::list<s_ptr<behavior>>	_bhs;
};

class KEYE_API bh_precondition{
public:
	virtual			~bh_precondition(){}
	virtual	bool	operator()()=0;
};
// --------------------------------------------------------
// Behavior,the schedulalbe behavior
// --------------------------------------------------------
template<typename _Sx=joint_scheduler>
class Behavior:public behavior,private joint_observer{
public:
					Behavior(_Sx& sx):_sx(sx){
						root.reset(joint::create(0xfff));
						root->link(this);
					}
	virtual			~Behavior(){}
	s_ptr<joint>	root;
private:
	//trigger self and children
	virtual void	_action(){if(root)root->update(_sx);}
	//the scheduler
	_Sx&			_sx;
};
// --------------------------------------------------------
};
#endif