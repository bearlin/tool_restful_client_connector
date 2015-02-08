//! @file CHttpURLConnectionTest.cpp
//!
//! @brief
//!

#include "CloudClientCommon.h"
#include "HttpsURLConnection.h"
#include "HttpURLConnectionFactory.h"
#include "HttpsURLConnectionFactory.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;

class CHttpURLConnectionTest: public ::testing::Test
{
};

class CHttpsURLConnectionTest: public ::testing::Test
{
};

class CHttpURLConnectionFactoryTest: public ::testing::Test
{
};

class CHttpsURLConnectionFactoryTest: public ::testing::Test
{
};

class CHttpsURLConnectionPOSTPUTTest: public ::testing::Test
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

TEST_F(CHttpURLConnectionTest, createHttpURLConnection)
{
  std::string aUrl = "http://example.com/";

  CHttpURLConnection* pCHttpURLConnection = new CHttpURLConnection();
  EXPECT_TRUE(NULL != pCHttpURLConnection);
  EXPECT_TRUE(pCHttpURLConnection->OpenConnection(aUrl));
  EXPECT_TRUE(pCHttpURLConnection->HttpSetFollowRedirection(true));
  EXPECT_TRUE(pCHttpURLConnection->HttpSetVerbose(true));
  EXPECT_TRUE(pCHttpURLConnection->Perform());
  showPerformResult(pCHttpURLConnection);

  delete pCHttpURLConnection;
}

TEST_F(CHttpURLConnectionTest, UrlEncodingDecoding)
{
  // We should open a connection before using curl funtions.
  std::string aUrl = "https://example.com/";
  CHttpsURLConnection* pCHttpsURLConnection = new CHttpsURLConnection();
  EXPECT_TRUE(NULL != pCHttpsURLConnection);
  EXPECT_TRUE(pCHttpsURLConnection->OpenConnection(aUrl));
  EXPECT_TRUE(pCHttpsURLConnection->HttpsSetSkipVerifications(false, false));

  // Test strings can be obtained from here :
  // https://dev.twitter.com/docs/auth/percent-encoding-parameters
  // http://en.wikipedia.org/wiki/Percent-encoding
  // http://www.url-encode-decode.com/
  char* aTestStrBeforeEncoded = (char*)"Dogs, Cats & Mice";//"85zU5BKwz98=";
  char* aTestStrAfterEncoded = (char*)"Dogs%2C%20Cats%20%26%20Mice";//"85zU5BKwz98%3D";
  char* pEncodedString = NULL;
  char* pDecodedString = NULL;
  printf("aTestStrBeforeEncoded:%s\n", aTestStrBeforeEncoded);
  printf("aTestStrAfterEncoded:%s\n", aTestStrAfterEncoded);

  pEncodedString = pCHttpsURLConnection->UrlEncoding(aTestStrBeforeEncoded, 0);
  EXPECT_TRUE(NULL != pEncodedString);
  printf("pEncodedString:%s\n", pEncodedString);
  EXPECT_TRUE(0 == std::string(pEncodedString).compare(aTestStrAfterEncoded));
  pCHttpsURLConnection->UrlFreeEncodeDecodeStringBuffer(pEncodedString);

  int outLength = 0;
  pDecodedString = pCHttpsURLConnection->UrlDecoding(aTestStrAfterEncoded, 0, &outLength);
  EXPECT_TRUE(NULL != pDecodedString);
  printf("outLength:%d\n", outLength);
  printf("pDecodedString:%s\n", pDecodedString);
  EXPECT_TRUE(0 == std::string(pDecodedString).compare(aTestStrBeforeEncoded));
  pCHttpsURLConnection->UrlFreeEncodeDecodeStringBuffer(pDecodedString);
}

TEST_F(CHttpsURLConnectionTest, createHttpsURLConnection)
{
  std::string aUrl = "https://example.com/";

  CHttpsURLConnection* pCHttpsURLConnection = new CHttpsURLConnection();
  EXPECT_TRUE(NULL != pCHttpsURLConnection);
  EXPECT_TRUE(pCHttpsURLConnection->OpenConnection(aUrl));
  EXPECT_TRUE(pCHttpsURLConnection->HttpsSetSkipVerifications(false, false));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetFollowRedirection(true));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetVerbose(true));
  EXPECT_TRUE(pCHttpsURLConnection->Perform());
  showPerformResult(pCHttpsURLConnection);

  delete pCHttpsURLConnection;
}

