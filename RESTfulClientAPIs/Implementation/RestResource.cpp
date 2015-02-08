//! @file RestResource.cpp
//!
//! @brief
//!

#include "RestResource.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// List of resources which can be accessed via REST.
const char* KSESSIONS = "sessions";
const char* KSTREAMING = "streaming";
const char* KACTIVE_ROUTE = "routes/active";
const char* KFAVORITES = "favorites/locations";
const char* KUSER_PROFILE_DATA = "profile";
const char* KPRIVACY_AGREEMENT = "agreement";
const char* KFORGET_ME = "forgetme";
const char* KMY_WORLD = "thirdparty/myworld";
const char* KPING = "ping";
const char* KPOI_DOWNLOAD_URLS = "pois/download";
const char* KPOI = "pois";

CRestResource::CRestResource(std::string aPath) :
  iPath(aPath)
{;}

CRestResource::~CRestResource()
{;}

std::string CRestResource::getResourceUrlWithAlternativePath(std::string aServerURL, std::string aAlternativePath)
{
  std::string url;

  if (0 == aAlternativePath.length())
    url = aServerURL + "/" + iPath;
  else
    url = aServerURL + "/" + aAlternativePath + '/' + iPath;

  return url;
}

std::string CRestResource::getResourceUrl(std::string aServerURL)
{
  return getResourceUrlWithAlternativePath(aServerURL, std::string(""));
}

