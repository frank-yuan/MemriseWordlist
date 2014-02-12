//
//  IDictionary.h
//  MemriseWordlist
//
//  Created by YuanXuan on 2/3/14.
//  Copyright (c) 2014 FrankY. All rights reserved.
//


#ifndef MemriseWordlist_IDictionary_h
#define MemriseWordlist_IDictionary_h

#include <string>
using namespace std;

class IDictionary
{
public:
    IDictionary(){};
    virtual ~IDictionary(){};
    virtual bool   Query(string word) = 0;
    virtual string GetExplanations() = 0;
    virtual string GetPronunciation() = 0;
};

#endif
