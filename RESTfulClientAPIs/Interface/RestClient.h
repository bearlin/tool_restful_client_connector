//! @file RestClient.h
//!
//! @brief 
//!

#ifndef _REST_CLIENT_H_
#define _REST_CLIENT_H_

#include "CloudClientCommon.h"
#include "CloudServer.h"
#include "RestClientContext.h"
#include "RestCall.h"
#include "ServerResponse.h"
#include <string>

// CRestClient error codes.
#define RESTCLIENT_OK                                         (0)
#define RESTCLIENT_FAILED_HTTP_SET                            (1)
#define RESTCLIENT_FAILED_HTTP_GET                            (2)
#define RESTCLIENT_FAILED_HTTP_PERFORM_SERVER_NOT_RESPOND     (3)
#define RESTCLIENT_FAILED_HTTP_PERFORM_NETWORK_NOT_AVAILABLE  (4)
#define RESTCLIENT_FAILED_HTTP_PERFORM_OTHERS                 (5)
#define RESTCLIENT_FAILED_INVALID_ARGUMENT                    (6)
#define RESTCLIENT_FAILED_UNKNOWN_ERROR                       (7)

class CRestClient
{
private:
  CRestClientContext* iContext;
  CCloudServer* iServer;
  int iErrCode;

  CServerResponse* issueRequest(CHttpsURLConnection* aConnection,
                                 THttpMethod& aHttpMethod,
                                 std::map<std::string, std::string>& aRequestHeaders,
                                 std::string& aBody,
                                 long& aReadTimeout);
  
public:
  CRestClient(CRestClientContext* aContext, CCloudServer *aServer);
  virtual ~CRestClient();

  //! @brief            Prepares and send a request to the server. 
  //!                   It might actually only do this once we start to read from a stream, but this method appears to send the real request.
  //! @param[in]  call  The RestCall descriptor to make the request with
  //! @return           A newly allocated CServerResponse object pointer represent the response from remote server.
  //!                   You must delete the returned CServerResponse object pointer when you're done with it.
  CServerResponse* makeRestCall(CRestCall& call);

  //! @brief            Prepares and send a request to the server. 
  //!                   It might actually only do this once we start to read from a stream, but this method appears to send the real request.
  //! @param[in]  aUrl              The request URL.
  //! @param[in]  aHttpMethod       The HTTP method to be used.
  //! @param[in]  aReadTimeout      The timeout while perform the request.
  //! @param[in]  aBodyObj          The request body content
  //! @param[in]  aRequestHeaders   The list of headers to be sent with this call
  //! @return                       A newly allocated CServerResponse object pointer represent the response from remote server.
  //!                               You must delete the returned CServerResponse object pointer when you're done with it.
  CServerResponse* makeRestCall(std::string& aUrl,
                                 THttpMethod& aHttpMethod,
                                 long& aReadTimeout,
                                 std::string& aBodyObj,
                                 std::map<std::string, std::string>& aRequestHeaders);

  //! @brief    Get CRestClient error code represent the status of makeRestCall().
  //! @return   CRestClient error code.
  int getErrorCode();
};

#endif //_REST_CLIENT_H_