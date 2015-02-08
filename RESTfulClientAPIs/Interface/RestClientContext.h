//! @file RestClientContext.h
//!
//! @brief 
//!

#ifndef _REST_CLIENT_CONTEXT_H_
#define _REST_CLIENT_CONTEXT_H_

#include "HttpURLConnectionFactory.h"
#include "HttpsURLConnectionFactory.h"
#include <string>

class CRestClientContext
{
private:
  CHttpsURLConnectionFactory* iHttpsURLConnectionFactory;

  CRestClientContext(); // Private default constructor

public:
  CRestClientContext(CHttpsURLConnectionFactory* aHttpsURLConnectionFactory);
  virtual ~CRestClientContext();

  //! @brief    Get a pointer to CHttpsURLConnectionFactory instance.
  //! @return   A pointer to CHttpsURLConnectionFactory instance.
  CHttpsURLConnectionFactory* getUrlConnectionFactory();
};

#endif //_REST_CLIENT_CONTEXT_H_