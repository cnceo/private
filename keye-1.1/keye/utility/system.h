// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: system.ch
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-09-09
 */
// --------------------------------------------------------
#ifndef _system_h_
#define _system_h_

namespace keye{
//milliseconds from history
time_t		KEYE_API ticker();
//press any key to continue...
void		KEYE_API pause();
//bits:16,32;checksum could be short or integer value
long long	KEYE_API crc(const void*,size_t,unsigned char bits=32);
//big/little endian test
bool		KEYE_API is_bigendian();
};//namespace keye
#endif//

