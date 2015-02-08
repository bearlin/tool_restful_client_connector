//! @file HttpURLConnectionFactory.cpp
//!
//! @brief 
//!

#include "HttpURLConnectionFactory.h"

CHttpURLConnectionFactory::CHttpURLConnectionFactory() :
  iCHttpURLConnection(NULL)
{;}

CHttpURLConnectionFactory::~CHttpURLConnectionFactory()
{
  if (iCHttpURLConnection)
    delete iCHttpURLConnection;
  iCHttpURLConnection = NULL;
}

CHttpURLConnectionFactory& CHttpURLConnectionFactory::GetInstance()
{
  // The only instance
  // Guaranteed to be lazy initialized
  // Guaranteed that it will be destroyed correctly
  static CHttpURLConnectionFactory instance;
  
  return instance;
}

CHttpURLConnection* CHttpURLConnectionFactory::createConnection(std::string aUrl)
{  
  if (iCHttpURLConnection)
    delete iCHttpURLConnection;
    
  iCHttpURLConnection = new CHttpURLConnection();
  if (!iCHttpURLConnection->OpenConnection(aUrl))
  {
    delete iCHttpURLConnection;
    iCHttpURLConnection = NULL;
  }
    
  return iCHttpURLConnection;
}

