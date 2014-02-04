/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2011, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
// Get a web page, parse it with libxml.
//
// Written by Lars Nilsson
//
// GNU C++ compile command line suggestion (edit paths accordingly):
//
// g++ -Wall -I/opt/curl/include -I/opt/libxml/include/libxml2 htmltitle.cpp \
// -o htmltitle -L/opt/curl/lib -L/opt/libxml/lib -lcurl -lxml2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <curl/curl.h>
#include <libxml/HTMLparser.h>

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


//
//  Parse given (assumed to be) HTML text and return the title
//


//int main(int argc, char *argv[])
//{
//  CURL *conn = NULL;
//  CURLcode code;
//  std::string title;
//
//  // Ensure one argument is given
//
//  if (argc != 2)
//  {
//    fprintf(stderr, "Usage: %s <url>\n", argv[0]);
//
//    exit(EXIT_FAILURE);
//  }
//
//  curl_global_init(CURL_GLOBAL_DEFAULT);
//
//  // Initialize CURL connection
//
//  if (!init(conn, argv[1]))
//  {
//    fprintf(stderr, "Connection initializion failed\n");
//
//    exit(EXIT_FAILURE);
//  }
//
//  // Retrieve content for the URL
//
//  code = curl_easy_perform(conn);
//  curl_easy_cleanup(conn);
//
//  if (code != CURLE_OK)
//  {
//    fprintf(stderr, "Failed to get '%s' [%s]\n", argv[1], errorBuffer);
//
//    exit(EXIT_FAILURE);
//  }
//
//  // Parse the (assumed) HTML code
//
//  parseHtml(buffer, title);
//
//  // Display the extracted title
//
//  printf("Title: %s\n", title.c_str());
//
//  return EXIT_SUCCESS;
//}
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
    
    // Parse the (assumed) HTML code
    
    //parseHtml(buffer, title);
    
    // Display the extracted title
    
    //printf("Title: %s\n", title.c_str());
    
    return true;
}
