//
//  CambridgeDictionary.cpp
//  MemriseWordlist
//
//  Created by YuanXuan on 2/3/14.
//  Copyright (c) 2014 FrankY. All rights reserved.
//

#include <libxml/HTMLparser.h>
#include "CambridgeDictionary.h"
#include "Util.h"


#ifdef _MSC_VER
#define COMPARE(a, b) (!stricmp((a), (b)))
#else
#define COMPARE(a, b) (!strcasecmp((a), (b)))
#endif

//
//  libxml callback context structure
//
enum ParseType
{
    PT_EXPLANATION,
    PT_PRONUNCIATION
};
struct Context
{
    Context(ParseType ptype):
        isInSpan(false),
        spanLevel(0),
        index(0),
        stringVal(""),
        type(ptype)
    { }
    int     spanLevel;
    bool isInSpan;
    int  index;
    std::string stringVal;
    ParseType type;
};
//
//  libxml start element callback function
//

static const string KEY = "class";
static const string EXPVALUE = "def";
static const string PRONVALUE = "pron";


static void StartElement(void *voidContext,
                         const xmlChar *name,
                         const xmlChar **attributes)
{
    Context *context = (Context *)voidContext;
    
    if (COMPARE((char *)name, "span"))
    {
        if (context->spanLevel > 0)
        {
            ++context->spanLevel;
        }
        else if (attributes)
        {
            std::string targetValue = context->type == PT_PRONUNCIATION? PRONVALUE : EXPVALUE;
            std::string key, value;
            while (NULL != attributes && NULL != attributes[0]) {
                key = (const char*)attributes[0];
                value = (const char*)attributes[1];
                if (!key.compare(KEY) && !value.compare(targetValue))
                {
                    context->spanLevel = 1;
                }
                attributes = &attributes[2];
            }
        }
        
    }
    //(void) attributes;
}

//
//  libxml end element callback function
//

static void EndElement(void *voidContext,
                       const xmlChar *name)
{
    Context *context = (Context *)voidContext;
    
    if (COMPARE((char *)name, "span") && context->spanLevel > 0)
    {
        --context->spanLevel;
    }
}

//
//  Text handling helper function
//

//static void handleCharacters(Context *context,
//                             const xmlChar *chars,
//                             int length)
//{
//    if (context->spanLevel > 0)
//        context->stringVal.append((char *)chars, length);
//}

//
//  libxml PCDATA callback function
//

static void Characters(void *voidContext,
                       const xmlChar *chars,
                       int length)
{
    Context *context = (Context *)voidContext;
    if (context->spanLevel > 0)
        context->stringVal.append((char *)chars, length);
//    handleCharacters(context, chars, length);
}

//
//  libxml CDATA callback function
//

//static void cdata(void *voidContext,
//                  const xmlChar *chars,
//                  int length)
//{
//    Context *context = (Context *)voidContext;
//    
//    if (context->spanLevel > 0)
//        context->stringVal.append((char *)chars, length);
//}

//
//  libxml SAX callback structure
//

static htmlSAXHandler saxHandler =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    StartElement,
    EndElement,
    NULL,
    Characters,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    Characters,
    NULL
};

static void parseHtml(const std::string &html,
                      std::string &stringVal,
                      ParseType type)
{
    htmlParserCtxtPtr ctxt;
    Context context(type);
    
    ctxt = htmlCreatePushParserCtxt(&saxHandler, &context, "", 0, "",
                                    XML_CHAR_ENCODING_NONE);
    
    htmlParseChunk(ctxt, html.c_str(), html.size(), 0);
    htmlParseChunk(ctxt, "", 0, 1);
    
    htmlFreeParserCtxt(ctxt);
    
    stringVal = context.stringVal;
}

string CambridgeDictionary::GetExplanations()
{

    std::string explanation;
 
    if (m_queryResult.length() <= 0)
    {
        return "";
    }
    parseHtml(m_queryResult, explanation, PT_EXPLANATION);

    // replace word in explanation with *
    size_t found;
    found = explanation.find(m_word);
    while (found!=string::npos){
        explanation.replace(found, m_word.length(), "****");
        found = explanation.find(m_word);
    };
    
    return explanation;
}
string CambridgeDictionary::GetPronunciation()
{
    
    std::string pron;
    
    if (m_queryResult.length() <= 0)
    {
        return "";
    }
    parseHtml(m_queryResult, pron, PT_PRONUNCIATION);
    return pron;
}
