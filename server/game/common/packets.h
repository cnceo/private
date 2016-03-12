// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: packets.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _packets_h_
#define _packets_h_

struct csmsg_auth{
	unsigned char	sz_name,sz_pswd;
	char			msg[0];
};

#endif
