//
//  main.cpp
//  MemriseWordlist
//
//  Created by YuanXuan on 2/2/14.
//  Copyright (c) 2014 FrankY. All rights reserved.
//


#include <iostream>
#include <libxml2/libxml/xpath.h>
#include "ezOptionParser.hpp"

using namespace ez;
static const char* helpStr = "usage: MemriseWorldlist <src filename> <dest filename>";

;int main(int argc, const char * argv[])
{

    ezOptionParser opt;
    if (argc <2)
    {
        std::cout << helpStr;
        return 0;
    }
    // insert code here...
  //  std::cout << "Hello, World!\n" << argc;
    return 0;
}