TEST_F(CHttpsURLConnectionTest, HttpsTimeout)
{
  std::string aUrl = "https://example.com/";

  // Test HttpSetTimeout(5), we EXPECT_TRUE after perform this http request.
  CHttpsURLConnection* pCHttpsURLConnection = new CHttpsURLConnection();
  EXPECT_TRUE(NULL != pCHttpsURLConnection);
  EXPECT_TRUE(pCHttpsURLConnection->OpenConnection(aUrl));
  EXPECT_TRUE(pCHttpsURLConnection->HttpsSetSkipVerifications(false, false));
  //EXPECT_TRUE(pCHttpsURLConnection->HttpSetFollowRedirection(true));
  //EXPECT_TRUE(pCHttpsURLConnection->HttpSetVerbose(true));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetTimeout(5));
  EXPECT_TRUE(pCHttpsURLConnection->Perform());
  showPerformResult(pCHttpsURLConnection);
  delete pCHttpsURLConnection;

  // Test HttpSetTimeout(1), we EXPECT_TRUE after perform this http request.
  pCHttpsURLConnection = new CHttpsURLConnection();
  EXPECT_TRUE(NULL != pCHttpsURLConnection);
  EXPECT_TRUE(pCHttpsURLConnection->OpenConnection(aUrl));
  EXPECT_TRUE(pCHttpsURLConnection->HttpsSetSkipVerifications(false, false));
  //EXPECT_TRUE(pCHttpsURLConnection->HttpSetFollowRedirection(true));
  //EXPECT_TRUE(pCHttpsURLConnection->HttpSetVerbose(true));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetTimeout(1));
  EXPECT_TRUE(pCHttpsURLConnection->Perform());
  showPerformResult(pCHttpsURLConnection);
  delete pCHttpsURLConnection;

  // Test HttpSetTimeoutMs(5000L), we EXPECT_TRUE after perform this http request.
  pCHttpsURLConnection = new CHttpsURLConnection();
  EXPECT_TRUE(NULL != pCHttpsURLConnection);
  EXPECT_TRUE(pCHttpsURLConnection->OpenConnection(aUrl));
  EXPECT_TRUE(pCHttpsURLConnection->HttpsSetSkipVerifications(false, false));
  //EXPECT_TRUE(pCHttpsURLConnection->HttpSetFollowRedirection(true));
  //EXPECT_TRUE(pCHttpsURLConnection->HttpSetVerbose(true));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetTimeoutMs(5000L));
  EXPECT_TRUE(pCHttpsURLConnection->Perform());
  showPerformResult(pCHttpsURLConnection);
  delete pCHttpsURLConnection;

  // Test HttpSetTimeoutMs(1L), we EXPECT_FALSE after perform this http request.
  pCHttpsURLConnection = new CHttpsURLConnection();
  EXPECT_TRUE(NULL != pCHttpsURLConnection);
  EXPECT_TRUE(pCHttpsURLConnection->OpenConnection(aUrl));
  EXPECT_TRUE(pCHttpsURLConnection->HttpsSetSkipVerifications(false, false));
  //EXPECT_TRUE(pCHttpsURLConnection->HttpSetFollowRedirection(true));
  //EXPECT_TRUE(pCHttpsURLConnection->HttpSetVerbose(true));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetTimeoutMs(1L));
  EXPECT_FALSE(pCHttpsURLConnection->Perform());
  showPerformResult(pCHttpsURLConnection);
  delete pCHttpsURLConnection;
}

TEST_F(CHttpsURLConnectionTest, HttpSetOutputHeaderBodyToSeparateFiles)
{
  std::string aUrl = "https://example.com/";
  const char *aHeaderFileName = "HttpsHead.out";
  const char *aBodyFileName = "HttpsBody.out";
  FILE *aFdHeader;
  FILE *aFdBody;

  // open the files
  aFdHeader = fopen(aHeaderFileName, "wb");
  if (aFdHeader == NULL) {
    EXPECT_TRUE(0);
  }
  aFdBody = fopen(aBodyFileName, "wb");
  if (aFdBody == NULL) {
    EXPECT_TRUE(0);
  }

  CHttpsURLConnection* pCHttpsURLConnection = new CHttpsURLConnection();
  EXPECT_TRUE(NULL != pCHttpsURLConnection);
  EXPECT_TRUE(pCHttpsURLConnection->OpenConnection(aUrl));
  EXPECT_TRUE(pCHttpsURLConnection->HttpsSetSkipVerifications(false, false));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetFollowRedirection(true));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetOutputHeaderBodyToSeparateFiles(aFdHeader, aFdBody));
  EXPECT_TRUE(pCHttpsURLConnection->Perform());
  showPerformResult(pCHttpsURLConnection);

  if (aFdHeader)
  {
    fclose(aFdHeader);
  }

  if (aFdBody)
  {
    fclose(aFdBody);
  }

  delete pCHttpsURLConnection;
}

