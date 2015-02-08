
#ifndef RESTFULCLIENTAPIS_CLOUDSERVER_H
#define RESTFULCLIENTAPIS_CLOUDSERVER_H

#include <string>
#include <stdlib.h>

class CCloudServer
{
private:
  std::string iServerUrl;

public:
  // Constructors and destructors
  CCloudServer(std::string aServerUrl);
  ~CCloudServer();

  //! @brief    Get cloud server URL.
  //! @return   A string representing cloud server URL.
  std::string getServerUrl();
};

#endif // RESTFULCLIENTAPIS_CLOUDSERVER_H