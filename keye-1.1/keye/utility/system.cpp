// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: system.cpp
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
time_t ticker(){
	//milliseconds from history
	#ifdef WIN32
	struct _timeb tb;
	_ftime(&tb);
	#else
	struct timeb tb;
	ftime(&tb);
	#endif
	return tb.time*1000+tb.millitm;
}

void pause(){
	printf("press any key to continue...\n");
	getch();
}

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

bool is_bigendian(){
	const int endian=1;
	return ((*(char*)&endian)==0);
}
// --------------------------------------------------------
};//namespace keye
