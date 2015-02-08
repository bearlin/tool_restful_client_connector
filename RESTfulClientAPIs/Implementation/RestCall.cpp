//! @file RestCall.cpp
//!
//! @brief 
//!

#include "RestCall.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>

const long KDEFAULT_TIMEOUT_NEVER = 0; //CURL: Default timeout is 0 (zero) which means it never times out.
const long KDEFAULT_CONNECT_TIMEOUT_MILLIS = 15*1000L;
const long KDEFAULT_READ_TIMEOUT_MILLIS = 30*1000L;

CRestCall::CRestCall() : 
  iUrl("")
  ,iResource(NULL)
  ,iReadTimeout(KDEFAULT_READ_TIMEOUT_MILLIS)
  ,iMethod(EGET)
  ,iBody("")
  ,iAlternativeServerPath("")
{
  iHeaders.clear();
}

CRestCall::~CRestCall() {;}

CRestCall& CRestCall::to(CRestResource* aResource)
{
  // Create a new static instance
  // Guaranteed to be lazy initialized
  // Guaranteed that it will be destroyed correctly
  static CRestCall instanceRes;

  instanceRes.reset();
  instanceRes.iResource = aResource;
  
  return instanceRes;
}

CRestCall& CRestCall::to(std::string aUrl)
{
  // Create a new static instance
  // Guaranteed to be lazy initialized
  // Guaranteed that it will be destroyed correctly
  static CRestCall instanceUrl;

  instanceUrl.reset();
  instanceUrl.iUrl = aUrl;

  return instanceUrl;
}

CRestCall& CRestCall::withReadTimeout(long aReadTimeout)
{
  iReadTimeout = aReadTimeout;
  
  return *this;
}

CRestCall& CRestCall::withHeaders(std::map<std::string, std::string>& aHeaders)
{
  iHeaders = aHeaders;

  return *this;
}

CRestCall& CRestCall::withHeader(std::string aHeader, std::string aValue)
{
  iHeaders.insert(std::pair<std::string, std::string>(aHeader, aValue));
  
  return *this;
}

CRestCall& CRestCall::withMethod(THttpMethod aMethod)
{
  iMethod = aMethod;

  return *this;
}

CRestCall& CRestCall::withBody(std::string aBody)
{
  if (iMethod != EPUT && iMethod != EPOST) 
  {
    throw std::invalid_argument("You can only set a body if the request method is PUT or POST");
  }

  iBody = aBody;

  return *this;
}


CRestCall& CRestCall::withAlternativeServerPath(std::string aAlternativeServerPath)
{
  if (iResource == NULL) 
  {
    throw std::invalid_argument("Alternative server path can only be used in conjunction with a RestResource");
  }

  iAlternativeServerPath = aAlternativeServerPath;

  return *this;
}

std::string& CRestCall::getUrl()
{
  return iUrl;
}

CRestResource* CRestCall::getResource()
{
  return iResource;
}

long& CRestCall::getReadTimeout()
{
  return iReadTimeout;
}

std::map<std::string, std::string>& CRestCall::getHeaders()
{
  return iHeaders;
}

THttpMethod& CRestCall::getMethod()
{
  return iMethod;
}

std::string& CRestCall::getBody()
{
  return iBody;
}

std::string& CRestCall::getAlternativeServerPath()
{
  return iAlternativeServerPath;
}

void CRestCall::reset()
{
  iUrl = "";
  iResource = NULL;
  iReadTimeout = KDEFAULT_READ_TIMEOUT_MILLIS;
  iMethod = EGET;
  iHeaders.clear();
  iBody = "";
  iAlternativeServerPath = "";
}

std::string CRestCall::toString() 
{
  std::stringstream convert;
  convert<<getReadTimeout();
  std::string timeout = convert.str();

  std::string headerStr("");
  std::map<std::string, std::string>& headeMap = getHeaders();
  for (std::map<std::string, std::string>::iterator it=headeMap.begin(); it!=headeMap.end(); ++it)
  {
    headerStr += "\t" + it->first + ": " + it->second +"\n";
  }

  std::string methodStr;
  if (EGET == getMethod())
    methodStr = "GET";
  else if (EPOST == getMethod())
    methodStr = "POST";
  else if (EPUT == getMethod())
    methodStr = "PUT";
  else
    methodStr = "XXX";

  return std::string("url:")+getUrl()+"\n"+
         std::string("timeout:")+timeout+"\n"+
         std::string("headers:")+"\n"+headerStr+
         std::string("method:")+methodStr+"\n"+
         std::string("body:")+getBody()+"\n"+
         std::string("alternativeServerPath:")+getAlternativeServerPath()+"\n";
}

