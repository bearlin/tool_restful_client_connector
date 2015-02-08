//! @file ServerResponse.h
//!
//! @brief
//!

#ifndef _SERVER_RESPONSE_H_
#define _SERVER_RESPONSE_H_

#include <string>

class CServerResponse
{
private:
  int iResponseCode;
  std::string iHeaders;
  char* iBodyBuffer;
  size_t iBodySize;

public:
  CServerResponse(int aResponseCode, std::string aHeaders, const char* aBodyBuffer, size_t aBodySize);
  virtual ~CServerResponse();

  //! @brief  Get HTTP response code after perform a request.
  //! @return HTTP response code
  int getResponseCode();

  //! @brief  Get HTTP header string after perform a request.
  //! @return HTTP header string
  std::string getHeader();

  //! @brief        Get HTTP body.
  //! @param[out]   Pass a pointer to char*, this pointer will be modified and point to the received body address after called. 
  //! @param[out]   A size_t variable address to get the body buffer size.
  //! @return       void.
  void getBody(char** aBodyBuffer, size_t* aBodySize);

  //! @brief        Get HTTP body buffer address.
  //! @return       A pointer to HTTP body buffer.
  char* getBodyData();

  //! @brief        Get HTTP body size.
  //! @return       HTTP body size.
  size_t getBodySize();

  //! @brief  Converts object to its string representation.
  //! @return Object string representation.
  std::string toString();
};

#endif //_SERVER_RESPONSE_H_
