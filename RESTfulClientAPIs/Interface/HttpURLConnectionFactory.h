//! @file HttpURLConnectionFactory.h
//!
//! @brief 
//!

#ifndef _HTTPURLCONNECTIONFACTORY_H_
#define _HTTPURLCONNECTIONFACTORY_H_

#include "HttpURLConnection.h"

// A singleton class : http://stackoverflow.com/questions/86582/singleton-how-should-it-be-used
class CHttpURLConnectionFactory 
{
private:
  // Private default constructor
  CHttpURLConnectionFactory(); 
  // Stop the compiler generating methods of copy the object
  CHttpURLConnectionFactory(CHttpURLConnectionFactory const& copy);             // Not Implemented
  CHttpURLConnectionFactory& operator=(CHttpURLConnectionFactory const& copy);  // Not Implemented

  CHttpURLConnection* iCHttpURLConnection;
  
public:
  virtual ~CHttpURLConnectionFactory();

  //! @brief    Get a CHttpURLConnectionFactory singleton instance.
  //! @return   Return true if successfully set the value, else return false.
  static CHttpURLConnectionFactory& GetInstance();

  //! @brief    Create a new CHttpURLConnection instance and open a connection to aUrl.
  //! @return   Return CHttpURLConnection instance.
  CHttpURLConnection* createConnection(std::string aUrl);
};

#endif //_HTTPURLCONNECTIONFACTORY_H_
