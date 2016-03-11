//
//  websocket_service.h
//  sanguo
//
//  Created by Vic Liu on 8/20/15.
//  Copyright (c) 2015 Vic Liu. All rights reserved.
//

#ifndef __sanguo__websocket_service__
#define __sanguo__websocket_service__

#include <memory>
#include <functional>

class websocket_service_impl;
class websocket_service {
public:
    void    run(unsigned short,std::function<void(size_t,const void*,size_t)>);
    void    send(size_t,const void*,size_t);
private:
    std::shared_ptr<websocket_service_impl> _impl;
};

#endif /* defined(__sanguo__websocket_service__) */
