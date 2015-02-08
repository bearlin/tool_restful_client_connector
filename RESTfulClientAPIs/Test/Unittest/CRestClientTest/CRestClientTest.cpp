//! @file CRestClientTest.cpp
//!
//! @brief
//!

#include "CloudClientCommon.h"
#include "RestResource.h"
#include "CloudServer.h"
#include "RestCall.h"
#include "RestClientContext.h"
#include "RestClient.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;

class CRestClientContextTest: public ::testing::Test
{
};

class CRestCallTest: public ::testing::Test
{
};

class CRestClientTest: public ::testing::Test
{
};

void showPerformResult(CHttpURLConnection* connection)
{
  printf("----------Result---------\n");
  char* url = NULL;
  long respcode = 0;
  long redirectCnt = 0;
  char* redirectUrl = NULL;
  char* contentType = NULL;
  EXPECT_TRUE(connection->HttpGetEffectiveUrl(&url));
  EXPECT_TRUE(connection->HttpGetResponseCode(&respcode));
  EXPECT_TRUE(connection->HttpGetRedirectCount(&redirectCnt));
  EXPECT_TRUE(connection->HttpGetRedirectUrl(&redirectUrl));
  EXPECT_TRUE(connection->HttpGetContentType(&contentType));
  printf("url:%s\n", url);
  printf("respcode:%ld\n", respcode);
  printf("contentType:%s\n", contentType);
  printf("redirectCnt:%ld\n", redirectCnt);
  printf("redirectUrl:%s\n", redirectUrl);
  printf("-------------------------\n");
}

TEST_F(CRestClientContextTest, Test_CreateCRestClientContext_And_HttpConnection)
{
  std::string aUrl = "https://example.com/";

  CRestClientContext* context = new CRestClientContext(&CHttpsURLConnectionFactory::GetInstance());
  EXPECT_TRUE(NULL != context);

  CHttpsURLConnection* pCHttpsURLConnection = context->getUrlConnectionFactory()->createConnection(aUrl);

  EXPECT_TRUE(NULL != pCHttpsURLConnection);
  EXPECT_TRUE(pCHttpsURLConnection->HttpsSetSkipVerifications(false, false));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetFollowRedirection(true));
  EXPECT_TRUE(pCHttpsURLConnection->Perform());

  showPerformResult(pCHttpsURLConnection);

  delete context;
}

TEST_F(CRestCallTest, createCRestCalls)
{
  std::string aUrl = "https://example.com/";

  std::cout << CRestCall::to(aUrl)
                        .withMethod(EGET)
                        .withReadTimeout(9999L)
                        .toString()
                        << std::endl;

  std::cout << CRestCall::to(aUrl)
                        .withMethod(EPUT)
                        .withHeader("Content-Type", "application/ov2")
                        .withHeader("Content-Disposition", "inline; filename=test.txt")
                        .withHeader("X-Content-Length", "2048")
                        .withBody(std::string("test_body", strlen("test_body")))
                        .toString()
                        << std::endl;
}

TEST_F(CRestClientTest, makeRestCallGET)
{
  std::string aUrl = "https://example.com/";
  CCloudServer* server = new CCloudServer(aUrl);
  CRestClientContext* context = new CRestClientContext(&CHttpsURLConnectionFactory::GetInstance());
  CRestClient* restClient = new CRestClient(context, server);
  CServerResponse* serverResponse = restClient->makeRestCall(CRestCall::to(aUrl)
                                                              .withMethod(EGET));
  EXPECT_TRUE(RESTCLIENT_OK == restClient->getErrorCode());
  EXPECT_TRUE(NULL != serverResponse);

  printf("\nserverResponse->toString():\n");
  printf("------------------------------\n");
  printf("%s", serverResponse->toString().c_str());
  printf("------------------------------\n");

  delete server;
  delete context;
  delete restClient;
  if (NULL != serverResponse)
    delete serverResponse;
}

TEST_F(CRestClientTest, makeRestCallPOST)
{
  const char* POSTdata = "{\"key\":\"the is a test body to server\"}";
  std::string aUrl = "https://example.com/";
  CCloudServer* server = new CCloudServer(aUrl);
  CRestClientContext* context = new CRestClientContext(&CHttpsURLConnectionFactory::GetInstance());
  CRestClient* restClient = new CRestClient(context, server);
  CServerResponse* serverResponse = restClient->makeRestCall(CRestCall::to(aUrl)
                                                              .withMethod(EPOST)
                                                              .withHeader("Accept", "application/vnd.server.cloud")
                                                              .withHeader("Content-Type", "application/json; charset=UTF-8")
                                                              .withBody(std::string(POSTdata, strlen(POSTdata))));
  EXPECT_TRUE(RESTCLIENT_OK == restClient->getErrorCode());
  EXPECT_TRUE(NULL != serverResponse);
  printf("\nserverResponse->toString():\n");
  printf("------------------------------\n");
  printf("%s", serverResponse->toString().c_str());
  printf("------------------------------\n");

  delete server;
  delete context;
  delete restClient;
  if (NULL != serverResponse)
    delete serverResponse;

}

TEST_F(CRestClientTest, makeRestCallPUT)
{
  const char* PUTdata = "{\"key\":\"the is a test body to server\"}";
  std::string aUrl = "https://example.com/";
  CCloudServer* server = new CCloudServer(aUrl);
  CRestClientContext* context = new CRestClientContext(&CHttpsURLConnectionFactory::GetInstance());
  CRestClient* restClient = new CRestClient(context, server);
  CServerResponse* serverResponse = restClient->makeRestCall(CRestCall::to(aUrl)
                                                              .withMethod(EPUT)
                                                              .withBody(std::string(PUTdata, strlen(PUTdata))));
  EXPECT_TRUE(RESTCLIENT_OK == restClient->getErrorCode());
  EXPECT_TRUE(NULL != serverResponse);
  printf("\nserverResponse->toString():\n");
  printf("------------------------------\n");
  printf("%s", serverResponse->toString().c_str());
  printf("------------------------------\n");

  delete server;
  delete context;
  delete restClient;
  if (NULL != serverResponse)
    delete serverResponse;
}