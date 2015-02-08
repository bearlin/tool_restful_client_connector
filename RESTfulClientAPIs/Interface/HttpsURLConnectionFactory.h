//! @file HttpsURLConnectionFactory.h
//!
//! @brief 
//!

#ifndef _HTTPSURLCONNECTIONFACTORY_H_
#define _HTTPSURLCONNECTIONFACTORY_H_

#include "HttpsURLConnection.h"
#include "HttpURLConnectionFactory.h"

// A singleton class : http://stackoverflow.com/questions/86582/singleton-how-should-it-be-used
class CHttpsURLConnectionFactory// : public CHttpURLConnectionFactory
{
private:
  // Private default constructor
  CHttpsURLConnectionFactory(); 
  // Stop the compiler generating methods of copy the object
  CHttpsURLConnectionFactory(CHttpsURLConnectionFactory const& copy);             // Not Implemented
  CHttpsURLConnectionFactory& operator=(CHttpsURLConnectionFactory const& copy);  // Not Implemented

  CHttpsURLConnection* iCHttpsURLConnection;
  
public:
  virtual ~CHttpsURLConnectionFactory();

  //! @brief    Get a CHttpsURLConnectionFactory singleton instance.
  //! @return   Return true if successfully set the value, else return false.
  static CHttpsURLConnectionFactory& GetInstance();

  //! @brief    Create a new CHttpsURLConnection instance and open a connection to aUrl.
  //! @return   Return CHttpsURLConnection instance.
  CHttpsURLConnection* createConnection(std::string aUrl);
};

#endif //_HTTPSURLCONNECTIONFACTORY_H_