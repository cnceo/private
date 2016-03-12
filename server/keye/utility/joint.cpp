// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: grid.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-10-30
 */
// --------------------------------------------------------
#include "stdafx.h"
#include <assert.h>
#include <keye/utility/utility_fwd.h>

using namespace keye;
// --------------------------------------------------------
joint::joint(size_t id):_id(id),_update_count(0),_observer(nullptr){}

joint::~joint(){
	_remove();
}

joint* joint::create(size_t id){
	//refuse 0 as id
	assert(id);
	return new joint(id);
}

size_t joint::id()const{
	return _id;
}

void joint::link(joint_observer* o){
	_observer=o;
}

bool joint::insert(joint* nd){
	if(!nd||nd->is_child_of(this)||is_child_of(nd))
		return false;

	_children.push_back(nd);
	//child
	nd->_parents.push_back(this);
	++nd->_update_count;
	return true;
}

void joint::remove(){
	_remove();
	//delete self
	delete this;
}

bool joint::is_child_of(joint* nd)const{
	if(nd)for(auto i=_children.begin(),ii=_children.end();i!=ii;++i)
		if(nd==*i)return true;
	return false;
}

bool joint::is_tip()const{
	return _children.empty();
}

size_t joint::width()const{
	size_t x=is_tip()?1:0;
	//recursive children
	for(auto i=_children.begin();i!=_children.end();++i)
		x+=(*i)->width();
	return x;
}

size_t joint::depth()const{
	size_t x=0;
	//recursive children
	for(auto i=_children.begin();i!=_children.end();++i){
		auto xch=(*i)->depth();
		if(xch>x)x=xch;
	}
	return ++x;
}

size_t joint::check_loop()const{
	const joint *slow=this,*fast;
	std::list<const joint*> q;
	for(auto i=_children.begin(),ii=_children.end();i!=ii;++i){
		fast=*i;
		q.clear();
		q.push_back(fast);
		//start loop check
		if(auto looped=_check_loop(slow,fast,q))
			return looped;
	}
	return 0;
}

/* check loop:
	using 2 ptr to check the list loop,move foward the slow 1 step once
	and the fast 2,if the fast reach the slow then the list is looped;
	tree has more branches,we trace the fast path by queue,and pass to the slow,
	so that all branches will be checked. */
size_t joint::_check_loop(const joint* slow,const joint* fast,std::list<const joint*>& q)const{
	if(slow&&fast){
//		printf("step: %03x - %03x\n",slow->id(),fast->id());
		//check 0: slow & fast
		if(slow==fast){
			printf("%03x looped\n",slow->id());
			return slow->id();
		}
		//end for leaf
		if(fast->is_tip())return 0;
		//check 1: slow & fast_child
		auto& ff=fast->_children;
		for(auto j=ff.begin(),jj=ff.end();j!=jj;++j){
			auto fast_child=*j;
			if(slow==fast_child){
				printf("%03x looped\n",slow->id());
				return slow->id();
			}
		}

		//step forward
		if(!q.empty()){
			//step 1 for slow,from the queue
			slow=q.front();
			q.pop_front();
			//multi-path
			for(auto j=ff.begin(),jj=ff.end();j!=jj;++j){
				auto fast_child=*j;
				//push a joint
				q.push_back(fast_child);
				//multi-path
				for(auto k=fast_child->_children.begin(),kk=fast_child->_children.end();k!=kk;++k){
					//step 2 for fast
					fast=*k;
					//make a queue copy,for recursive
					auto p=q;
					p.push_back(fast);
					if(auto looped=_check_loop(slow,fast,p))
						return looped;
				}
				//pop a joint
				q.pop_back();
			}
		}
	}
	return 0;
}

bool joint::_update_self(){
	{
		//needed lock here only
		--_update_count;
	}
	if(0==_update_count||-1==_update_count){
		//update self
		if(_observer)_observer->update(this);
		//reset count
		_update_count=_parents.size();
		return true;
	}else
		return false;
}

void joint::_remove(){
	//remove children
	while(!_children.empty()){
		auto n=_children.front();
		//it will clean my _children
		n->remove();
	}
	//remove from parent
	for(auto i=_parents.begin(),ii=_parents.end();i!=ii;++i){
		auto& pv=(*i)->_children;
		for(auto pi=pv.begin(),pii=pv.end();pi!=pii;++pi)
			if(this==*pi){
				pv.erase(pi);
				break;
			}
	}
	_parents.clear();
}

void joint::print()const{
	if(check_loop())return;

	size_t w=width(),
		d=depth();
	printf("width=%d,depth=%d\n",w,d);
	printf("**");
	_print_node(this,d);
	printf("\n");
}

void joint::_print_node(const joint* n,size_t depth)const{
	if(n){
		auto dthis=n->depth();
		auto tabs=depth-dthis+1;
		//self
		printf("%03x",n->id());
		//recursive children
		auto& ch=n->_children;
		if(!ch.empty()){
			printf("__");
			for(auto i=ch.begin();i!=ch.end();++i){
				if(i!=ch.begin()){
					for(size_t j=0;j<tabs;++j)printf("    |");
					printf("\n");
					for(size_t j=0;j<tabs;++j)printf("    |");
					printf("__");
				}
				_print_node(*i,depth);
			}
		}else
			printf("\n");
	}
}
