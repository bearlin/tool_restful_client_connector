//! @file CCloudServerTest.cpp
//!
//! @brief 
//!

#include "CloudClientCommon.h"
#include "CloudServer.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;

class CCloudServerTest: public ::testing::Test
{
};

TEST_F(CCloudServerTest, createCCloudServer)
{
  std::string serverUrl;
  
  CCloudServer* cloudServer = new CCloudServer(KCLOUD_SERVER);
  EXPECT_TRUE(NULL != cloudServer);
  serverUrl = cloudServer->getServerUrl();
  EXPECT_TRUE(0 != serverUrl.length());
  printf("serverUrl:%s\n", serverUrl.c_str());

  delete cloudServer;
}

