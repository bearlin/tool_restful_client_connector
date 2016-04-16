//! @file CServerResponseTest.cpp
//!
//! @brief 
//!

#include "CloudClientCommon.h"
#include "HttpsURLConnection.h"
#include "HttpURLConnectionFactory.h"
#include "HttpsURLConnectionFactory.h"

#include "ServerResponse.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;

class CServerResponseTest: public ::testing::Test
{
};

TEST_F(CServerResponseTest, createCServerResponse)
{
  int aResponseCode = 302;
  std::string aHeaders = "test_header_text";
  const char* aBody = "test_body_text";
  
  printf("aBody addr:0x%lx, size:%ld\n", (unsigned long int)aBody, (size_t)strlen(aBody));
  CServerResponse* serverResponse = new CServerResponse(aResponseCode, aHeaders, aBody, (size_t)strlen(aBody));
  EXPECT_TRUE(NULL != serverResponse);
  EXPECT_TRUE(aResponseCode == serverResponse->getResponseCode());
  EXPECT_TRUE(0 == aHeaders.compare(serverResponse->getHeader()));

  char* getBodyBuffer; 
  size_t getBodySize;
  serverResponse->getBody(&getBodyBuffer, &getBodySize);
  printf("getBodyBuffer addr:0x%lx, getBodySize:%d\n", (unsigned long int)getBodyBuffer, (unsigned int)getBodySize);
  EXPECT_TRUE(getBodySize == strlen(aBody));
  EXPECT_TRUE(0 == memcmp(aBody, getBodyBuffer, getBodySize));

  printf("\nserverResponse->toString():\n%s\n", serverResponse->toString().c_str());
  
  delete serverResponse;
}

TEST_F(CServerResponseTest, createCServerResponseFromHttpsRequestBuffer)
{
  std::string aUrl = "https://example.com/";

  struct TMemoryStructGET headerChunk;
  struct TMemoryStructGET bodyChunk;
  
  headerChunk.memory = (char*)malloc(1); // will be grown as needed by the realloc() in write_data_to_memory()
  headerChunk.size = 0; // no data at this point
  bodyChunk.memory = (char*)malloc(1); // will be grown as needed by the realloc() in write_data_to_memory()
  bodyChunk.size = 0; // no data at this point

  CHttpsURLConnection* pCHttpsURLConnection = CHttpsURLConnectionFactory::GetInstance().createConnection(aUrl);
  EXPECT_TRUE(NULL != pCHttpsURLConnection);
  EXPECT_TRUE(pCHttpsURLConnection->HttpsSetSkipVerifications(false, false));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetFollowRedirection(false)); //For GetLoginToken, we just want to get the re-direct URL(in "Location:xxx" field) of responsed http header.
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetOutputHeaderBodyToSeparateMemorys(&headerChunk, &bodyChunk));
  EXPECT_TRUE(pCHttpsURLConnection->Perform());
  //showPerformResult(pCHttpsURLConnection);
  printf("headerChunk.size: %lu bytes retrieved\n", (long)headerChunk.size);
  printf("bodyChunk.size: %lu bytes retrieved\n", (long)bodyChunk.size);

  // Create the CServerResponse instance with the HTTP request result.
  long respcode = 0;
  EXPECT_TRUE(pCHttpsURLConnection->HttpGetResponseCode(&respcode));
  CServerResponse* serverResponse = new CServerResponse(respcode, headerChunk.memory, bodyChunk.memory, bodyChunk.size);

  // Once CServerResponse instance created, we can delete the HTTP request result buffers.
  free(headerChunk.memory);
  free(bodyChunk.memory);

  // Get the result.
  printf("\nserverResponse->toString():\n%s\n", serverResponse->toString().c_str());

  delete serverResponse;
}



