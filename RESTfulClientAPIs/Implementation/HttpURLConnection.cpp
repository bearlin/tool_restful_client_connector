//! @file HttpURLConnection.cpp
//!
//! @brief
//!

#include "HttpURLConnection.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h> //stat()

CHttpURLConnection::CHttpURLConnection() :
  iCurl(NULL)
  ,iRes(CURLE_OK)
  ,iUrl("")
  ,iFdPUT(NULL)
  ,iHeaderList(NULL)
{
}

CHttpURLConnection::~CHttpURLConnection()
{
  /* always cleanup */
  if (NULL != iCurl)
  {
    curl_easy_cleanup(iCurl);
    iCurl = NULL;
  }

  if (NULL != iHeaderList)
  {
    curl_slist_free_all(iHeaderList); /* free the list again */
    iHeaderList = NULL;
  }

  // Close previous file.
  if (NULL != iFdPUT)
  {
    if (0 != fclose(iFdPUT))  /* close the local file */
    {
      perror("fclose");
    }
    iFdPUT = NULL;
  }
}

bool CHttpURLConnection::OpenConnection(std::string aUrl)
{
  std::cout<< "CHttpURLConnection::OpenConnection()" <<std::endl;
  std::cout<< "aUrl: " << aUrl.c_str() <<std::endl;
  iUrl = aUrl;

  iRes = curl_global_init(CURL_GLOBAL_ALL);
  if(0 != iRes)
  {
    std::cout<< "curl_global_init() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  iCurl = curl_easy_init();
  if(NULL == iCurl)
  {
    std::cout<< "curl_easy_init() failed" <<std::endl;
    return false;
  }

  iRes = curl_easy_setopt(iCurl, CURLOPT_URL, iUrl.c_str());
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  return true;
}

bool CHttpURLConnection::Perform()
{
  std::cout<< "CHttpURLConnection::Perform()" <<std::endl;
  if (NULL == iCurl)
  {
    std::cout<< "CHttpURLConnection::Perform() failed because (NULL == iCurl) !!!" <<std::endl;
    return false;
  }

  /* Perform the request, res will get the return code */
  iRes = curl_easy_perform(iCurl);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_perform() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  return true;
}

// Callback functions.
size_t CHttpURLConnection::write_data_to_file(void* ptr, size_t size, size_t nmemb, void* userdata)
{
  int written = fwrite(ptr, size, nmemb, (FILE*)userdata);
  return written;
}

size_t CHttpURLConnection::write_data_to_memory(void* ptr, size_t size, size_t nmemb, void* userdata)
{
  size_t realsize = size * nmemb;
  struct TMemoryStructGET *mem = (struct TMemoryStructGET*)userdata;

  mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
  if (mem->memory == NULL)
  {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), ptr, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

size_t CHttpURLConnection::read_data_from_file(void* ptr, size_t size, size_t nmemb, void* userdata)
{
  size_t retcode;
  //curl_off_t nread;

  /* in real-world cases, this would probably get this data differently
  as this fread() stuff is exactly what the library already would do
  by default internally */
  retcode = fread(ptr, size, nmemb, (FILE*)userdata);

  //nread = (curl_off_t)retcode;
  //fprintf(stderr, "*** We read %" CURL_FORMAT_CURL_OFF_T " bytes from file\n", nread);
  return retcode;
}

size_t CHttpURLConnection::read_data_from_memory(void *ptr, size_t size, size_t nmemb, void *userdata)
{
  //http://curl.haxx.se/libcurl/c/post-callback.html
  if (userdata)
  {
    //printf("ptr:0x%lx, size:%d, nmemb:%d\n", (long)ptr, size, nmemb);
    struct TMemoryStructPOSTPUT* memoryChunk = (struct TMemoryStructPOSTPUT*)userdata;
    //printf("memoryChunk->data:0x%lx, memoryChunk->size:%d\n", (long)memoryChunk->data, memoryChunk->size);
    if (size*nmemb < 1)
      return 0;

    if (memoryChunk->size)
    {
      *(char*)ptr = memoryChunk->data[0];  /* copy one single byte */
      memoryChunk->data++;                 /* advance pointer */
      memoryChunk->size--;                /* less data left */
      return 1;                               /* we return 1 byte at a time! */
    }
  }

  return 0;                                   /* no more data left to deliver */
}

bool CHttpURLConnection::HttpSetFollowRedirection(bool aFollow)
{
  std::cout<< "CHttpURLConnection::HttpSetFollowRedirection:" << aFollow <<std::endl;

  /* Tell libcurl to follow redirection */
  iRes = curl_easy_setopt(iCurl, CURLOPT_FOLLOWLOCATION, ((true == aFollow)? 1L : 0L));
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  return true;
}

bool CHttpURLConnection::HttpSetVerbose(bool aVerbose)
{
  /* get verbose debug output please */
  iRes = curl_easy_setopt(iCurl, CURLOPT_VERBOSE, ((true == aVerbose)? 1L : 0L));
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  return true;
}

bool CHttpURLConnection::HttpSetOutputHeaderBodyToSeparateFiles(FILE *aHeaderFd, FILE *aBodyFd)
{
  // send all data to this function
  iRes = curl_easy_setopt(iCurl, CURLOPT_WRITEFUNCTION, CHttpURLConnection::write_data_to_file);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  if (NULL != aHeaderFd)
  {
    /* we want the headers be written to this file handle */
    iRes = curl_easy_setopt(iCurl,   CURLOPT_WRITEHEADER, aHeaderFd);
    if(CURLE_OK != iRes)
    {
      std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
      return false;
    }
  }

  if (NULL != aBodyFd)
  {
    /* we want the body be written to this file handle instead of stdout */
    iRes = curl_easy_setopt(iCurl,   CURLOPT_WRITEDATA, aBodyFd);
    if(CURLE_OK != iRes)
    {
      std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
      return false;
    }
  }

  return true;
}

bool CHttpURLConnection::HttpSetOutputHeaderBodyToSeparateMemorys(struct TMemoryStructGET* aHeaderChunk, struct TMemoryStructGET* aBodyChunk)
{
  // send all data to this function
  iRes = curl_easy_setopt(iCurl, CURLOPT_WRITEFUNCTION, CHttpURLConnection::write_data_to_memory);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  if (NULL != aHeaderChunk)
  {
    /* we want the headers be written to this file handle */
    iRes = curl_easy_setopt(iCurl,   CURLOPT_WRITEHEADER, aHeaderChunk);
    if(CURLE_OK != iRes)
    {
      std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
      return false;
    }
  }

  if (NULL != aBodyChunk)
  {
    /* we want the body be written to this file handle instead of stdout */
    iRes = curl_easy_setopt(iCurl,   CURLOPT_WRITEDATA, aBodyChunk);
    if(CURLE_OK != iRes)
    {
      std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
      return false;
    }
  }

  return true;
}

bool CHttpURLConnection::HttpSetPUTFromFile(const char* aFilePath)
{
  if (NULL == aFilePath)
  {
    std::cout<< "Error: HttpSetPUTFromFile() input error" <<std::endl;
    return false;
  }

  // Get the file size of the local file
  struct stat file_info;
  if (-1 == stat(aFilePath, &file_info))
  {
    perror("stat");
    return false;
  }

  // Close previous file.
  if (NULL != iFdPUT)
  {
    if (0 != fclose(iFdPUT))  /* close the local file */
    {
      perror("fclose");
      return false;
    }
    iFdPUT = NULL;
  }

  // Get a FILE* of the same file, could also be made with fdopen() from the previous descriptor.
  iFdPUT = fopen(aFilePath, "rb");
  if (NULL == iFdPUT)
  {
    perror("fopen");
    return false;
  }

  // enable uploading
  iRes = curl_easy_setopt(iCurl, CURLOPT_UPLOAD, 1L);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  /* HTTP PUT please */
  iRes = curl_easy_setopt(iCurl, CURLOPT_PUT, 1L);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  // we want to use our own read function
  iRes = curl_easy_setopt(iCurl, CURLOPT_READFUNCTION, CHttpURLConnection::read_data_from_file);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  // now specify which file to upload
  iRes = curl_easy_setopt(iCurl, CURLOPT_READDATA, iFdPUT);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  // provide the size of the upload, we specicially typecast the value to curl_off_t since we must be sure to use the correct data size
  iRes = curl_easy_setopt(iCurl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_info.st_size);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  return true;
}

bool CHttpURLConnection::HttpSetPUTFromBuffer(struct TMemoryStructPOSTPUT& memoryChunk)
{
  // enable uploading
  iRes = curl_easy_setopt(iCurl, CURLOPT_UPLOAD, 1L);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  /* HTTP PUT please */
  iRes = curl_easy_setopt(iCurl, CURLOPT_PUT, 1L);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  /* we want to use our own read function */
  iRes = curl_easy_setopt(iCurl, CURLOPT_READFUNCTION, CHttpURLConnection::read_data_from_memory);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  /* pointer to pass to our read function */
  iRes = curl_easy_setopt(iCurl, CURLOPT_READDATA, &memoryChunk);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  // provide the size of the upload, we specicially typecast the value to curl_off_t since we must be sure to use the correct data size
  iRes = curl_easy_setopt(iCurl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)memoryChunk.size);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  return true;
}

bool CHttpURLConnection::HttpSetPOSTFromBuffer(struct TMemoryStructPOSTPUT& memoryChunk)
{
  /* Now specify we want to POST data */
  iRes = curl_easy_setopt(iCurl, CURLOPT_POST, 1L);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  /* we want to use our own read function */
  iRes = curl_easy_setopt(iCurl, CURLOPT_READFUNCTION, CHttpURLConnection::read_data_from_memory);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  /* pointer to pass to our read function */
  iRes = curl_easy_setopt(iCurl, CURLOPT_READDATA, &memoryChunk);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  /*
    If you use POST to a HTTP 1.1 server, you can send data without knowing
    the size before starting the POST if you use chunked encoding. You
    enable this by adding a header like "Transfer-Encoding: chunked" with
    CURLOPT_HTTPHEADER. With HTTP 1.0 or without chunked transfer, you must
    specify the size in the request.
  */
#ifdef USE_CHUNKED
  {
    struct curl_slist *chunk = NULL;

    chunk = curl_slist_append(chunk, "Transfer-Encoding: chunked");
    res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    /* use curl_slist_free_all() after the *perform() call to free this
       list again */
  }
#else
  /* Set the expected POST size. If you want to POST large amounts of data, consider CURLOPT_POSTFIELDSIZE_LARGE */
  // If you want to post data to the server without letting libcurl do a strlen() to measure the data size, this option must be used.
  // When this option is used you can post fully binary data, which otherwise is likely to fail.
  // If this size is set to -1, the library will use strlen() to get the size.
  iRes = curl_easy_setopt(iCurl, CURLOPT_POSTFIELDSIZE, memoryChunk.size);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }
#endif

#ifdef DISABLE_EXPECT
  /*
    Using POST with HTTP 1.1 implies the use of a "Expect: 100-continue"
    header.  You can disable this header with CURLOPT_HTTPHEADER as usual.
    NOTE: if you want chunked transfer too, you need to combine these two
    since you can only set one list of headers with CURLOPT_HTTPHEADER. */

  /* A less good option would be to enforce HTTP 1.0, but that might also
     have other implications. */
  {
    struct curl_slist *chunk = NULL;

    chunk = curl_slist_append(chunk, "Expect:");
    res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    /* use curl_slist_free_all() after the *perform() call to free this
       list again */
  }
#endif

  return true;
}

