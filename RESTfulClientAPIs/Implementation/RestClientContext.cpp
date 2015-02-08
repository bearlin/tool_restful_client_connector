//! @file RestClientContext.cpp
//!
//! @brief 
//!

#include "RestClientContext.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

CRestClientContext::CRestClientContext(CHttpsURLConnectionFactory* aHttpsURLConnectionFactory)
{
  assert(NULL != aHttpsURLConnectionFactory);
  iHttpsURLConnectionFactory = aHttpsURLConnectionFactory;//&CHttpsURLConnectionFactory::GetInstance();
}

CRestClientContext::~CRestClientContext() {;}

CHttpsURLConnectionFactory* CRestClientContext::getUrlConnectionFactory() 
{
  return iHttpsURLConnectionFactory;
}
