//
//  BaseDictionary.h
//  MemriseWordlist
//
//  Created by YuanXuan on 2/12/14.
//  Copyright (c) 2014 FrankY. All rights reserved.
//

#ifndef __MemriseWordlist__BaseDictionary__
#define __MemriseWordlist__BaseDictionary__

#include <iostream>

#include "IDictionary.h"

using namespace std;

class BaseDictionary : public IDictionary
{
protected:
    string m_word;
    string m_queryResult;
    
    virtual string GetURLDelimiter(){return "%20";};
    virtual string GetURL(){return "";}
public:
    virtual ~BaseDictionary(){};
    virtual bool   Query(string word);
    virtual string GetExplanations() = 0;
    virtual string GetPronunciation() = 0;
};
#endif /* defined(__MemriseWordlist__BaseDictionary__) */
