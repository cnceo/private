// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: fwd.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _common_fwd_h_
#define _common_fwd_h_

// instance macro
#ifndef INSTANCE_DECL
	#define INSTANCE_DECL(T) \
		public: \
			static T*		instance(); \
			static void		close_instance(); \
		private: \
			static T*		_instance;	// don't use shared_ptr
#endif //INSTANCE_DECL
#ifndef INSTANCE_IMP
	#define INSTANCE_IMP(T) \
		T* T::_instance=nullptr; \
		T* T::instance() \
		{ \
			if(nullptr==_instance) \
				_instance=new T; \
			return _instance; \
		} \
		void T::close_instance() \
		{ \
			if(nullptr!=_instance) \
				delete _instance; \
			_instance=nullptr; \
		};
#endif //INSTANCE_IMP

#include "common/protocol.h"
#include "common/packets.h"

#endif