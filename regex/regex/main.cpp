//
//  main.cpp
//  regex
//
//  Created by Vic Liu on 9/3/15.
//  Copyright (c) 2015 Vic Liu. All rights reserved.
//

#include <iostream>
#include <regex>
#include <map>
#include <vector>
using namespace std;

void split(vector<string>& lines,const string& buf){
    const char* _pattern="[^\n]+(?:\n|$)";
    try{
        regex pattern(_pattern);
        auto beg = std::sregex_iterator(buf.begin(), buf.end(), pattern);
        auto end = std::sregex_iterator();
        for(auto i=beg;i!=end; ++i)
            for(auto s:*i)lines.push_back(s);
    }catch(regex_error e){
        cout<<e.what()<<endl;
    }
}

bool parse_ini(map<string,string>& dict,const string& line){
    const char* ini_pattern=
    "(?!\\s*$)"                                     // Don't match empty last value.
    "\\s*"                                          // Strip whitespace before value.
    "([^=]+)=([\\S\\s]*)"                           // Group key and value.
    "\\s*"                                          // Strip whitespace after value.
    "(?:\n|$)";                                     // Field ends on line end or EOS.
    
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

bool parse_csv(vector<string>& fields,const string& line,bool tab=false){
    const char* csv_pattern=
    "(?!\\s*$)"                                     // Don't match empty last value.
    "\\s*"                                          // Strip whitespace before value.
    "(?:"                                           // Group for value alternatives.
        "'([^']*(?:[\\S\\s][^']*)*?)'"               // Either $1: Single quoted string,
        "|\"([^\"]*(?:[\\S\\s][^\"]*)*?)\""          // or $2: Double quoted string,
        "|([^,'\"]*\\w[^,'\"]*?)"                    // or $3: Non-comma, non-quote stuff.
    ")"                                             // End group of value alternatives.
    "\\s*"                                          // Strip whitespace after value.
    "(?:,|$)";                                      // Field ends on comma or EOS.
    
    const char* tab_pattern=
    "(?!\\s*$)"                                     // Don't match empty last value.
    "\\s*"                                          // Strip whitespace before value.
    "(?:"                                           // Group for value alternatives.
        "'([^']*(?:[\\S\\s][^']*)*?)'"               // Either $1: Single quoted string,
        "|\"([^\"]*(?:[\\S\\s][^\"]*)*?)\""          // or $2: Double quoted string,
        "|([^\t'\"]*\\w[^\t'\"]*?)"                    // or $3: Non-comma, non-quote stuff.
    ")"                                             // End group of value alternatives.
    "\\s*"                                          // Strip whitespace after value.
    "(?:\t|$)";                                      // Field ends on comma or EOS.
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

int main(int argc, const char * argv[]) {
    std::string str(" \\v\\i  cs \\,\"m\\\\ \" , e\" ,'ha\pp'y\\,latte'");
    
    str="\"hero_id\"\t\"name\"\t\"exp\"\t\"cClass\"\t\"cSubclass\"\t\"shieldtype\"\t\"life\"\t\"level\"\t\"skillid\"\t\"awaken\"";
    str="\"hero_id\",\"name\",\"exp\",\"cClass\",\"cSubclass\",\"shieldtype\",\"life\",\"level\",\"skillid\",\"awaken\"";
    vector<string> fields;
    if(parse_csv(fields,str,false)){
        for(auto& i:fields)cout<<i<<endl;
        cout<<endl;
    }

    str=" \\v\\i  cs \\\t\"m\\\\ \" \t e\" \t'ha\pp'y\\\tlatte'";
    fields.clear();
    if(parse_csv(fields,str,true)){
        for(auto& i:fields)cout<<i<<endl;
        cout<<endl;
    }
    
    str="\tk'e \y=v='\"alue";
    map<string,string> dict;
    if(parse_ini(dict,str)){
        auto m=dict.begin();
        cout<<m->first<<"=["<<m->second<<"]"<<endl;
        cout<<endl;
    }

    str="  111,1\n2,22\n\n33 33";
    fields.clear();
    split(fields,str);
    for(auto& i:fields)cout<<i;

    return 0;
}
