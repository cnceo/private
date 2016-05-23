// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: ObjectPool.h
 *Desc		: 
 *Version	: 1.0
 *Program	: Vic
 *Date		: 2016-4-25
 */
// --------------------------------------------------------
#ifndef _ObjectPool_h_
#define _ObjectPool_h_
// --------------------------------------------------------
template<typename T>
struct slab_t{
	slab_t	*prev,*next;
	T		slab;
			slab_t():prev(nullptr),next(nullptr){}
};

template<typename T>
class PANDA_API ObjectPool{
public:
	const size_t defaultSize=1000;
	const size_t defaultExtend=16;

	ObjectPool():head(nullptr),size(0){
		extend(defaultSize);
	}

	~ObjectPool(){
		for(auto& mp:mptr){
			alloc.deallocate((slab_t<T>*)mp.prev,mp.slab);
			head=nullptr;
			size=0;
		}
	}

	T*		create(){
		//extend first
		if(size<defaultExtend)extend(defaultExtend<<3);

		auto ptr=head;
		head=head->next;
		if(head)head->prev=nullptr;
		--size;

		auto t=&ptr->slab;
		new (t) T;
		return t;
	};

	void	destroy(T* t){
		if(t){
			auto ptr=(slab_t<T>**)t;
			ptr-=2;
			auto slab=(slab_t<T>*)ptr;
			if(head){
				slab->next=head;
				head->prev=slab;
			}
			head=slab;
			head->prev=nullptr;
			++size;

			t->~T();
		}
	}
private:
	void	extend(size_t count){
		if(count==0)return;
		if(auto ptr=alloc.allocate(count)){
			//link
			for(size_t i=0;i<count;++i){
				if(i+1<count){
					slab_t<T> &cur=ptr[i],
						&nxt=ptr[i+1];
					cur.next=&nxt;
					nxt.prev=&cur;
				}
			}
			//link head and tail
			ptr[count-1].next=head;
			if(head)head->prev=&ptr[count-1];
			head=ptr;
			head->prev=nullptr;
			size+=count;
			//record
			mptr.push_back(slab_t<size_t>());
			auto& mp=mptr.back();
			mp.prev=(decltype(mp.prev))ptr;
			mp.slab=count;
		}
	};

	std::allocator<slab_t<T>> alloc;
	slab_t<T> *head;
	size_t size;
	std::vector<slab_t<size_t>>	mptr;
};
// --------------------------------------------------------
#endif // _ObjectPool_h_