bool CHttpURLConnection::HttpSetTimeout(long aSeconds)
{
  /* get verbose debug output please */
  iRes = curl_easy_setopt(iCurl, CURLOPT_TIMEOUT, aSeconds);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  return true;
}

bool CHttpURLConnection::HttpSetTimeoutMs(long aMilliseconds)
{
  /* get verbose debug output please */
  iRes = curl_easy_setopt(iCurl, CURLOPT_TIMEOUT_MS, aMilliseconds);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  return true;
}

bool CHttpURLConnection::HttpSetHeader(const char* aHeaderAccept, const char* aHeaderContentType, const char* aExpect, const char* aCustom)
{
  //http://curl.haxx.se/libcurl/c/curl_easy_setopt.html#CURLOPTHTTPHEADER
  //http://stackoverflow.com/questions/19396696/415-unsupported-media-type-post-json-to-odata-service-in-lightswitch-2012

  // Update and append additional POST header.
  if (NULL != iHeaderList)
  {
    curl_slist_free_all(iHeaderList); /* free the list again */
    iHeaderList = NULL;
  }

  if (NULL != aHeaderAccept)
  {
    iHeaderList = curl_slist_append(iHeaderList, aHeaderAccept);
  }

  if (NULL != aHeaderContentType)
  {
    iHeaderList = curl_slist_append(iHeaderList, aHeaderContentType);
  }

  if (NULL != aExpect)
  {
    iHeaderList = curl_slist_append(iHeaderList, aExpect);
  }

  if (NULL != aCustom)
  {
    iHeaderList = curl_slist_append(iHeaderList, aCustom);
  }

  iRes = curl_easy_setopt(iCurl, CURLOPT_HTTPHEADER, iHeaderList);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  return true;
}

