// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: mysql_resultset.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2011-4-22
 */
// --------------------------------------------------------
#include "stdafx.h"
#include <keye/mysql_proxy/mysql_proxy_fwd.h>
#include <keye/mysql_proxy/mysql_resultset.hpp>
#include <keye/mysql_proxy/mysql_error.hpp>

using namespace keye;

enum{
	RESULT_SET_BUFFER_MAX_LENGTH=2048,		// 结果数据，每个数据包最多发送2500字节
};
// --------------------------------------------------------
mysql_resultset_impl::mysql_resultset_impl(mysql_resultset& host,MYSQL_STMT* _stmt,const char* _sql,size_t id_){
	host.id=id_;
	host.length=sizeof(host.id)+sizeof(uint16_t)+sizeof(uint8_t);
	MYSQL_RES* _mysql_res=nullptr;
	//ctor resultset by MYSQL_STMT
	if(_stmt&&_sql)try{
		//fetch fields
		_mysql_res = mysql_stmt_result_metadata(_stmt);
		if (!_mysql_res)
			throw_stmt_error("empty result", _stmt, _sql);
		MYSQL_FIELD* fields = mysql_fetch_fields(_mysql_res);
		//fields count
		uint8_t nFields=mysql_stmt_field_count(_stmt);
		host.head.resize(nFields);
		//prepare MYSQL_BIND for data fetch
		s_ptr<MYSQL_BIND> binds(new MYSQL_BIND[nFields],std::default_delete<MYSQL_BIND[]>());
		std::vector<s_ptr<char>> vbuf(nFields);	//buffer
		std::vector<size_t> lengths(nFields);	//length pointer
		for(uint8_t i=0;i<nFields;++i){
			MYSQL_FIELD& field=fields[i];
			host.head[i]=_map(field.type);

			size_t max_len=sizeof(long long);
			if(EF_STRING==host.head[i]||EF_BLOB==host.head[i])
				max_len=RESULT_SET_BUFFER_MAX_LENGTH;
			vbuf[i].reset(new char[max_len],std::default_delete<char[]>());
			MYSQL_BIND& bind_=binds.get()[i];
			bind_.buffer_type = field.type;
			bind_.buffer = vbuf[i].get();
			bind_.buffer_length = max_len;
			bind_.length =(unsigned long*)&lengths[i];
			bind_.is_null = 0;
			bind_.error = 0;
		}
		//bind and store result
		if (mysql_stmt_bind_result(_stmt, binds.get()))
			throw_stmt_error("mysql_stmt_bind_result", _stmt, _sql);
		if (mysql_stmt_store_result(_stmt))
			throw_stmt_error("mysql_stmt_store_result", _stmt, _sql);
		auto nRows=(uint16_t)mysql_stmt_num_rows(_stmt);
		host.rows.resize(nRows);

		//all length:id,rows,fields number,head length
		host.length+=sizeof(e_field)*nFields;
		//rows length
		for (size_t i=0,ii=host.rows.size();i<ii;++i){
			if(0!=mysql_stmt_fetch(_stmt))
				break;

			uint16_t row_data_length=0;
			for(uint8_t j=0;j<nFields;++j){
				row_data_length+=lengths[j];
				if(EF_STRING==host.head[j]||EF_BLOB==host.head[j])
					//append string and blob length
					row_data_length+=sizeof(unsigned short);
			}
			host.rows[i].length=row_data_length;
			host.rows[i].fields.resize(nFields);
			host.length += row_data_length;
		}
		//fill buffer
		host.buffer.reset(new char[host.length],std::default_delete<char[]>());
		char* buf=host.buffer.get();
		buf_set(&buf,id_);
		buf_set(&buf,nRows);
		buf_set(&buf,nFields);
		for(uint8_t j=0;j<nFields;++j)
			buf_set(&buf,host.head[j]);
		//fetch and copy data
		mysql_stmt_data_seek(_stmt,0);
		for (size_t i=0,ii=host.rows.size();i<ii;++i){
			if(0!=mysql_stmt_fetch(_stmt))
				break;
			for(uint8_t j=0;j<nFields;++j){
				//record field pointer
				host.rows[i].fields[j]=buf;
				size_t len=lengths[j];
				if(EF_STRING==host.head[j]||EF_BLOB==host.head[j])
					//append string or blob length
					buf_set(&buf,(unsigned short)len);
				char* src=vbuf[j].get();
				buf_set(&buf,src,len);
			}
		}
		LINFO("fetch rows: %d,fields: %d,length: %d.\n",nRows,nFields,host.length);
//		throw std::exception("ok");
		throw std::exception();
	}catch (std::exception& err){
		//free result
		mysql_free_result(_mysql_res);
		if(strlen(err.what())>3)
			LOG("mysql_stmt_fetch, %s",err.what());
	}
}

