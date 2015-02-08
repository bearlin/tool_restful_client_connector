//! @file HttpsURLConnectionFactory.cpp
//!
//! @brief 
//!

#include "HttpsURLConnectionFactory.h"

CHttpsURLConnectionFactory::CHttpsURLConnectionFactory() :
  iCHttpsURLConnection(NULL)
{;}

CHttpsURLConnectionFactory::~CHttpsURLConnectionFactory()
{
  if (iCHttpsURLConnection)
    delete iCHttpsURLConnection;
  iCHttpsURLConnection = NULL;
}

CHttpsURLConnectionFactory& CHttpsURLConnectionFactory::GetInstance()
{
  // The only instance
  // Guaranteed to be lazy initialized
  // Guaranteed that it will be destroyed correctly
  static CHttpsURLConnectionFactory instance;
  
  return instance;
}

CHttpsURLConnection* CHttpsURLConnectionFactory::createConnection(std::string aUrl)
{  
  if (iCHttpsURLConnection)
    delete iCHttpsURLConnection;
    
  iCHttpsURLConnection = new CHttpsURLConnection();
  if (!iCHttpsURLConnection->OpenConnection(aUrl))
  {
    delete iCHttpsURLConnection;
    iCHttpsURLConnection = NULL;
  }
    
  return iCHttpsURLConnection;
}

