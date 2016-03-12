// --------------------------------------------------------
/*Copyright Keye Knew.All rights reserved.
 *
 *File		: conf_file.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: Keye Knew
 *Date		: 2012-10-31
 */
// --------------------------------------------------------
#include "stdafx.h"
#include <fstream>
#include "utility_fwd.h"

using namespace keye;

static const std::string LF("\n"),CR("\r"),CL("\r\n"),TAB("\t"),SPACE(" ");
// --------------------------------------------------------
txt_file::txt_file():_endl(CL),_endlen(CL.length()){}

bool txt_file::load(const char* file){
	if(!file){
		LOG("no file specified.\n");
		return false;
	}

	std::ifstream fp;
	fp.open(file,std::ios::in|std::ios::binary);
	if(!fp.is_open()){
		LOG("file %s does not exist\n",file);
		return false;
	}

	fp.seekg(0,std::ios_base::end);
	auto sz=(size_t)fp.tellg();
	if(sz){
		fp.seekg(0, std::ios_base::beg);
		std::string buf;
		buf.resize(sz);
		auto ptr=(char*)buf.data();
		fp.read(ptr,static_cast<std::streamsize>(sz));
		fp.close();
		if(_check_endl(buf,CL)||_check_endl(buf,LF)||_check_endl(buf,CR))
			return _parse(buf);
		else{
			LOG("file without endl\n");
			return false;
		}
	}else{
		fp.close();
		LOG("file empty\n");
		return false;
	}
}

bool txt_file::save(const char* file){
	if(!file){
		LOG("no file specified.\n");
		return false;
	}

	std::ofstream fp;
	fp.open(file,std::ios::out|std::ios::binary);
	if(!fp.is_open()){
		LOG("file %s open failed.\n",file);
		return false;
	}

	std::string buf;
	auto ret=_make_buffer(buf);
	if(ret)
		fp.write(buf.c_str(),buf.size());
	else
		LOG("file empty\n");
	fp.close();
	return true;
}

bool txt_file::_check_endl(const std::string& buf,const std::string& endl){
	if(std::string::npos!=buf.find(endl)){
		_endl=endl;
		_endlen=endl.length();
		return true;
	}else
		return false;
}
// --------------------------------------------------------
tab_file::tab_file():_rows(0),_cols(0){}

bool tab_file::_parse(const std::string& buf){
	//reset
	_rows=_cols=0;
	_grids.clear();
	//load
	size_t beg=0,end=0;
	end=(size_t)buf.find(_endl,beg);
	auto title=buf.substr(beg,end-beg);
	if(_parse_title(title)){
		while(true){
			beg=end+_endlen;
			end=buf.find(_endl,beg);
			if(std::string::npos==end)
				break;

			auto content=buf.substr(beg,end-beg);
			if(_parse_content(content))
				++_rows;
		}
		return true;
	}else
		return false;
}

bool tab_file::_parse_title(const std::string& buf){
	size_t beg=0,cur=0,end=buf.size();
	bool over=false;
	while(!over){
		cur=buf.find(TAB,beg);
		if(std::string::npos==cur){
			cur=end;
			over=true;
		}
		auto str=buf.substr(beg,cur-beg);
		cast_t grid(str.c_str());
		_grids.push_back(grid);
		if(!over)
			beg=cur+TAB.length();
		//update
		++_cols;
	}
	return true;
}

bool tab_file::_parse_content(const std::string& buf){
	size_t beg=0,cur=0,end=buf.size();
	bool over=false;
	while(!over){
		cur=buf.find(TAB,beg);
		if(std::string::npos==cur){
			cur=end;
			over=true;
		}
		std::string str(buf.substr(beg,cur-beg));
		if(str.empty())str="0";
		cast_t grid(str.c_str());
		_grids.push_back(grid);
		if(!over)
			beg=cur+TAB.length();
	}
	return true;
}

size_t tab_file::rows()const{
	return _rows;
}

size_t tab_file::colulmns()const{
	return _cols;
}

const cast_t& tab_file::value(size_t row,size_t col)const{
	if(row<_rows&&col<_cols)
		return _grids[(row+1)*_cols+col];
	return _default;
}

