//
//  utils.cpp
//  regex
//
//  Created by Vic Liu on 9/3/15.
//  Copyright (c) 2015 Vic Liu. All rights reserved.
//

#include "utilfwd.h"
#include <iostream>
#include <regex>

using namespace std;
namespace vl{

void split(vector<string>& lines,const string& buf){
    const char* _pattern="([^(?:\r\n)\n\r]+)(?:(?:\r\n)|\n|\r|$)";
    try{
        regex pattern(_pattern);
        auto beg = std::sregex_iterator(buf.begin(), buf.end(), pattern);
        auto end = std::sregex_iterator();
        for(auto i=beg;i!=end; ++i)
            lines.push_back((*i)[1]);
    }catch(regex_error e){
        cout<<e.what()<<endl;
    }
}

bool parse_ini(map<string,string>& dict,const string& line){
    const char* ini_pattern=
    "(?!\\s*#*$)"                                   // Don't match empty last value,# line.
    "\\s*"                                          // Strip whitespace before value.
    "([^=]+)=([\\S\\s]*)"                           // Group key and value.
    "\\s*"                                          // Strip whitespace after value.
    "(?:(?:\r\n)|\n|\r|$)";                                     // Field ends on line end or EOS.
    
    try{
        regex pattern(ini_pattern);
        smatch match;
        if(regex_match(line,match,pattern)){
            dict[match[1]]=match[2];
            return true;
        }
    }catch(regex_error e){
        cout<<e.what()<<endl;
    }
    return false;
}

bool parse_csv(vector<string>& fields,const string& line,bool tab){
    const char* csv_pattern=
    "(?!\\s*$)"                                     // Don't match empty last value.
    "\\s*"                                          // Strip whitespace before value.
    "(?:"                                           // Group for value alternatives.
        "'([^']*(?:[\\S\\s][^']*)*?)'"              // Either $1: Single quoted string,
        "|\"([^\"]*(?:[\\S\\s][^\"]*)*?)\""         // or $2: Double quoted string,
        "|([^,'\"]*\\w[^,'\"]*)"                    // or $3: Non-comma, non-quote stuff.
    ")"                                             // End group of value alternatives.
    "\\s*"                                          // Strip whitespace after value.
    "(?:,|$)";                                      // Field ends on comma or EOS.
    
    const char* tab_pattern=
    "(?!\\s*$)"                                     // Don't match empty last value.
    "\\s*"                                          // Strip whitespace before value.
    "(?:"                                           // Group for value alternatives.
        "'([^']*(?:[\\S\\s][^']*)*?)'"              // Either $1: Single quoted string,
        "|\"([^\"]*(?:[\\S\\s][^\"]*)*?)\""         // or $2: Double quoted string,
        "|([^\t'\"]*\\w[^\t'\"]*)"                  // or $3: Non-comma, non-quote stuff.
    ")"                                             // End group of value alternatives.
    "\\s*"                                          // Strip whitespace after value.
    "(?:\t|$)";                                     // Field ends on comma or EOS.
    try{
        regex pattern(tab?tab_pattern:csv_pattern);
        auto beg = std::sregex_iterator(line.begin(), line.end(), pattern);
        auto end = std::sregex_iterator();
        for(auto i=beg;i!=end; ++i){
            auto& match=*i;
            auto empty=true;
            for(auto it=++match.begin(),iend=match.end();it!=iend;++it)
                if(it->length()>0){
                    fields.push_back(*it);
                    empty=false;
                    break;
                }
            if(empty)fields.push_back("");
        }
    }catch(regex_error e){
        cout<<e.what()<<endl;
        return false;
    }
    return true;
}
};
