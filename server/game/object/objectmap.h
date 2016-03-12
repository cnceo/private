// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: objectmap.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _objectmap_h_
#define _objectmap_h_
// --------------------------------------------------------
// ObjectMap
// --------------------------------------------------------
class ObjectMap{
public:
				ObjectMap();
	//object factory
	template<typename T>
	T*			create(){
		T* t=nullptr;
		if(auto ptr=game.alloc().allocate(sizeof(T))){
			new(ptr) T;
			t=(T*)ptr;
			t->_sid=_genSid();
			_insert(t);
		}
		return t;
	};
	template<typename T>
	void		destroy(T* t){
		if(t){
			_remove(t);
			_regenSid(t->_sid);
			t->~T();
			game.alloc().deallocate(t);
		}
	}
	//object visitor,T::visit(Object*)
	template<typename V>
	void		visit(V* v,Object::_t tp=Object::UNKNOWN){
		if(v){
			if(UNKNOWN==tp){
				for(auto i=_om.begin(),ii=_om.end();i!=ii;++i){
					auto& om=i->second;
					for(auto j=om.begin(),jj=om.end();j!=jj;++j)
						v->visit(*j);
				}
			}else{
				auto i=_om.find(tp);
				if(i!=_om.end()){
					auto& om=i->second;
					for(auto j=om.begin(),jj=om.end();j!=jj;++j)
						v->visit(*j);
				}
			}
		}
	}
private:
	void		_insert(Object* o);
	void		_remove(Object* o);
	//server id
	size_t		_genSid();
	void		_regenSid(size_t);
	std::map<Object::_t,std::map<size_t,Object*>>	_om;
	std::vector<size_t>		_lid;
};

#endif