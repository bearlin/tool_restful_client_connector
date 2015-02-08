//! @file HttpsURLConnection.cpp
//!
//! @brief 
//!

#include "HttpsURLConnection.h"

CHttpsURLConnection::CHttpsURLConnection() : 
  CHttpURLConnection()
{
}

CHttpsURLConnection::~CHttpsURLConnection()
{;}

bool CHttpsURLConnection::OpenConnection(std::string aUrl)
{
  if (!this->CHttpURLConnection::OpenConnection(aUrl))
    return false;

  return true;
}

bool CHttpsURLConnection::HttpsSetSkipVerifications(bool aVerifyPeer, bool aVerifyHostname)
{
  //std::cout<< "aVerifyPeer:" << aVerifyPeer << "aVerifyHostname" << aVerifyHostname <<std::endl;

//#ifdef SKIP_PEER_VERIFICATION
  /*
   * If you want to connect to a site who isn't using a certificate that is
   * signed by one of the certs in the CA bundle you have, you can skip the
   * verification of the server's certificate. This makes the connection
   * A LOT LESS SECURE.
   *
   * If you have a CA cert for the server stored someplace else than in the
   * default bundle, then the CURLOPT_CAPATH option might come handy for
   * you.
   */
  iRes = curl_easy_setopt(iCurl, CURLOPT_SSL_VERIFYPEER, ((true == aVerifyPeer)? 1L : 0L));
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }

//#endif
//#ifdef SKIP_HOSTNAME_VERIFICATION
  /*
   * If the site you're connecting to uses a different host name that what
   * they have mentioned in their server certificate's commonName (or
   * subjectAltName) fields, libcurl will refuse to connect. You can skip
   * this check, but this will make the connection less secure.
   */
  iRes = curl_easy_setopt(iCurl, CURLOPT_SSL_VERIFYHOST, ((true == aVerifyHostname)? 1L : 0L));
  if(CURLE_OK != iRes)
  {
    std::cout<< "curl_easy_setopt() failed: " << curl_easy_strerror(iRes) <<std::endl;
    return false;
  }
//#endif

  return true;
}

