//
//  BaseDictionary.cpp
//  Memrisem_wordlist
//
//  Created by YuanXuan on 2/12/14.
//  Copyright (c) 2014 FrankY. All rights reserved.
//

#include "BaseDictionary.h"
#include "Util.h"
bool BaseDictionary::Query(string word)
{
    m_word = word;
    if (m_word.length() == 0 || GetURL().length() == 0)
        return false;
    std::string htmlBuffer;
    
    string urlDelimiter = GetURLDelimiter();
    
    if (urlDelimiter.length() > 0)
    {
//        std::replace_if(m_word.begin() , m_word.end() ,
//                    [] (const char& c) { return std::isspace(c) ;},'+');
        int pos;
        
        while ((pos = m_word.find(" ")) != std::string::npos)
            m_word.replace(pos, 1, urlDelimiter);
    }
    std::string url = GetURL();
    url += m_word;
    return (GetHTMLByURL(url, m_queryResult));
}