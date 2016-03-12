// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: Receiver.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2011-4-22
 */
// --------------------------------------------------------
#include "stdafx.h"
#ifndef NO_MYSQL
#include <keye/mysql_proxy/mysql_proxy_fwd.h>
#include <keye/mysql_proxy/mysql_parameters.hpp>
#include <keye/mysql_proxy/mysql_statement.hpp>
#include <keye/mysql_proxy/mysql_resultset.hpp>
#include <mysql/errmsg.h>

using namespace keye;

mysql_statement_impl::mysql_statement_impl(const char* name,const char* db)
:_name(name){
	if(db)_db=db;
}

void mysql_statement_impl::_prepare(const mysql_parameter* params){
	if(_sql.empty()&&!_name.empty()){
		if(std::string::npos==_name.find(' ')){
			//procedure
			_sql = "CALL "+_name+"(";
			if(params)
			for (uint8_t i=0,ii=params->size();i<ii;i++){
				if (i)_sql += ",";
				_sql += "?";
			}
			_sql += ")";
		}else{
			//normal query statement
			_sql=_name;
		}
	}
}

s_ptr<mysql_resultset> mysql_statement_impl::execute(MYSQL* mysql,mysql_parameter* params){
	_prepare(params);

	s_ptr<mysql_resultset> sprs;
	if(mysql&&!_sql.empty())try{
		//mysql_stmt_init
		if(MYSQL_STMT* stmt = mysql_stmt_init(mysql))try{
			if (mysql_stmt_prepare(stmt,_sql.c_str(),_sql.length()))
				throw std::runtime_error("mysql_stmt_prepare error.");
			size_t id=0;
			if(params&&params->_impl){
				id=params->id();
				MYSQL_BIND* bind_params=params->_impl->_mysql_binds.get();
				unsigned short number_of_params=params->size();
				if (bind_params != NULL && number_of_params != 0){
					if (mysql_stmt_param_count(stmt) != number_of_params)
						throw std::invalid_argument("invalid parameter count");
					if (mysql_stmt_bind_param(stmt, bind_params))
						throw std::runtime_error("mysql_stmt_bind_param error.");
				}

				LINFO("execute \"%s\"\n",_sql.c_str());
//				size_t len;
//				params->deserialize(len);
			}

			if(mysql_stmt_execute(stmt)){
				//try execute from mysql console
				throw std::runtime_error(mysql_stmt_error(stmt));
			}
			//result set
			sprs.reset(new mysql_resultset());
			sprs->_impl.reset(new mysql_resultset_impl(*sprs,stmt,_sql.c_str(),id));
			//throw to free
			throw std::exception();
//			throw std::exception("ok");
		}catch (std::exception& err){
			//free result
			int status = 0;
			do{// 调用存储过程，会返回多个结果集（后续的结果集为空，但必须取走，否则会出错OUT_OF_SYNC）
				status = mysql_stmt_next_result(stmt);
			} while (status == 0);
			mysql_stmt_free_result(stmt);
			if(strlen(err.what())>3)
				LOG("%s\n",err.what());
		}else
			throw std::runtime_error("mysql_stmt_init error.");
	}catch (std::exception& err){
		LOG("%s",err.what());
	}
	return sprs;
}
// --------------------------------------------------------
mysql_statement::mysql_statement(const char* name,const char* db){
	_impl.reset(new mysql_statement_impl(name,db));
}

const char* mysql_statement::name()const{return _impl?_impl->name():nullptr;}
const char* mysql_statement::database()const{return _impl?_impl->database():nullptr;}
#endif
