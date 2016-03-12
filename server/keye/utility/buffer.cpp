// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: buffer.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-09-09
 */
// --------------------------------------------------------
#include "stdafx.h"
#include <keye/utility/utility_fwd.h>
namespace keye{
// --------------------------------------------------------
buffer_wrapper::buffer_wrapper(void* buf,size_t sz)
	:_buf((unsigned char*)buf),_cap(sz),_rp(0),_wp(0){}

void buffer_wrapper::reset(){
	_rp=_wp=0;
}

size_t buffer_wrapper::capacity()const{
	return _cap;
}

void* buffer_wrapper::data(){
	return _buf;
}

buffer_wrapper& buffer_wrapper::operator<<(const std::string& s){
	size_t len=s.length();
	if(len<=_cap-_rp-1){
		push(s.data(),len);
		*this<<'\0';
	}
	return *this;
}

buffer_wrapper& buffer_wrapper::push(const void* buf,size_t sz){
	if(sz<=_cap-_rp){
		memcpy(_buf+_rp,buf,sz);
		_rp+=sz;
	}
	return *this;
}

buffer_wrapper&	buffer_wrapper::operator>>(std::string& s){
	if(_buf&&_wp<_cap){
		s=(char*)_buf+_wp;
		_wp+=s.length()+1;
	}
	return *this;
}

buffer_wrapper&	buffer_wrapper::pop(void* buf,size_t sz){
	if(_buf&&_wp<_cap){
		memcpy(buf,_buf+_wp,sz);
		_wp+=sz;
	}
	return *this;
}
// --------------------------------------------------------
FastStream::FastStream():_pos(0){
	memset(_buf,0,FastStream::_buf_size);
}
void FastStream::clear(){
	_buf[_pos=0]='\0';
}
const char* FastStream::str()const{
	return _buf;
}
FastStream& FastStream::operator<<(char v){
	if(_buf_size-_pos>1){
		_buf[_pos++]=v;
		_buf[_pos]='\0';
	}
	return *this;
}
FastStream& FastStream::operator<<(int v){
	if(_buf_size-_pos>32)
		_pos+=sprintf(_buf+_pos,"%d",v);
	else if(sprintf(_tmp,"%d",v))
		(*this)<<_tmp;
	return *this;
}
FastStream& FastStream::operator<<(unsigned int v){
	return (*this)<<(int)v;
}
FastStream& FastStream::operator<<(long long v){
	if(_buf_size-_pos>64)
		_pos+=sprintf(_buf+_pos,"%Ld",v);
	else if(sprintf(_tmp,"%Ld",v))
		(*this)<<_tmp;
	return *this;
}
FastStream& FastStream::operator<<(unsigned long long v){
	return (*this)<<(long long)v;
}
FastStream& FastStream::operator<<(const char* v){
	if(v){
		if(size_t sz=strlen(v)){
			const size_t len=_buf_size-_pos;
			if(sz>=len)sz=len-1;
			memcpy(_buf+_pos,v,sz);
			_pos+=sz;
			_buf[_pos]='\0';
		}
	}
	return *this;
}
FastStream& FastStream::operator<<(const std::string& v){
	return (*this)<<v.c_str();
}
// --------------------------------------------------------
};//namespace keye
