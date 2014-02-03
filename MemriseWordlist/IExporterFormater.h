//
//  IExporter.h
//  MemriseWordlist
//
//  Created by YuanXuan on 2/3/14.
//  Copyright (c) 2014 FrankY. All rights reserved.
//

#ifndef MemriseWordlist_IExporter_h
#define MemriseWordlist_IExporter_h

#include <string>
using namespace std;

class IExportFormater
{
public:
    IExportFormater(){};
    virtual ~IExportFormater(){};
    virtual string GetExportLine(string word, string explanation, string pronunciation = "") = 0;
};


#endif
