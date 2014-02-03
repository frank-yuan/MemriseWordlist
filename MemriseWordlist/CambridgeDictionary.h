//
//  CambridgeDictionary.h
//  MemriseWordlist
//
//  Created by YuanXuan on 2/3/14.
//  Copyright (c) 2014 FrankY. All rights reserved.
//

#ifndef __MemriseWordlist__CambridgeDictionary__
#define __MemriseWordlist__CambridgeDictionary__

#include <iostream>
#include "IDictionary.h"

using namespace std;

class CambridgeDictionary : public IDictionary
{
public:
    virtual string GetExplanations(string word);
    virtual string GetPronunciation(string word);

};
#endif /* defined(__MemriseWordlist__CambridgeDictionary__) */
