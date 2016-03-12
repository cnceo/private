// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: guid_t.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-09-09
 */
// --------------------------------------------------------
#include "stdafx.h"
#include <algorithm>
#include <keye/utility/utility_fwd.h>

//#define _UUID_H_

#ifdef WIN32
#	include <objbase.h>
#elif defined(_UUID_H_)
#	include <uuid/uuid.h>
#endif

using namespace keye;
static const size_t uuid_str_len=36;
/*
typedef struct _GUID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[ 8 ];
} GUID;
*/
// --------------------------------------------------------
guid_t::guid_t():_dirty(true){
#ifdef WIN32
	GUID* guid=(GUID*)_uuid;
	CoCreateGuid(guid);
#elif defined(_UUID_H_)
	uuid_generate(reinterpret_cast<unsigned char*>(_uuid));
#endif
}

guid_t& guid_t::operator=(const std::string& s){
	size_t ii=s.length();
	if(ii==uuid_str_len){
		std::string ss,t;
		for(auto i=s.begin(),ii=s.end();i!=ii;++i){
			auto c=*i;
			if(c!='-')ss+=c;
		}

		auto p=&_uuid[0];
		t=ss.substr(0,8);
		auto l=strtol(t.c_str(),nullptr,16);
		*(unsigned long*)p=l;
		p+=4;

		t=ss.substr(8,4);
		l=strtol(t.c_str(),nullptr,16);
		*(unsigned long*)p=l;
		p+=2;

		t=ss.substr(12,4);
		l=strtol(t.c_str(),nullptr,16);
		*(unsigned long*)p=l;
		p+=2;

		t=ss.substr(16);
		size_t pos=0;
		for(auto i=0;i<8;++i){
			ss=t.substr(pos,2);
			l=strtol(ss.c_str(),nullptr,16);
			*(unsigned long*)p=l;
			++p;
			pos+=2;
		}
		_dirty=true;
	}
	return *this;
}

guid_t& guid_t::operator=(const guid_t& g){
	memcpy(_uuid,g._uuid,sizeof(_uuid));
	_dirty=true;
	return *this;
}

bool guid_t::operator==(const guid_t& g){
	for(auto i=0;i<16;++i)
		if(_uuid[i]!=g._uuid[i])return false;
	return true;
}

bool guid_t::operator!=(const guid_t& g){
	return !((*this)==g);
}

const std::string& guid_t::to_string(){
	if(_dirty){
		_str_buf.resize(uuid_str_len+1);
		auto buf=(char*)_str_buf.data();
		sprintf(buf,"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
			(unsigned long)_uuid[0],(unsigned short)_uuid[4],(unsigned short)_uuid[6],
			_uuid[8+0],_uuid[8+1],
			_uuid[8+2],_uuid[8+3],
			_uuid[8+4],_uuid[8+5],
			_uuid[8+6],_uuid[8+7]);
		_dirty=false;
	}
	return _str_buf;
}
