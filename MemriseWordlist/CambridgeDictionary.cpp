//
//  CambridgeDictionary.cpp
//  MemriseWordlist
//
//  Created by YuanXuan on 2/3/14.
//  Copyright (c) 2014 FrankY. All rights reserved.
//
#include <curl/curl.h>
#include "CambridgeDictionary.h"
#include "htmltitle.cpp"


#ifdef _MSC_VER
#define COMPARE(a, b) (!stricmp((a), (b)))
#else
#define COMPARE(a, b) (!strcasecmp((a), (b)))
#endif

//
//  libxml callback context structure
//

struct Context
{
    Context():
        isInSpan(false),
        spanLevel(0),
        index(0),
        stringVal("")
    { }
    int     spanLevel;
    bool isInSpan;
    int  index;
    std::string stringVal;
};
//
//  libxml start element callback function
//

static const string KEY = "class";
static const string VALUE = "def";


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
            std::string key, value;
            while (NULL != attributes && NULL != attributes[0]) {
                key = (const char*)attributes[0];
                value = (const char*)attributes[1];
                if (!key.compare(KEY) && !value.compare(VALUE))
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

static void handleCharacters(Context *context,
                             const xmlChar *chars,
                             int length)
{
    if (context->spanLevel > 0)
        context->stringVal.append((char *)chars, length);
}

//
//  libxml PCDATA callback function
//

static void Characters(void *voidContext,
                       const xmlChar *chars,
                       int length)
{
    Context *context = (Context *)voidContext;
    
    handleCharacters(context, chars, length);
}

//
//  libxml CDATA callback function
//

static void cdata(void *voidContext,
                  const xmlChar *chars,
                  int length)
{
    Context *context = (Context *)voidContext;
    
    handleCharacters(context, chars, length);
}

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
    cdata,
    NULL
};

static void parseHtml(const std::string &html,
                      std::string &stringVal)
{
    htmlParserCtxtPtr ctxt;
    Context context;
    
    ctxt = htmlCreatePushParserCtxt(&saxHandler, &context, "", 0, "",
                                    XML_CHAR_ENCODING_NONE);
    
    htmlParseChunk(ctxt, html.c_str(), html.size(), 0);
    htmlParseChunk(ctxt, "", 0, 1);
    
    htmlFreeParserCtxt(ctxt);
    
    stringVal = context.stringVal;
}


string CambridgeDictionary::GetExplanations(string word)
{
    std::string htmlBuffer;
    std::string explanation;
    
    std::replace_if(word.begin() , word.end() ,
                    [] (const char& c) { return std::isspace(c) ;},'+');
    std::string url("dictionary.cambridge.org/search/british/direct/?q=");
    url += word;
    if (GetHTMLByURL(url, htmlBuffer))
    {
        
        parseHtml(htmlBuffer, explanation);
    }
    return explanation;
}
string CambridgeDictionary::GetPronunciation(string word)
{
    return "pronunciation";
}