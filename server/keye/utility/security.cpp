// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: security.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-09-09
 */
// --------------------------------------------------------
#include "stdafx.h"
#include <keye/utility/utility_fwd.h>
#ifdef WIN32
#include <conio.h>
#else
#include <curses.h>
#endif

namespace keye{
// --------------------------------------------------------
long long crc(const void* buf,size_t len,unsigned char bytes){
	long long ret=0;
	switch(bytes){
	case 16:{
		boost::crc_16_type computer;
		computer.process_bytes(buf,len);
		ret=(long long)computer.checksum();
		break;
	}
	case 32:{
		boost::crc_32_type computer;
		computer.process_bytes(buf,len);
		ret=(long long)computer.checksum();
		break;
	}
	}
	return ret;
}
// --------------------------------------------------------
static unsigned char char_to_hex(unsigned char x){
	return(unsigned char)(x > 9 ? x + 55: x + 48);
}

static bool is_alpha_number_char(unsigned char c){
	return ((c >= 'a' && c <= 'z') ||(c >= 'A' && c <= 'Z') ||(c >= '0' && c <= '9'));
}

size_t url_encode(const unsigned char* src,unsigned char* dest,size_t dest_len){
	unsigned char ch;
	size_t len=0,d0=(size_t)dest;
	//prevent overflow
	while(len <(dest_len - 4) && *src){
		ch =(unsigned char)*src;
		if(*src == ' ')
			*dest++ = '+';
		else if(is_alpha_number_char(ch) || strchr("-_.!~*'()", ch))
			*dest++ = *src;
		else{
			*dest++ = '%';
			*dest++ = char_to_hex((unsigned char)(ch >> 4));
			*dest++ = char_to_hex((unsigned char)(ch % 16));
		} 
		++src;
		++len;
	}
	*dest='\0';
	return (size_t)dest-d0;
}

size_t url_decode(const unsigned char* encd,unsigned char* decd){
	char *cd =(char*)encd;
	size_t d0=(size_t)decd;
	char p[2];
	size_t j=0;
	for(size_t i = 0,ii=strlen(cd);i<ii; i++){
		memset(p, '\0', 2);
		if(cd[i] != '%'){
			decd[j++] = cd[i];
			continue;
		}  
		p[0] = cd[++i];
		p[1] = cd[++i];

		p[0] = p[0] - 48 -((p[0] >= 'A') ? 7 : 0) -((p[0] >= 'a') ? 32 : 0);
		p[1] = p[1] - 48 -((p[1] >= 'A') ? 7 : 0) -((p[1] >= 'a') ? 32 : 0);
		decd[j++] =(unsigned char)(p[0] * 16 + p[1]);
	}
	decd[j]='\0';
	return j+1;
}
// --------------------------------------------------------
};//namespace keye
