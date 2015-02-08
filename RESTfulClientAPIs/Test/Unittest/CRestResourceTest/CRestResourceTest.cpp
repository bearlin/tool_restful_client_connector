//! @file RestResource.cpp
//!
//! @brief 
//!

#include "CloudClientCommon.h"
#include "RestResource.h"
#include "CloudServer.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;

class CRestResourceTest: public ::testing::Test
{
};

TEST_F(CRestResourceTest, createCRestResource)
{
  std::string serverUrl;
  std::string resourceUrl;
  
  CCloudServer* cloudServer = new CCloudServer(KCLOUD_SERVER);
  serverUrl = cloudServer->getServerUrl();
  printf("serverUrl:%s\n", serverUrl.c_str());
  
  //"https://example.com/api/agreement"
  CRestResource* restResource = new CRestResource(KPRIVACY_AGREEMENT);
  EXPECT_TRUE(NULL != restResource);
  resourceUrl = restResource->getResourceUrl(cloudServer->getServerUrl());
  EXPECT_TRUE(0 != resourceUrl.length());
  printf("KPRIVACY_AGREEMENT resourceUrl:%s\n", resourceUrl.c_str());
  EXPECT_TRUE(0 == resourceUrl.compare(std::string(KCLOUD_SERVER)+"/"+KPRIVACY_AGREEMENT));
  delete restResource;

  //"https://example.com/api/sessions"
  restResource = new CRestResource(KSESSIONS);
  EXPECT_TRUE(NULL != restResource);
  resourceUrl = restResource->getResourceUrl(cloudServer->getServerUrl());
  EXPECT_TRUE(0 != resourceUrl.length());
  printf("KSESSIONS resourceUrl:%s\n", resourceUrl.c_str());
  EXPECT_TRUE(0 == resourceUrl.compare(std::string(KCLOUD_SERVER)+"/"+KSESSIONS));
  delete restResource;

  //"https://example.com/api/routes/active"
  restResource = new CRestResource(KACTIVE_ROUTE);
  EXPECT_TRUE(NULL != restResource);
  resourceUrl = restResource->getResourceUrl(cloudServer->getServerUrl());
  EXPECT_TRUE(0 != resourceUrl.length());
  printf("KACTIVE_ROUTE resourceUrl:%s\n", resourceUrl.c_str());
  EXPECT_TRUE(0 == resourceUrl.compare(std::string(KCLOUD_SERVER)+"/"+KACTIVE_ROUTE));

  delete restResource;
  delete cloudServer;
}

