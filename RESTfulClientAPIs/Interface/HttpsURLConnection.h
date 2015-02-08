//! @file HttpsURLConnection.h
//!
//! @brief 
//!

#ifndef _HTTPSURLCONNECTION_H_
#define _HTTPSURLCONNECTION_H_

#include "HttpURLConnection.h"

class CHttpsURLConnection : public CHttpURLConnection
{
private:

public:
  CHttpsURLConnection();
  virtual ~CHttpsURLConnection();

  // [Basic HTTPS actions]
  //! @brief            Initialize and set actual URL to deal with.
  //! @param[in]  aUrl  The actual URL to deal with, aUrl must be URL-encoded with format scheme://host:port/path.
  //! @return           Return true if success, else return false.
  virtual bool OpenConnection(std::string aUrl);

  // [For HTTPS options before perform]
  //! @brief                        This function can be used to: 
  //!                               Skip the verification of the server's certificate(This makes the connection A LOT LESS SECURE). 
  //!                               Skip the checking of server host name(This will make the connection less secure).
  //! @param[out] aVerifyPeer       Enable/Disable the verification of the server's certificate. 
  //! @param[out] aVerifyHostname   Enable/Disable the checking of server host name. 
  //! @return                       Return true if successfully set the value, else return false.
  bool HttpsSetSkipVerifications(bool aVerifyPeer, bool aVerifyHostname);
};

#endif //_HTTPSURLCONNECTION_H_
