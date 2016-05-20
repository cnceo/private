//
//  main.cpp
//  keye_server
//
//  Created by Vic Liu on 3/11/16.
//  Copyright © 2016 Vic Liu. All rights reserved.
//

#include <iostream>
//#include <keye/keye_pch.hpp>
#include <keye/keye_fwd.h>

using namespace keye;
using namespace std;

typedef std::allocator<char>			std_ax_t;
keye::logger log;

class Alloc:public htio_alloc{
public:
    //					Alloc():_kax(64<<20,_sax){}
    virtual void*	allocate(size_t _Count){return _sax.allocate(_Count);}
    virtual void	deallocate(void* _Ptr, size_t=0){_sax.deallocate((char*)_Ptr,0);}
private:
    std_ax_t		_sax;
    //	keye_ax_t		_kax;
};

class my_handler:public work_handler{
public:
    my_handler(Alloc& ax):_ax(ax){}
    virtual void	on_open(keye::sh_type&){
        log<<"client connected"<<endl;
        printf("client connected here");
    }
    virtual void	on_close(keye::sh_type&){}
    virtual void	on_read(keye::sh_type& sh,void* buf,size_t len){
        log<<"read "<<(int)len<<endl;
    }
    
private:
    Alloc&	_ax;
};

int main(int argc, const char * argv[]) {
    Alloc a;
    my_handler h(a);
    service s(h,a);
    s.run(12345);
    log<<"server started"<<endl;
    
    bool exit=false;
    while(!exit)
#ifdef WIN32
        Sleep(100000);
#else
    usleep(100000);
#endif
    /*
     switch(std::getchar()){
     case 'x':
     stop();
     exit=true;
     break;
     }
     */

    return 0;
}
