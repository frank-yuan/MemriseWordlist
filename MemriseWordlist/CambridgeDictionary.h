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
#include "BaseDictionary.h"

using namespace std;

class CambridgeDictionary : public BaseDictionary
{
protected:
    virtual string GetURLDelimiter(){return "+";};
    virtual string GetURL(){return "dictionary.cambridge.org/search/british/direct/?q=";}
public:

    virtual string GetExplanations();
    virtual string GetPronunciation();

};
#endif /* defined(__MemriseWordlist__CambridgeDictionary__) */
