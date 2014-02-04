//
//  CambridgeDictionary.cpp
//  MemriseWordlist
//
//  Created by YuanXuan on 2/3/14.
//  Copyright (c) 2014 FrankY. All rights reserved.
//
#include <curl/curl.h>
#include "CambridgeDictionary.h"

string CambridgeDictionary::GetExplanations(string word)
{
    CURL *curl;
    CURLcode res;
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
        /* example.com is redirected, so we tell libcurl to follow redirection */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    return "cambridge university";
}
string CambridgeDictionary::GetPronunciation(string word)
{
    return "pronunciation";
}