TEST_F(CHttpsURLConnectionTest, HttpSetOutputHeaderBodyToSeparateMemorys)
{
  std::string aUrl = "https://example.com/";
  struct TMemoryStructGET headerChunk;
  struct TMemoryStructGET bodyChunk;

  headerChunk.memory = (char*)malloc(1); // will be grown as needed by the realloc() in write_data_to_memory()
  headerChunk.size = 0; // no data at this point
  bodyChunk.memory = (char*)malloc(1); // will be grown as needed by the realloc() in write_data_to_memory()
  bodyChunk.size = 0; // no data at this point

  CHttpsURLConnection* pCHttpsURLConnection = new CHttpsURLConnection();
  EXPECT_TRUE(NULL != pCHttpsURLConnection);
  EXPECT_TRUE(pCHttpsURLConnection->OpenConnection(aUrl));
  EXPECT_TRUE(pCHttpsURLConnection->HttpsSetSkipVerifications(false, false));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetFollowRedirection(true));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetOutputHeaderBodyToSeparateMemorys(&headerChunk, &bodyChunk));
  EXPECT_TRUE(pCHttpsURLConnection->Perform());

  // Now, our chunk.memory points to a memory block that is chunk.size bytes big and contains the remote file.
  printf("headerChunk.size: %lu bytes retrieved\n", (long)headerChunk.size);
  printf("bodyChunk.size: %lu bytes retrieved\n", (long)bodyChunk.size);
  printf("-------------------------------\n");
    if (0 != headerChunk.size)
      printf("%s\n", headerChunk.memory);
  printf("-------------------------------\n");
    if (0 != bodyChunk.size)
      printf("%s\n", bodyChunk.memory);
  printf("-------------------------------\n");

  showPerformResult(pCHttpsURLConnection);

  if(headerChunk.memory)
    free(headerChunk.memory);
  if(bodyChunk.memory)
    free(bodyChunk.memory);

  delete pCHttpsURLConnection;
}

TEST_F(CHttpURLConnectionFactoryTest, useCHttpURLConnectionFactory)
{
  std::string aUrl = "http://example.com/";

  CHttpURLConnection* pCHttpURLConnection = CHttpURLConnectionFactory::GetInstance().createConnection(aUrl);
  EXPECT_TRUE(NULL != pCHttpURLConnection);
  EXPECT_TRUE(pCHttpURLConnection->HttpSetFollowRedirection(true));
  EXPECT_TRUE(pCHttpURLConnection->Perform());

  showPerformResult(pCHttpURLConnection);
}

TEST_F(CHttpsURLConnectionFactoryTest, useCHttpsURLConnectionFactory)
{
  std::string aUrl = "https://example.com/";

  CHttpsURLConnection* pCHttpsURLConnection = CHttpsURLConnectionFactory::GetInstance().createConnection(aUrl);
  EXPECT_TRUE(NULL != pCHttpsURLConnection);
  EXPECT_TRUE(pCHttpsURLConnection->HttpsSetSkipVerifications(false, false));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetFollowRedirection(true));
  EXPECT_TRUE(pCHttpsURLConnection->Perform());

  showPerformResult(pCHttpsURLConnection);
}

TEST_F(CHttpsURLConnectionFactoryTest, HttpsFactoryGetLoginTokenToMemoryChunk)
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

  // Now, our chunk.memory points to a memory block that is chunk.size
  // bytes big and contains the remote file.
  //
  // Do something nice with it!
  printf("headerChunk.size: %lu bytes retrieved\n", (long)headerChunk.size);
  printf("bodyChunk.size: %lu bytes retrieved\n", (long)bodyChunk.size);
  printf("-------------------------------\n");
    if (0 != headerChunk.size)
      printf("%s\n", headerChunk.memory);
  printf("-------------------------------\n");
    if (0 != bodyChunk.size)
      printf("%s\n", bodyChunk.memory);
  printf("-------------------------------\n");

  showPerformResult(pCHttpsURLConnection);

  if(headerChunk.memory)
    free(headerChunk.memory);
  if(bodyChunk.memory)
    free(bodyChunk.memory);

}

