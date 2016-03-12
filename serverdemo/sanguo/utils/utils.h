//
//  utils.h
//  sanguo
//
//  Created by Vic Liu on 9/9/15.
//  Copyright (c) 2015 Vic Liu. All rights reserved.
//

#ifndef sanguo_utils_h
#define sanguo_utils_h

namespace vl{
    void split(std::vector<std::string>& lines,const std::string& buf);
    bool parse_ini(std::map<std::string,std::string>& dict,const std::string& line);
    bool parse_csv(std::vector<std::string>& fields,const std::string& line,bool tab=false);
};

#endif