bool tab_file::_make_buffer(std::string& buf){
	if(0==_rows||0==_cols)return false;

	buf.clear();
	//title
	for(size_t j=0;j<_cols;++j){
		auto s=(const char*)_grids[j];
		buf+=s;
		buf+=(j==_cols-1)?CL:TAB;
	}
	//content
	for(size_t i=0;i<_rows;++i){
		for(size_t j=0;j<_cols;++j){
			auto s=(const char*)value(i,j);
			buf+=s;
			buf+=(j==_cols-1)?CL:TAB;
		}
	}
	return true;
}

void tab_file::print()const{
	if(0==_rows||0==_cols)return;

	const char* LINE="|---------------";
	LOG("rows=%d,columns=%d\n",_rows,_cols);
	//title
	for(size_t j=0;j<_cols;++j)
		LOG(LINE);
	LOG("|\n");
	for(size_t j=0;j<_cols;++j){
		auto s=(const char*)_grids[j];
		LOG("%s",s);
		if(strlen(s)<8)
			LOG("\t\t");
		else if(strlen(s)<16)
			LOG("\t");
	}
	LOG("\n");
	//content
	for(size_t j=0;j<_cols;++j)
		LOG(LINE);
	LOG("|\n");
	for(size_t i=0;i<_rows;++i){
		for(size_t j=0;j<_cols;++j){
			auto s=(const char*)value(i,j);
			LOG("%s",s);
			if(strlen(s)<8)
				LOG("\t\t");
			else if(strlen(s)<16)
				LOG("\t");
		}
		LOG("\n");
	}
	for(size_t j=0;j<_cols;++j)
		LOG(LINE);
	LOG("|\n");
}
// --------------------------------------------------------
bool ini_file::_parse(const std::string& buf){
	//reset
	_map.clear();
	//load
	size_t beg=0,end=0,cur=0;
	bool over=false;
	while(!over){
		cur=buf.find(_endl,beg);
		if(std::string::npos==cur){
			cur=end;
			over=true;
		}
		auto str=buf.substr(beg,cur-beg);
		_parse_content(str);
		if(!over)
			beg=cur+_endlen;
	}
	return true;
}

bool ini_file::_parse_content(const std::string& buf){
	size_t beg=0,cur=0,end=buf.size();
	cur=buf.find("=",beg);
	if(std::string::npos!=cur){
		std::string key(buf.substr(0,cur)),
			val(buf.substr(cur+1));
		_clean(key),_clean(key,' ');
		_clean(val),_clean(val,' ');
		if(val.empty())val="0";
		cast_t grid(val.c_str());
		_map.insert(std::make_pair(key,grid));
	}
	return true;
}

const cast_t& ini_file::value(const char* key)const{
	if(key&&!_map.empty()){
		auto i=_map.find(key);
		if(i!=_map.end())
			return i->second;
	}
	return _default;
}

void ini_file::_clean(std::string& ss,char c){
	while(0==ss.find(c))ss=ss.substr(1);
	while(true){
		size_t i=ss.rfind(c),ii=ss.length()-1;
		if(i==ii&&i!=std::string::npos)ss=ss.substr(0,ii);
		else break;
	}
}

bool ini_file::_make_buffer(std::string& buf){
	if(_map.empty())return false;

	buf.clear();
	for(auto i=_map.begin(),ii=_map.end();i!=ii;++i){
		auto& key=i->first;
		const char* val=i->second;
		buf+=key+"="+val+CL;
	}
	return true;
}

void ini_file::print()const{
	for(auto i=_map.begin(),ii=_map.end();i!=ii;++i){
		auto& key=i->first;
		const char* val=i->second;
		LOG("%s",key.c_str());
		auto len=key.length();
		if(len<8)
			LOG("\t\t");
		else if(len<16)
			LOG("\t");
		LOG("=%s\n",val);
	}
}
// --------------------------------------------------------
cast_t::cast_t(const char* raw){
	_raw=raw?raw:"0";
}

cast_t::operator int()const{
	return atoi(_raw.c_str());
}

cast_t::operator float()const{
	return (float)atof(_raw.c_str());
}

cast_t::operator const char*()const{
	return _raw.c_str();
}
