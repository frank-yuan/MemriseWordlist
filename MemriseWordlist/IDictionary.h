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
    virtual string GetExplanations(string word) = 0;
    virtual string GetPronunciation(string word) = 0;
};

#endif