bool CHttpURLConnection::HttpSetHeaderFromMap(std::map<std::string, std::string>& aHeadersMap)
{
  //Pass a empty map will reset back to no custom headers.
  if (0 == aHeadersMap.size())
  {
    iRes = curl_easy_setopt(iCurl, CURLOPT_HTTPHEADER, NULL);
    if(CURLE_OK != iRes)
    {
      std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
      return false;
    }
    
    return true;
  }

  // Map is not empty, set this new header.
  // Clear previous list.
  if (NULL != iHeaderList)
  {
    curl_slist_free_all(iHeaderList); /* free the list again */
    iHeaderList = NULL;
  }

  std::string headerStr("");
  for (std::map<std::string, std::string>::iterator it=aHeadersMap.begin(); it!=aHeadersMap.end(); ++it)
  {
    headerStr = it->first + ": " + it->second;
    iHeaderList = curl_slist_append(iHeaderList, headerStr.c_str());
  }

  iRes = curl_easy_setopt(iCurl, CURLOPT_HTTPHEADER, iHeaderList);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  return true;
}

bool CHttpURLConnection::HttpGetEffectiveUrl(char** aUrl)
{
  iRes = curl_easy_getinfo(iCurl, CURLINFO_EFFECTIVE_URL, aUrl);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  return true;
}

