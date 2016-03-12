// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: library.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-09-09
 */
// --------------------------------------------------------
#include "stdafx.h"
#include <keye/utility/utility_fwd.h>

#if(defined(_WIN32)||defined(_WIN64))
#define LOAD_LIB(f)			LoadLibraryExA(f,nullptr,LOAD_WITH_ALTERED_SEARCH_PATH)
#define FREE_LIB(f)			FreeLibrary((HMODULE)f)
#define GET_PROC(h,name)	GetProcAddress((HMODULE)h,name)
#else
#include <dlfcn.h>
#define LOAD_LIB(f)			dlopen(f,RTLD_NOW)
#define FREE_LIB(f)			dlclose(f)
#define GET_PROC(h,name)	dlsym(h,name)
#endif

using namespace std;
using namespace keye;
// --------------------------------------------------------
class keye::library_impl{
public:
			library_impl(Library*);
			~library_impl();
	//load plugin and install
	bool	load(const char*);
	//uninstall and unload plugin
	void	unload(const char*);
	//get/set value by key from plugins
	void	set(const char*,void*);
	void*	get(const char*);
private:
	Library*					_library;
	std::map<std::string,void*>	_values;
	// unsorted handles,dont using map
	std::list<std::pair<std::string,void*>>	_plugins;
};

library_impl::library_impl(Library* l):_library(l){}

library_impl::~library_impl(){
	for(auto i=_plugins.begin();i!=_plugins.end();++i)
		unload(i->first.c_str());
}

bool library_impl::load(const char* file){
	if(file){
		string name(file);
		name=name.substr(0,name.rfind('.'));
#if(defined(_WIN32)||defined(_WIN64))
		std::transform(name.begin(),name.end(),name.begin(),tolower);	//linux has an error with transform, i'v not resolved
#endif
		// find first
		for(auto i=_plugins.begin();i!=_plugins.end();++i)
			if(i->first==name)
				return true;

		// load lib
		if(auto h=LOAD_LIB(file)){
			// push front
			_plugins.push_front(std::make_pair(name,h));
			// install plugin
			typedef bool (*LPFNREGISTER)(Library*);
			LPFNREGISTER lpfnRegister=(LPFNREGISTER)GET_PROC(h,"installPlugin");
			if(lpfnRegister)
				return (*lpfnRegister)(_library);
		}
	}
	return false;
}

void library_impl::unload(const char* file){
	if(file){
		auto i=_plugins.begin();
		for(auto i=_plugins.begin();i!=_plugins.end();++i)
			if(i->first==file)
				break;

		if(i!=_plugins.end()){
			// uninstall plugin
			auto h=i->second;
			typedef void (*LPFNREGISTER)();
			LPFNREGISTER lpfnRegister=(LPFNREGISTER)GET_PROC(h,"uninstallPlugin");
			if(lpfnRegister)
				(*lpfnRegister)();
			// free lib
			FREE_LIB(h);
		}
	}
}

void library_impl::set(const char* key,void* value){
	if(key){
		if(_values.find(key)==_values.end())
			_values.insert(std::make_pair(key,value));
	}
}

void* library_impl::get(const char* key){
	if(key){
		auto i=_values.find(key),iend=_values.end();
		if(i!=iend)
			return i->second;
	}
	return nullptr;
}
// --------------------------------------------------------
Library::Library(){
	_impl.reset(new library_impl(this));
}

bool Library::load(const char* file){
	return _impl?_impl->load(file):false;
}

void Library::unload(const char* file){
	if(_impl)_impl->unload(file);
}

void Library::set(const char* key,void* value){
	if(_impl)_impl->set(key,value);
}

void* Library::get(const char* key){
	return _impl?_impl->get(key):nullptr;
}
// --------------------------------------------------------
