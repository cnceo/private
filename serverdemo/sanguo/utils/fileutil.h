//
//  fileutil.h
//  sanguo
//
//  Created by Vic Liu on 9/12/15.
//  Copyright (c) 2015 Vic Liu. All rights reserved.
//

#ifndef __sanguo__fileutil__
#define __sanguo__fileutil__

//#include <stdio.h>
namespace vl{
    // --------------------------------------------------------
    // cast_t:a help type casting class
    // --------------------------------------------------------
    class VL_API cast_t{
        std::string		_raw;
    public:
        cast_t(const char* =nullptr);
        operator int()const;
        operator float()const;
        operator const char*()const;
    };
    // --------------------------------------------------------
    /* txt_file:file lines split by "\n","\r" or "\r\n".
     store by string and auto cast value returned */
    // --------------------------------------------------------
    class VL_API txt_file{
    public:
        txt_file();
        virtual			~txt_file(){}
        bool			load(const char*);
        bool			save(const char*);
        //test print in console
        virtual void	print()const=0;
    protected:
        virtual bool	_parse(const std::string&)=0;
        virtual bool	_make_buffer(std::string&)=0;
        bool			_check_endl(const std::string& buf,const std::string& endl);
        
        cast_t			_default;
        std::string		_endl;	//"\n","\r" or "\r\n"
        size_t			_endlen;
    };
    // --------------------------------------------------------
    // tab_file:elements inline split by "\t"
    // --------------------------------------------------------
    class VL_API tab_file:public txt_file{
    public:
        tab_file();
        size_t			rows()const;
        size_t			colulmns()const;
        /* retrieve values,usage:auto val=value(x,y)
         cast_t will auto cast types */
        const cast_t&	value(size_t row,size_t col)const;
        //test print in console
        virtual void	print()const;
    private:
        virtual bool	_parse(const std::string&);
        virtual bool	_make_buffer(std::string&);
        
        size_t				_rows,_cols;
        std::vector<cast_t>	_grids;
    };
    // --------------------------------------------------------
    // ini_file:elements inline split by "=".
    // --------------------------------------------------------
    class VL_API ini_file:public txt_file{
    public:
        /* retrieve values,usage:auto val=value(name)
         cast_t will auto cast types */
        const cast_t&	value(const char*)const;
        //test print in console
        virtual void	print()const;
    private:
        virtual bool	_parse(const std::string&);
        
        virtual bool	_make_buffer(std::string&);
        
        //clean '\t' and space before and after string
        void			_clean(std::string&,char='\t');
        
        std::map<std::string,cast_t>	_map;
    };
    // --------------------------------------------------------
};// namespace

#endif /* defined(__sanguo__fileutil__) */
