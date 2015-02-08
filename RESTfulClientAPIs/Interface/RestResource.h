//! @file RestResource.h
//!
//! @brief
//!

#ifndef _REST_RESOURCE_H_
#define _REST_RESOURCE_H_

#include <string>

extern const char* KSESSIONS;
extern const char* KSTREAMING;
extern const char* KACTIVE_ROUTE;
extern const char* KFAVORITES;
extern const char* KUSER_PROFILE_DATA;
extern const char* KPRIVACY_AGREEMENT;
extern const char* KFORGET_ME;
extern const char* KMY_WORLD;
extern const char* KPING;
extern const char* KPOI_DOWNLOAD_URLS;
extern const char* KPOI;

class CRestResource
{
private:
  std::string iPath;

public:
  CRestResource(std::string aPath);
  virtual ~CRestResource();

  //! @brief                      Obtain the URL for this resource.
  //! @param[in] aServerURL       The main server URL at which the Cloud API is available.
  //! @param[in] aAlternativePath The alternative server URL at which the Cloud API is available.
  //! @return                     The URL for this resource, constructed from the server URL.
  std::string getResourceUrlWithAlternativePath(std::string aServerURL, std::string aAlternativePath);

  //! @brief                      Obtain the URL for this resource.
  //! @param[in] aServerURL       The main server URL at which the Cloud API is available.
  //! @return                     The URL for this resource, constructed from the server URL.
  std::string getResourceUrl(std::string aServerURL);
};

#endif //_REST_RESOURCE_H_
