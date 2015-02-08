
#include "CloudServer.h"

CCloudServer::CCloudServer(std::string aServerUrl) :
  iServerUrl(aServerUrl)
{;}

CCloudServer::~CCloudServer() {;}

std::string CCloudServer::getServerUrl()
{
  return iServerUrl;
}
