// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: behavior.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-10-30
 */
// --------------------------------------------------------
#include "stdafx.h"
#include <keye/utility/utility_fwd.h>

using namespace keye;
// --------------------------------------------------------
bh_signal::bh_signal(s_ptr<behavior>* b,bool act){
	install(*b);
	if(act)(*this)();
}

void bh_signal::operator()(){
	for(auto i=_bhs.begin(),ii=_bhs.end();i!=ii;++i)(**i)();
}

void bh_signal::install(s_ptr<behavior> b){
	_bhs.push_back(b);
}

void bh_signal::uninstall(s_ptr<behavior> b){
	for(auto i=_bhs.begin(),ii=_bhs.end();i!=ii;++i){
		if(b==*i){
			_bhs.erase(i);
			break;
		}
	}
}
// --------------------------------------------------------
void behavior::operator()(){
	if(!_precond||(*_precond)())
		_action();
}

void behavior::set_precond(s_ptr<bh_precondition> p){
	_precond=p;
}
