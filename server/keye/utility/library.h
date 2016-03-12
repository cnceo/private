// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: library.ch
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-09-09
 */
// --------------------------------------------------------
#ifndef _library_h_
#define _library_h_

namespace keye{
class library_impl;
class KEYE_API Library{
public:
						Library();
	//load plugin and install
	bool				load(const char*);
	//uninstall and unload plugin
	void				unload(const char*);
	//get/set value by key from plugins
	void				set(const char*,void*);
	void*				get(const char*);
protected:
	s_ptr<library_impl>	_impl;
};
};//namespace keye
#endif

