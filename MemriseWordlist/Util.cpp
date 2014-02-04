//
//  Util.cpp
//  MemriseWordlist
//
//  Created by YuanXuan on 2/4/14.
//  Copyright (c) 2014 FrankY. All rights reserved.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <curl/curl.h>

#include "Util.h"

//
//  Case-insensitive string comparison
//


//
//  libcurl variables for error strings and returned data

static char errorBuffer[CURL_ERROR_SIZE];
static std::string buffer;

//
//  libcurl write callback function
//

static int writer(char *data, size_t size, size_t nmemb,
                  std::string *writerData)
{
    if (writerData == NULL)
        return 0;
    
    writerData->append(data, size*nmemb);
    
    return size * nmemb;
}

//
//  libcurl connection initialization
//

static bool init(CURL *&conn,const char *url, std::string& htmlBuff)
{
    CURLcode code;
    
    conn = curl_easy_init();
    
    if (conn == NULL)
    {
        fprintf(stderr, "Failed to create CURL connection\n");
        
        exit(EXIT_FAILURE);
    }
    
    code = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, errorBuffer);
    if (code != CURLE_OK)
    {
        fprintf(stderr, "Failed to set error buffer [%d]\n", code);
        
        return false;
    }
    
    code = curl_easy_setopt(conn, CURLOPT_URL, url);
    if (code != CURLE_OK)
    {
        fprintf(stderr, "Failed to set URL [%s]\n", errorBuffer);
        
        return false;
    }
    
    code = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1L);
    if (code != CURLE_OK)
    {
        fprintf(stderr, "Failed to set redirect option [%s]\n", errorBuffer);
        
        return false;
    }
    
    code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, writer);
    if (code != CURLE_OK)
    {
        fprintf(stderr, "Failed to set writer [%s]\n", errorBuffer);
        
        return false;
    }
    
    code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, &htmlBuff);
    if (code != CURLE_OK)
    {
        fprintf(stderr, "Failed to set write data [%s]\n", errorBuffer);
        
        return false;
    }
    
    return true;
}

static bool GetHTMLByURL(const std::string& url, std::string& htmlBuffer)
{
    CURL *conn = NULL;
    CURLcode code;
    std::string title;
    
    // Ensure one argument is given
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    // Initialize CURL connection
    
    if (!init(conn, url.c_str(), htmlBuffer))
    {
        fprintf(stderr, "Connection initializion failed\n");
        
        //exit(EXIT_FAILURE);
        return false;
    }
    
    // Retrieve content for the URL
    
    code = curl_easy_perform(conn);
    curl_easy_cleanup(conn);
    
    if (code != CURLE_OK)
    {
        fprintf(stderr, "Failed to get '%s' [%s]\n", url.c_str(), errorBuffer);
        
        //exit(EXIT_FAILURE);
        return false;
    }
    
    
    return true;
}
