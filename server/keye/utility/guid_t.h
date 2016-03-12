// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: guid_t.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-09-09
 */
// --------------------------------------------------------
#ifndef _guid_t_h_
#define _guid_t_h_

namespace keye{
class KEYE_API guid_t{
public:
						guid_t();
	guid_t&				operator=(const guid_t&);
	guid_t&				operator=(const std::string&);
	bool				operator==(const guid_t&);
	bool				operator!=(const guid_t&);
	const std::string&	to_string();
private:
	unsigned char		_uuid[16];
	std::string			_str_buf;
	bool				_dirty;
};
};//namespace keye
#endif//
