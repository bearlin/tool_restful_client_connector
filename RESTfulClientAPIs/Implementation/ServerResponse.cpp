//! @file ServerResponse.cpp
//!
//! @brief 
//!

#include "ServerResponse.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>

CServerResponse::CServerResponse(int aResponseCode, std::string aHeaders, const char* aBodyBuffer, size_t aBodySize) :
  iResponseCode(aResponseCode)
  ,iHeaders(aHeaders)
  ,iBodyBuffer(NULL)
  ,iBodySize(aBodySize)
{  
  // we should keep the body in another memory buffer.
  if (0 != aBodySize)
  {
    iBodyBuffer = new char[aBodySize];
    memset(iBodyBuffer, '\0', aBodySize);
    memcpy(iBodyBuffer, aBodyBuffer, aBodySize);
  }
}

CServerResponse::~CServerResponse()
{
  if (iBodyBuffer)
    delete []iBodyBuffer;
}

int CServerResponse::getResponseCode() 
{
  return iResponseCode;
}

std::string CServerResponse::getHeader() 
{
  return iHeaders;
}

void CServerResponse::getBody(char** aBodyBuffer, size_t* aBodySize) 
{
  *aBodyBuffer = iBodyBuffer;
  *aBodySize = iBodySize;
}

char* CServerResponse::getBodyData() 
{
  return iBodyBuffer;
}

size_t CServerResponse::getBodySize() 
{
  return iBodySize;
}

std::string CServerResponse::toString() 
{
  std::string bodyStr(iBodyBuffer, iBodySize);

  return std::string("header:\n")+getHeader()+"\n"+
         std::string("body:\n")+bodyStr+"\n";
}

