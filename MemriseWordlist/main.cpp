//
//  main.cpp
//  MemriseWordlist
//
//  Created by YuanXuan on 2/2/14.
//  Copyright (c) 2014 FrankY. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <libxml/xpath.h>
#include "ezOptionParser.hpp"
#include "MemriseExportFormater.h"
#include "CambridgeDictionary.h"

using namespace ez;
static const char* usage = "Usage: %s <words filename>\n";

std::string& rtrim(std::string& str) {
    size_t endpos = str.find_last_not_of("\r\n");
    if(endpos != std::string::npos) {
        str.substr(0,endpos+1).swap(str);
    }
    return str;
}
int main(int argc, const char * argv[])
{

    ezOptionParser opt;
    if (argc != 2)
    {
        fprintf(stderr, usage, argv[0]);
        
        exit(EXIT_FAILURE);
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
    unsigned line_count = std::count(std::istreambuf_iterator<char>(ifile),
               std::istreambuf_iterator<char>(), '\n');

    fprintf(stdout, "%d words needs to be quried.\n", line_count);
    ifile.seekg(0);
    IDictionary* dic = new CambridgeDictionary();
    IExportFormater* formatExporter = new MemriseExportFormater();
    std::string strLine;
    try{
        int i = 0;
//        while (ifile >> strLine)
        while(std::getline(ifile, strLine))
        {
            strLine = rtrim(strLine);
            fprintf(stdout, "[%d/%d]%s..........", ++i, line_count, strLine.c_str());
            dic->Query(strLine);
            string explanation = dic->GetExplanations();
            if (explanation.length() > 0)
            {
                ofile << formatExporter->GetExportLine(strLine, explanation) << std::endl;
                fprintf(stdout, "[SUCCESS!]\n");
            }
            else
            {
                fprintf(stdout, "[FAILED]\n");
            }
        }
    } catch (int e) {
        std::cout << "Write file error with error code:" << e;
       
    }
    ofile.close();
    
    delete dic;
    delete formatExporter;
    
    return 0;
}