bool CHttpURLConnection::HttpGetResponseCode(long* aRespcode)
{
  iRes = curl_easy_getinfo(iCurl, CURLINFO_RESPONSE_CODE, aRespcode);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  return true;
}

bool CHttpURLConnection::HttpGetRedirectCount(long* aRedirectCnt)
{
  iRes = curl_easy_getinfo(iCurl, CURLINFO_REDIRECT_COUNT, aRedirectCnt);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  return true;
}

bool CHttpURLConnection::HttpGetRedirectUrl(char** aUrl)
{
  iRes = curl_easy_getinfo(iCurl, CURLINFO_REDIRECT_URL, aUrl);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  return true;
}

bool CHttpURLConnection::HttpGetContentType(char** aContentType)
{
  iRes = curl_easy_getinfo(iCurl, CURLINFO_CONTENT_TYPE, aContentType);
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

  return true;
}

char* CHttpURLConnection::UrlEncoding(const char* aStr, int aLength)
{
  //http://stackoverflow.com/questions/154536/encode-decode-urls-in-c
  char* encodedStr = curl_easy_escape(iCurl, aStr, aLength);
  return encodedStr;
}

char* CHttpURLConnection::UrlDecoding(const char* aStr, int aInLength, int* aOutLength)
{
  //http://stackoverflow.com/questions/154536/encode-decode-urls-in-c
  char* decodedStr = curl_easy_unescape(iCurl, aStr, aInLength, aOutLength);
  return decodedStr;
}

void CHttpURLConnection::UrlFreeEncodeDecodeStringBuffer(char* aStr)
{
  // Reclaim memory that has been obtained through a libcurl call.
  if (aStr)
    curl_free(aStr);
}

int CHttpURLConnection::getRespondCode()
{
  return iRes;
}

