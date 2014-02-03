//
//  MemriseExportFormater.h
//  MemriseWordlist
//
//  Created by YuanXuan on 2/3/14.
//  Copyright (c) 2014 FrankY. All rights reserved.
//

#ifndef __MemriseWordlist__MemriseExportFormater__
#define __MemriseWordlist__MemriseExportFormater__

#include <iostream>
#include "IExporterFormater.h"
class MemriseExportFormater : public IExportFormater
{
public:
    virtual string GetExportLine(string word, string explanation, string pronunciation = "");
};
#endif /* defined(__MemriseWordlist__MemriseExportFormater__) */
