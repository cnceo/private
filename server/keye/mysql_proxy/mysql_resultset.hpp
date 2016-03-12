// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: mysql_resultset.hpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-09-29
 */
// --------------------------------------------------------
#ifndef _mysql_resultset_hpp_
#define _mysql_resultset_hpp_

enum enum_field_types {
	MYSQL_TYPE_DECIMAL, MYSQL_TYPE_TINY,
	MYSQL_TYPE_SHORT, MYSQL_TYPE_LONG,
	MYSQL_TYPE_FLOAT, MYSQL_TYPE_DOUBLE,
	MYSQL_TYPE_NULL, MYSQL_TYPE_TIMESTAMP,
	MYSQL_TYPE_LONGLONG, MYSQL_TYPE_INT24,
	MYSQL_TYPE_DATE, MYSQL_TYPE_TIME,
	MYSQL_TYPE_DATETIME, MYSQL_TYPE_YEAR,
	MYSQL_TYPE_NEWDATE, MYSQL_TYPE_VARCHAR,
	MYSQL_TYPE_BIT,
	MYSQL_TYPE_NEWDECIMAL = 246,
	MYSQL_TYPE_ENUM = 247,
	MYSQL_TYPE_SET = 248,
	MYSQL_TYPE_TINY_BLOB = 249,
	MYSQL_TYPE_MEDIUM_BLOB = 250,
	MYSQL_TYPE_LONG_BLOB = 251,
	MYSQL_TYPE_BLOB = 252,
	MYSQL_TYPE_VAR_STRING = 253,
	MYSQL_TYPE_STRING = 254,
	MYSQL_TYPE_GEOMETRY = 255

};

namespace keye{
// --------------------------------------------------------
class mysql_resultset_impl{
public:
				//from buffer
				mysql_resultset_impl(mysql_resultset&,const void* =nullptr,size_t len =0);
private:
	friend class mysql_statement;
	friend class mysql_resultset_builder;
	friend class mysql_statement_impl;
	friend class parameter_impl;
				//from query
				mysql_resultset_impl(mysql_resultset&,MYSQL_STMT*,const char* sql,size_t id=0);
	static size_t			_field_len(e_field);
	static enum_field_types	_map(e_field);
	static e_field			_map(enum_field_types);
};
// --------------------------------------------------------
};// namespace
#endif // _mysql_resultset_hpp_
