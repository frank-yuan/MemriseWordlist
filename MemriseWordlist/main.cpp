//
//  main.cpp
//  MemriseWordlist
//
//  Created by YuanXuan on 2/2/14.
//  Copyright (c) 2014 FrankY. All rights reserved.
//


#include <iostream>
#include <string>
#include <libxml2/libxml/xpath.h>
#include "ezOptionParser.hpp"
#include "MemriseExportFormater.h"
#include "CambridgeDictionary.h"

using namespace ez;
static const char* usage = "usage: MemriseWorldlist <src filename>";


int mainMine(int argc, const char * argv[])
{

    ezOptionParser opt;
    if (argc <2)
    {
        std::cout << usage;
        return 0;
    }
    // check word flie name
    std::string srcFileName = argv[argc - 1];
    if (srcFileName.length() == 0)
    {
        std::cout << "Can not parse word file name.\n";
        std::cout << usage;
        return 0;
    }
    
    // check file exist
    std::ifstream ifile(srcFileName.c_str());
    if (!ifile)
    {
        std::cout << "Can not find input file.\n";
        std::cout << usage;
        return 0;
    }
    std::ofstream ofile((srcFileName + ".csv").c_str());
    if (!ofile)
    {
        std::cout << "Can not write to new file!";
        return 0;
    }
    
    IDictionary* dic = new CambridgeDictionary();
    IExportFormater* formatExporter = new MemriseExportFormater();
    std::string strLine;
    try{
        while (ifile >> strLine)
        {
            string explanation = formatExporter->GetExportLine(strLine, dic->GetExplanations(strLine));
            ofile << explanation << std::endl;
        }
    } catch (int e) {
        std::cout << "Write file error with error code:" << e;
       
    }
    ofile.close();
    
    delete dic;
    delete formatExporter;
    
    return 0;
}

