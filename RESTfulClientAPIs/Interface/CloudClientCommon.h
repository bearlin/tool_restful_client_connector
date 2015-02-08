//! @file CloudClientCommon.h
//!
//! @brief
//!

#ifndef _NAV_CLOUD_CLIENT_COMMON_H_
#define _NAV_CLOUD_CLIENT_COMMON_H_

#include <string>
#include <stdlib.h>
#include <cstring>
#include <cassert>

// Const values.
extern const char* KCLOUD_SERVER;

extern const unsigned char* KMacKey;
extern const unsigned char* KEncryptionKey;
extern const char* KPublicKey;

enum THttpMethod
{
  EGET = 0,
  EPUT,
  EPOST
};

class CDate
{
private:

public:
  //! @brief    Get current TimeStamp presented as strings using a restricted ISO8601 format.
  //!           Comply with Java format: Local time "2014-04-25T13:47:42.456Z"
  //! @return   A TimeStamp string.
  static std::string GetLocalTimeStamp();
};

//! @brief                  Trim string with delimiters.
//! @param[in]  aStr        String to be trimmed.
//! @param[in]  delimiters  Delimiters used to trim the input string.
//! @return                 A new string after trimmed.
extern std::string trimStr(std::string aStr, const char* delimiters);

#endif  // _NAV_CLOUD_CLIENT_COMMON_H_