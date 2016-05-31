// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: Utils.h
 *Desc		: 
 *Version	: 1.0
 *Program	: Vic
 *Date		: 2016-4-25
 */
// --------------------------------------------------------
#ifndef _Utils_h_
#define _Utils_h_

#include <time.h>
// --------------------------------------------------------
static size_t generateId(void* ptr=nullptr){
	if(ptr)return (size_t)ptr;
	else return (size_t)time(nullptr);
}
// --------------------------------------------------------
#endif // _Utils_h_
