// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: joint.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-10-30
 */
// --------------------------------------------------------
#ifndef _joint_h_
#define _joint_h_

namespace keye{
class joint_observer;
// --------------------------------------------------------
/* joint: an unlooped direction graphic,with a joint_observer attached.
		check_loop before traverse or remove to avoid dead loop */
// --------------------------------------------------------
class KEYE_API joint{
public:
	static joint*	create(size_t);			//create joint with id,0 is void
					~joint();
	size_t			id()const;
	void			link(joint_observer*);	//attach an observer
	bool			insert(joint*);			//attach a child
	void			remove();				//remove self and children
	/* check if children contain me,the return id is in loop
		but may not be the start joint of loop */
	size_t			check_loop()const;
	bool			is_child_of(joint*)const;
	bool			is_tip()const;
	size_t			width()const;			//width and depth of joint(tree)
	size_t			depth()const;
	/* traversing with scheduler,it is async! so do not insert,
		remove or link on nodes while updating */
	template<class _Sx>
	void			update(_Sx& sx){
						if(_update_self())
							for(auto i=_children.begin(),ii=_children.end();i!=ii;++i)
								sx.schedule(*i);//(*i)->update();
					}
	void			print()const;			//print tree,test only
private:
					joint(size_t);			//ctor with id
	void			_remove();				//remove children
	bool			_update_self();			//self only
	size_t			_check_loop(const joint*,const joint*,std::list<const joint*>&)const;
	void			_print_node(const joint*,size_t)const;

	size_t				_id,_update_count;
	std::list<joint*>	_parents,_children;
	joint_observer*		_observer;
};
// --------------------------------------------------------
// joint_observer
// --------------------------------------------------------
class KEYE_API joint_observer{
public:
					~joint_observer(){}
	virtual void	update(joint*)=0;
};
// --------------------------------------------------------
};
#endif