TEST_F(CHttpsURLConnectionPOSTPUTTest, HttpsPOSTTest)
{
  //std::string aUrl = "http://example.com/index.cgi";
  //const char* POSTdata = "this is what we post to the silly web server";

  std::string aUrl = "https://example.com/";
  const char* POSTdata = "{\"key\":\"the is a test body to server\"}";

  // For server response datas.
  struct TMemoryStructGET headerChunk;
  struct TMemoryStructGET bodyChunk;
  headerChunk.memory = (char*)malloc(1); // will be grown as needed by the realloc() in write_data_to_memory()
  headerChunk.size = 0; // no data at this point
  bodyChunk.memory = (char*)malloc(1); // will be grown as needed by the realloc() in write_data_to_memory()
  bodyChunk.size = 0; // no data at this point

  CHttpsURLConnection* pCHttpsURLConnection = new CHttpsURLConnection();
  EXPECT_TRUE(NULL != pCHttpsURLConnection);
  EXPECT_TRUE(pCHttpsURLConnection->OpenConnection(aUrl));
  EXPECT_TRUE(pCHttpsURLConnection->HttpsSetSkipVerifications(false, false));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetFollowRedirection(false));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetVerbose(true));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetOutputHeaderBodyToSeparateMemorys(&headerChunk, &bodyChunk));

  struct TMemoryStructPOSTPUT memoryChunk;
  memoryChunk.data = POSTdata;
  memoryChunk.size = strlen(POSTdata);
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetHeader("Accept: application/vnd.server.cloud", "Content-Type: application/json; charset=UTF-8", NULL, NULL));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetPOSTFromBuffer(memoryChunk));
  EXPECT_TRUE(pCHttpsURLConnection->Perform());

  // Now, our chunk.memory points to a memory block that is chunk.size
  // bytes big and contains the remote file.
  //
  // Do something nice with it!
  printf("headerChunk.size: %lu bytes retrieved\n", (long)headerChunk.size);
  printf("bodyChunk.size: %lu bytes retrieved\n", (long)bodyChunk.size);
  printf("-------------------------------\n");
    if (0 != headerChunk.size)
      printf("%s\n", headerChunk.memory);
  printf("-------------------------------\n");
    if (0 != bodyChunk.size)
      printf("%s\n", bodyChunk.memory);
  printf("-------------------------------\n");

  showPerformResult(pCHttpsURLConnection);

  delete pCHttpsURLConnection;

  if(headerChunk.memory)
    free(headerChunk.memory);
  if(bodyChunk.memory)
    free(bodyChunk.memory);
}

TEST_F(CHttpsURLConnectionPOSTPUTTest, HttpsPUTTest)
{
  //std::string aUrl = "http://example.com/index.cgi";
  //const char* PUTdata = "this is what we post to the silly web server";

  std::string aUrl = "https://example.com/";
  const char* PUTdata = "{\"key\":\"the is a test body to server\"}";

  // For server response datas.
  struct TMemoryStructGET headerChunk;
  struct TMemoryStructGET bodyChunk;
  headerChunk.memory = (char*)malloc(1); // will be grown as needed by the realloc() in write_data_to_memory()
  headerChunk.size = 0; // no data at this point
  bodyChunk.memory = (char*)malloc(1); // will be grown as needed by the realloc() in write_data_to_memory()
  bodyChunk.size = 0; // no data at this point

  CHttpsURLConnection* pCHttpsURLConnection = new CHttpsURLConnection();
  EXPECT_TRUE(NULL != pCHttpsURLConnection);
  EXPECT_TRUE(pCHttpsURLConnection->OpenConnection(aUrl));
  EXPECT_TRUE(pCHttpsURLConnection->HttpsSetSkipVerifications(false, false));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetFollowRedirection(false));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetVerbose(true));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetOutputHeaderBodyToSeparateMemorys(&headerChunk, &bodyChunk));

  struct TMemoryStructPOSTPUT memoryChunk;
  memoryChunk.data = PUTdata;
  memoryChunk.size = strlen(PUTdata);
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetHeader(NULL, NULL, NULL, NULL));
  EXPECT_TRUE(pCHttpsURLConnection->HttpSetPUTFromBuffer(memoryChunk));
  EXPECT_TRUE(pCHttpsURLConnection->Perform());

  // Now, our chunk.memory points to a memory block that is chunk.size
  // bytes big and contains the remote file.
  //
  // Do something nice with it!
  printf("headerChunk.size: %lu bytes retrieved\n", (long)headerChunk.size);
  printf("bodyChunk.size: %lu bytes retrieved\n", (long)bodyChunk.size);
  printf("-------------------------------\n");
    if (0 != headerChunk.size)
      printf("%s\n", headerChunk.memory);
  printf("-------------------------------\n");
    if (0 != bodyChunk.size)
      printf("%s\n", bodyChunk.memory);
  printf("-------------------------------\n");

  showPerformResult(pCHttpsURLConnection);

  delete pCHttpsURLConnection;

  if(headerChunk.memory)
    free(headerChunk.memory);
  if(bodyChunk.memory)
    free(bodyChunk.memory);
}

