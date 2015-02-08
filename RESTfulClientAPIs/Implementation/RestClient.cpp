//! @file RestResource.cpp
//!
//! @brief 
//!

#include "RestClient.h"
#include <curl/curl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

CRestClient::CRestClient(CRestClientContext* aContext, CCloudServer *aServer) :
  iContext(NULL)
  ,iServer(NULL)
  ,iErrCode(RESTCLIENT_OK)
{
  assert(NULL != aContext);
  assert(NULL != aServer);

  iContext = aContext;
  iServer = aServer;
}

CRestClient::~CRestClient() {;}

CServerResponse* CRestClient::makeRestCall(CRestCall& call)
{
  std::string aUrl;
  if (0 != call.getUrl().length()) 
  {
    aUrl = call.getUrl();
  }
  else if (0 != call.getAlternativeServerPath().length()) 
  {
    aUrl = call.getResource()->getResourceUrlWithAlternativePath(iServer->getServerUrl(), call.getAlternativeServerPath());
  }
  else 
  {
    aUrl = call.getResource()->getResourceUrl(iServer->getServerUrl());
  }

  return makeRestCall(aUrl, call.getMethod(), call.getReadTimeout(), call.getBody(), call.getHeaders());
}

CServerResponse* CRestClient::makeRestCall(std::string& aUrl,
                                           THttpMethod& aHttpMethod,
                                           long& aReadTimeout,
                                           std::string& aBodyObj,
                                           std::map<std::string, std::string>& aRequestHeaders)
{
  //assert(0 != aUrl.length());
  //assert(aHttpMethod <= EPOST);
  if (0 == aUrl.length())
  {
    std::cout<< "Error: aUrl.length() == 0" <<std::endl;
    iErrCode = RESTCLIENT_FAILED_INVALID_ARGUMENT;
    return NULL;
  }
  if (aHttpMethod > EPOST)
  {
    std::cout<< "Error: Unsupport HTTP method" <<std::endl;
    iErrCode = RESTCLIENT_FAILED_INVALID_ARGUMENT;
    return NULL;
  }

  CHttpsURLConnection* pCHttpsURLConnection = iContext->getUrlConnectionFactory()->createConnection(aUrl);
  if (NULL == pCHttpsURLConnection)
  {
    std::cout<< "Error: Create HTTP connection failed" <<std::endl;
    iErrCode = RESTCLIENT_FAILED_UNKNOWN_ERROR;
    return NULL;
  }
  
  CServerResponse* serverResponse = issueRequest(pCHttpsURLConnection, aHttpMethod, aRequestHeaders, aBodyObj, aReadTimeout);

  return serverResponse;
}

