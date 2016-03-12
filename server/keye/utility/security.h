// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: security.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-09-09
 */
// --------------------------------------------------------
#ifndef _security_h_
#define _security_h_

namespace keye{
//bits:16,32;checksum could be short or integer value
long long	KEYE_API crc(const void*,size_t,unsigned char bits=32);

//url encode,return dest length
size_t		KEYE_API url_encode(const unsigned char* src,unsigned char* dest,size_t max_len);
size_t		KEYE_API url_decode(const unsigned char* src,unsigned char* dest);
};//namespace keye
#endif

