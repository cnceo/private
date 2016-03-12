// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: buffer_helper.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-09-09
 */
// --------------------------------------------------------
#ifndef _buffer_helper_h_
#define _buffer_helper_h_

namespace keye{
// --------------------------------------------------------
// buffer_wrapper:wrapper only,donot alloc or free real data
// --------------------------------------------------------
class KEYE_API buffer_wrapper{
public:
					buffer_wrapper(void*,size_t=0);
	void			reset();
	size_t			capacity()const;
	void*			data();
	//input
	template<typename T>
	buffer_wrapper&	operator<<(const T& t){return push(&t,sizeof(T));}
	buffer_wrapper&	operator<<(const std::string&);
	buffer_wrapper&	push(const void*,size_t);
	//output
	template<typename T>
	buffer_wrapper&	operator>>(T& t){return pop(&t,sizeof(T));}
	buffer_wrapper&	operator>>(std::string&);
	buffer_wrapper&	pop(void*,size_t);
protected:
	unsigned char*	_buf;
	size_t			_cap,_rp,_wp;
};
// --------------------------------------------------------
// FastStream:fast temp string stream
// --------------------------------------------------------
class KEYE_API FastStream{
public:
				FastStream();
	FastStream&	operator<<(char v);
	FastStream&	operator<<(int v);
	FastStream&	operator<<(unsigned int v);
	FastStream&	operator<<(long long v);
	FastStream&	operator<<(unsigned long long v);
	FastStream&	operator<<(const char* v);
	FastStream&	operator<<(const std::string& v);
	void		clear();
	const char*	str()const;
private:
	const static size_t	_buf_size=2048;
	char		_buf[_buf_size],_tmp[64];
	size_t		_pos;
};
// --------------------------------------------------------
// buffer help functions
// --------------------------------------------------------
template<typename T>
void buf_set(char** buf,const T& val){
	if(buf&&*buf){
		memcpy(*buf,&val,sizeof(T));
		//(*(T*)(*buf))=val;
		(*buf)+=sizeof(T);
	}
}
inline void buf_set(char** buf,const void* val,size_t len){
	if(buf&&*buf&&len){
		memcpy(*buf,val,len);
		//(*(T*)(*buf))=val;
		(*buf)+=len;
	}
}
inline void buf_set(char** buf,const std::string& val){
	buf_set(buf,val.c_str(),val.length());
	buf_set(buf,'\0');
}

template<typename T>
void buf_get(T& val,const char** buf){
	if(buf&&*buf){
		memcpy(&val,*buf,sizeof(T));
		(*buf)+=sizeof(T);
	}
}
inline void buf_get(void* val,size_t len,const char** buf){
	if(buf&&*buf&&len){
		memcpy(&val,*buf,len);
		(*buf)+=len;
	}
}
inline void buf_get(std::string& val,const char** buf){
	if(buf&&*buf){
		val=*buf;
		(*buf)+=val.length()+1;
	}
}
// --------------------------------------------------------
};//namespace keye
#endif//

