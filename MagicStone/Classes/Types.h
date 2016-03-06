// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: types
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _types_h_
#define _types_h_

enum GAME_ENUM:int{
	INIT_HAND_CARD	=5,
	
	//layers
	LAYER_TOP		=0,
	LAYER_UI,
	LAYER_GAME,
	LAYER_BG,
	LAYER_HIDE,

	//ui id
	UI_LOGIN,
	UI_GAME,
};

#if (COCOS2D_VERSION<0x00030000)
#	define _ALPHA_PRE_
#endif

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
// --------------------------------------------------------
#endif
