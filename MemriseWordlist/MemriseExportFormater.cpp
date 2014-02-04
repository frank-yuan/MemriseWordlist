//
//  MemriseExportFormater.cpp
//  MemriseWordlist
//
//  Created by YuanXuan on 2/3/14.
//  Copyright (c) 2014 FrankY. All rights reserved.
//

#include "MemriseExportFormater.h"
const static char delimiter = '|';
string MemriseExportFormater::GetExportLine(string word, string explanation, string pronunciation)
{
    return word + delimiter + explanation + delimiter + pronunciation;
}