CServerResponse* CRestClient::issueRequest(CHttpsURLConnection* aConnection,
                               THttpMethod& aHttpMethod,
                               std::map<std::string, std::string>& aRequestHeaders,
                               std::string& aBody,
                               long& aReadTimeout) 
{
  if (0 > aReadTimeout)
  {
    std::cout<< "Timeout must be positive value" <<std::endl;
    iErrCode = RESTCLIENT_FAILED_INVALID_ARGUMENT;
    return NULL;
  }

  struct TMemoryStructGET headerOutChunk;
  struct TMemoryStructGET bodyOutChunk;
  struct TMemoryStructPOSTPUT postBodyChunk;
  struct TMemoryStructPOSTPUT putBodyChunk;

  headerOutChunk.memory = (char*)malloc(1); // will be grown as needed by the realloc() in write_data_to_memory()
  headerOutChunk.size = 0; // no data at this point
  bodyOutChunk.memory = (char*)malloc(1); // will be grown as needed by the realloc() in write_data_to_memory()
  bodyOutChunk.size = 0; // no data at this point

  if (!aConnection->HttpsSetSkipVerifications(false, false))
  {
    std::cout<< "Error: HttpsSetSkipVerifications()" <<std::endl;
    iErrCode = RESTCLIENT_FAILED_HTTP_SET;
    return NULL;
  }
  
  if (!aConnection->HttpSetFollowRedirection(false))
  {
    std::cout<< "Error: HttpSetFollowRedirection()" <<std::endl;
    iErrCode = RESTCLIENT_FAILED_HTTP_SET;
    return NULL;
  }
  
  if (!aConnection->HttpSetVerbose(true))
  {
    std::cout<< "Error: HttpSetVerbose()" <<std::endl;
    iErrCode = RESTCLIENT_FAILED_HTTP_SET;
    return NULL;
  }
  
  if (!aConnection->HttpSetTimeoutMs(aReadTimeout))
  {
    std::cout<< "Error: HttpSetTimeoutMs()" <<std::endl;
    iErrCode = RESTCLIENT_FAILED_HTTP_SET;
    return NULL;
  }
  
  if (!aConnection->HttpSetHeaderFromMap(aRequestHeaders))
  {
    std::cout<< "Error: HttpSetHeaderFromMap()" <<std::endl;
    iErrCode = RESTCLIENT_FAILED_HTTP_SET;
    return NULL;
  }
  
  if (!aConnection->HttpSetOutputHeaderBodyToSeparateMemorys(&headerOutChunk, &bodyOutChunk))
  {
    std::cout<< "Error: HttpSetOutputHeaderBodyToSeparateMemorys()" <<std::endl;
    iErrCode = RESTCLIENT_FAILED_HTTP_SET;
    return NULL;
  }

  switch (aHttpMethod) 
  {
    case EGET:
      {
        // Do nothing.
      }
      break;
      
    case EPUT:
      {
        putBodyChunk.data = aBody.c_str();
        putBodyChunk.size = aBody.length();

        if (!aConnection->HttpSetPUTFromBuffer(putBodyChunk))
        {
          std::cout<< "Error: HttpSetPUTFromBuffer()" <<std::endl;
          iErrCode = RESTCLIENT_FAILED_HTTP_SET;
          return NULL;
        }
      }
      break;

    case EPOST:
      {
        postBodyChunk.data = aBody.c_str();
        postBodyChunk.size = aBody.length();

        if (!aConnection->HttpSetPOSTFromBuffer(postBodyChunk))
        {
          std::cout<< "Error: HttpSetPOSTFromBuffer()" <<std::endl;
          iErrCode = RESTCLIENT_FAILED_HTTP_SET;
          return NULL;
        }
      }
      break;
      
    default:
      {
        std::cout<< "Unsupport HTTP method" <<std::endl;
        iErrCode = RESTCLIENT_FAILED_INVALID_ARGUMENT;
        return NULL;
      }
      break;
  }

  if (!aConnection->Perform())
  {
    std::cout<< "Error: Perform()" <<std::endl;
    int httpResult = aConnection->getRespondCode();

    switch (httpResult)
    {
      case CURLE_COULDNT_RESOLVE_HOST :
        std::cout<< "COULDNT_RESOLVE_HOST" <<std::endl;
        iErrCode = RESTCLIENT_FAILED_HTTP_PERFORM_NETWORK_NOT_AVAILABLE;
        break;
        
      case CURLE_COULDNT_CONNECT :
        std::cout<< "COULDNT_CONNECT" <<std::endl;
        iErrCode = RESTCLIENT_FAILED_HTTP_PERFORM_SERVER_NOT_RESPOND;
        break;
        
      default :
        std::cout<< "incorrect perform" <<std::endl;
        iErrCode = RESTCLIENT_FAILED_HTTP_PERFORM_OTHERS;
        break;
    }

    return NULL;
  }

  //std::cout<< "headerOutChunk.size:" << headerOutChunk.size <<std::endl;
  //std::cout<< "bodyOutChunk.size:" << bodyOutChunk.size <<std::endl;
  //std::cout<< "-------------------------------" <<std::endl;
  //if (0 != headerOutChunk.size)
  //  std::cout<< "" << headerOutChunk.memory <<std::endl;
  //if (0 != bodyOutChunk.size)
  //  std::cout<< "" << bodyOutChunk.memory <<std::endl;
  //std::cout<< "-------------------------------" <<std::endl;

  // Create the CServerResponse instance with the HTTP request result.
  long respcode = 0;
  if (!aConnection->HttpGetResponseCode(&respcode))
  {
    std::cout<< "Error: HttpGetResponseCode()" <<std::endl;
    iErrCode = RESTCLIENT_FAILED_HTTP_GET;
    return NULL;
  }
  
  CServerResponse* serverResponse = new CServerResponse(respcode, headerOutChunk.memory, bodyOutChunk.memory, bodyOutChunk.size);

  // Once CServerResponse instance created, we can delete the HTTP request result buffers.
  free(headerOutChunk.memory);
  free(bodyOutChunk.memory);

  return serverResponse;
}

int CRestClient::getErrorCode() 
{
  return iErrCode;
}


