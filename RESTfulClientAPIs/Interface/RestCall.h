//! @file RestCall.h
//!
//! @brief 
//!

#ifndef _REST_CALL_H_
#define _REST_CALL_H_

#include "CloudClientCommon.h"
#include "RestResource.h"
#include <map>
#include <sstream>

extern const long KDEFAULT_TIMEOUT_MILLIS;
extern const long KDEFAULT_CONNECT_TIMEOUT_MILLIS;
extern const long KDEFAULT_READ_TIMEOUT_MILLIS;

class CRestCall
{
private:
  std::string iUrl;
  CRestResource* iResource;
  long iReadTimeout;
  std::map<std::string, std::string> iHeaders;
  THttpMethod iMethod;
  std::string iBody;
  std::string iAlternativeServerPath;

  // Private default constructor
  CRestCall(); 
  // Stop the compiler generating methods of copy the object
  CRestCall(CRestCall const& copy);             // Not Implemented
  CRestCall& operator=(CRestCall const& copy);  // Not Implemented

  //! @brief Reset all private members in CRestCall::to().
  void reset();

public:
  virtual ~CRestCall();

  //! @brief                Create a new RestCall to a resource from the predefined enumeration of resources
  //! @param[in]  aResource The target resource
  //! @return               A new RestCall
  static CRestCall& to(CRestResource* aResource);

  //! @brief            Create a new RestCall to a URL
  //! @param[in]  aUrl  The URL the request will be made to
  //! @return           A new RestCall
  static CRestCall& to(std::string aUrl);

  //! @brief                    Configures the current rest call with a read timeout
  //! @param[in]  aReadTimeout  The timeout after which the request will disconnect, in milliseconds
  //! @return                   This RestCall object
  CRestCall& withReadTimeout(long aReadTimeout);

  //! @brief                Adds multiple headers to the list of headers to be sent with this call
  //! @param[in]  aHeaders  A map containing key-value pairs to be added to the header entries
  //! @return               This RestCall object
  CRestCall& withHeaders(std::map<std::string, std::string>& aHeaders);
  
  //! @brief              Adds a header to the list of headers to be sent with this call
  //! @param[in]  aHeader The name of the header (e.g. Content-Type)
  //! @param[in]  aValue  The value (e.g. application/json)
  //! @return             This RestCall object
  CRestCall& withHeader(std::string aHeader, std::string aValue);

  //! @brief              Configures the current call to use the specified HTTP method
  //! @param[in]  aMethod The HTTP method to use
  //! @return             This RestCall object
  CRestCall& withMethod(THttpMethod aMethod);

  //! @brief            Sets an object to be used as a request body. Valid for POST and PUT requests.
  //! @param[in]  aBody The request body content
  //! @return           This RestCall object
  //! @throws           std::invalid_argument when body is set for a method other than POST or PUT
  CRestCall& withBody(std::string aBody);

  //! @brief                              An alternative server context path to use, in case the call is pointed to a RestResource
  //! @param[in]  aAlternativeServerPath  The alternative context path
  //! @return                             This RestCall object
  //! @throws                             std::invalid_argument when this method is invoked on a RestCall that is not using a RestResource
  CRestCall& withAlternativeServerPath(std::string aAlternativeServerPath);

  //! @brief  Gets the URL string
  //! @return URL string
  std::string& getUrl();

  //! @brief  Gets the RestResource, if set
  //! @return The RestResource if set, null otherwise
  CRestResource* getResource();

  //! @brief  Gets the read timeout (in milliseconds)
  //! @return The read timeout, using KDEFAULT_READ_TIMEOUT_MILLIS by default
  long& getReadTimeout();

  //! @brief  Gets the configured headers
  //! @return A map of configured headers; empty map if none were set
  std::map<std::string, std::string>& getHeaders();

  //! @brief  Gets the HTTP method
  //! @return The HTTP method. If not set, GET is used by default.
  THttpMethod& getMethod();

  //! @brief  Gets the body of the request
  //! @return The body string
  std::string& getBody();

  //! @brief  Gets the alternative server context path
  //! @return The iAlternativeServerPath string
  std::string& getAlternativeServerPath();

  //! @brief  Converts object to its string representation.
  //! @return Object string representation.
  std::string toString();
};

#endif //_REST_CALL_H_