mysql_resultset_impl::mysql_resultset_impl(mysql_resultset& host,const void* src,size_t len){
	host.length=sizeof(host.id)+sizeof(uint16_t)+sizeof(uint8_t);
	//ctor resultset from buffer
	if(!src||len<=0)return;
	//copy buffer
	host.length=len;
	host.buffer.reset(new char[host.length],std::default_delete<char[]>());
	char* buf=host.buffer.get();
	memcpy(buf,src,host.length);
	const char* ptr=(const char*)buf;
	//rows,fields
	unsigned short nRows;
	unsigned char nFields;
	buf_get(host.id,&ptr);
	buf_get(nRows,&ptr);
	buf_get(nFields,&ptr);
	host.rows.resize(nRows);
	host.head.resize(nFields);
	LINFO("receive rows: %d,fields: %d,length: %d.\n",nRows,nFields,host.length);
	//head
	for (uint8_t i = 0; i<nFields; i++)
		buf_get((unsigned char&)host.head[i],&ptr);
	//rows
	if(nRows){
	LINFO("\nquerry result\n---------------------------------------------\n");
	uint16_t field_len=0;
	for(uint16_t j=0;j<nRows;++j){
		row_t& row=host.rows[j];
		row.length=0;
		row.fields.resize(nFields);
		for (uint8_t i = 0; i<nFields; i++){
			switch(host.head[i]){
			case EF_BYTE:
				row.length+=1;
				row.fields[i]=(void*)ptr;
				LINFO("%d\t",*(char*)ptr);
				ptr+=1;
				break;
			case EF_SHORT:
				row.length+=2;
				row.fields[i]=(void*)ptr;
				LINFO("%d\t",*(short*)ptr);
				ptr+=2;
				break;
			case EF_INT:
				row.length+=4;
				row.fields[i]=(void*)ptr;
				LINFO("%d\t",*(int*)ptr);
				ptr+=4;
				break;
			case EF_LONGLONG:
				row.length+=8;
				row.fields[i]=(void*)ptr;
				LINFO("%lld\t",*(long long*)ptr);
				ptr+=8;
				break;
			case EF_STRING:
				row.fields[i]=(void*)ptr;
				buf_get(field_len,&ptr);
				row.length+=field_len;
				do{
					char str[256];
					size_t str_len=field_len>=256?256:field_len;
					memcpy(str,ptr,str_len);
					str[str_len]='\0';
					LINFO("%s\t",str);
				}while(false);
				ptr+=field_len;
				break;
			case EF_BLOB:
				row.fields[i]=(void*)ptr;
				buf_get(field_len,&ptr);
				row.length+=field_len;
				LINFO("blob(%d)\t",field_len);
				ptr+=field_len;
				break;
			}
		}
		LINFO("\n");
	}
	LINFO("\n---------------------------------------------\n");
	}
}

size_t mysql_resultset_impl::_field_len(e_field field_type){
	size_t len=0;
	switch (field_type){
	case EF_BYTE:
		len = sizeof(uint8_t);
		break;
	case EF_SHORT:
		len = sizeof(uint16_t);
		break;
	case EF_INT:
		len = sizeof(uint32_t);
		break;
	case EF_LONGLONG:
		len = sizeof(uint64_t);
		break;
	}
	return len;
}

enum_field_types mysql_resultset_impl::_map(e_field e){
	switch(e){
	case EF_BYTE:
		return MYSQL_TYPE_TINY;
	case EF_SHORT:
		return MYSQL_TYPE_SHORT;
	case EF_INT:
		return MYSQL_TYPE_LONG;
	case EF_LONGLONG:
		return MYSQL_TYPE_LONGLONG;
	case EF_STRING:
		return MYSQL_TYPE_STRING;
	case EF_BLOB:
	default:
		return MYSQL_TYPE_BLOB;
	}
}

e_field mysql_resultset_impl::_map(enum_field_types e){
	switch(e){
	case MYSQL_TYPE_TINY:
		return EF_BYTE;
	case MYSQL_TYPE_SHORT:
		return EF_SHORT;
	case MYSQL_TYPE_LONG:
		return EF_INT;
	case MYSQL_TYPE_LONGLONG:
		return EF_LONGLONG;
	case MYSQL_TYPE_STRING:
	case MYSQL_TYPE_VAR_STRING:
		return EF_STRING;
	case MYSQL_TYPE_BLOB:
	default:
		return EF_BLOB;
	}
}
// --------------------------------------------------------
mysql_resultset::mysql_resultset(const void* src,size_t len)
:length(0),id(0){
	_impl.reset(new mysql_resultset_impl(*this,src,len));
}
// --------------------------------------------------------
mysql_resultset_builder::mysql_resultset_builder(mysql_resultset& rs)
:_rs(rs){}

void mysql_resultset_builder::add_field(e_field e){
	_rs.head.push_back(e);
	_rs.length+=sizeof(e_field);
}

void mysql_resultset_builder::add_row(row_t& row){
	_rs.rows.push_back(row);
	_rs.length+=row.length;
}

bool mysql_resultset_builder::build(size_t id){
	uint8_t nFields=_rs.head.size();
	uint16_t nRows=_rs.rows.size();
	//fill buffer
	_rs.buffer.reset(new char[_rs.length],std::default_delete<char[]>());
	char* buf=_rs.buffer.get();
	buf_set(&buf,id);
	buf_set(&buf,nRows);
	buf_set(&buf,nFields);
	for(uint8_t j=0;j<nFields;++j)
		buf_set(&buf,_rs.head[j]);
	//fetch and copy data
	for (size_t i=0,ii=_rs.rows.size();i<ii;++i){
		auto& row=_rs.rows[i];
		for(uint8_t j=0;j<nFields;++j){
			auto e=_rs.head[j];
			auto src=(const char*)row.fields[j];
			//record field pointer
			row.fields[j]=buf;
			size_t len=0;
			if(EF_STRING==e||EF_BLOB==e){
				//append string or blob length
				buf_get(len,&src);
				buf_set(&buf,(unsigned short)len);
			}else
				len=mysql_resultset_impl::_field_len(e);
			buf_set(&buf,src,len);
		}
	}
	return true;
}
