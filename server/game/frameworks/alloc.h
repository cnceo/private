// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: alloc.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _alloc_h_
#define _alloc_h_

typedef std::allocator<char>			std_ax_t;
typedef keye::keye_allocator<std_ax_t>	keye_ax_t;
// --------------------------------------------------------
class Alloc:public htio_alloc{
public:
					Alloc():_kax(64<<20,_sax){}
	virtual void*	allocate(size_t _Count){return _sax.allocate(_Count);}
	virtual void	deallocate(void* _Ptr, size_t=0){_sax.deallocate((char*)_Ptr,0);}
private:
	std_ax_t		_sax;
	keye_ax_t		_kax;
};

#endif