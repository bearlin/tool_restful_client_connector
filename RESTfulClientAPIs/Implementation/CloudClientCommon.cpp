//! @file CloudClientCommon.cpp
//!
//! @brief
//!

#include "CloudClientCommon.h"

// Const values.
const char* KCLOUD_SERVER = "https://example.com/api";
const int KEY_SIZE = 17;

static const unsigned char* generateMacKey()
{
  static unsigned char macKey[KEY_SIZE];
  srand(time(NULL));
  for (int i = 0; i < KEY_SIZE - 1; i++)
  {
    macKey[i] = (rand() % 255) + 1;
  }

  macKey[KEY_SIZE - 1] = 0;
  return macKey;
}

static const unsigned char* generateEncryptionKey()
{
  static unsigned char encryptionKey[KEY_SIZE];
  srand(time(NULL) + 1);
  for (int i = 0; i < KEY_SIZE - 1; i++)
  {
    encryptionKey[i] = (rand() % 255) + 1;
  }

  encryptionKey[KEY_SIZE - 1] = 0;
  return encryptionKey;
}

const unsigned char* KMacKey = generateMacKey();
const unsigned char* KEncryptionKey = generateEncryptionKey();
const char* KPublicKey = "d0f1f4ace3ec2c008bf7272a36d3bf7ffb8aaabf8d7384c9a1d8e3985ff80e0ce3256d1b08b1f27e2ff6dad29674dd7c7c3175c6e8d8c8bb69ef569301a2571c2e4c5775c1785dc46fee835c05e4a5170840d3f78be99c7d25111e10c3be6f0daf871f6dabd5d40f8abecef38b9bc823a72f35de377523a391e6c9191d7d03831f602914a6d7fa1006a205f747cb3323d32831f4e9b6f9f4d2a89349571af39441fc8b5ef38736a338a5ba8d3006f2a9257fe6a6c893bf92d8cbf53f686455addbebc6d4ea3f4603214287ef3021def7ad3b0789b80bcced641853276bd56b00a8ac01ee8a9c65e86b822c845b3fcfa063571bd71e070c1c956522e90ed98789";

std::string CDate::GetLocalTimeStamp()
{
  // Timestamps are presented as strings using a restricted ISO8601 format:
  // YYYY-MM-DDThh:mm:ss.SSSZ ('T' and 'Z' are literal.).
  // EX: Local time "1997-07-16T19:20:30.450+0100" = GMT time "1997-07-16T18:20:30.450Z"
  // EX: Local time "2014-04-25T13:47:42.000+0800" = GMT time "2014-04-25T05:47:42.000Z"
  // Check http://www.w3.org/TR/NOTE-datetime, http://www.cl.cam.ac.uk/~mgk25/iso-time.html
  // Check http://www.cplusplus.com/reference/ctime/strftime/ about how to create this timestamp format.
  std::string timestamp;

  time_t rawtime;
  struct tm* timeinfo;
  char buffer[512];

  memset(buffer, 0, sizeof(buffer));

  time(&rawtime);
#if 1
  // Comply with Java format: Local time "2014-04-25T13:47:42.456Z"
  timeinfo = localtime(&rawtime); //Fill struct tm as local timezone.
  strftime(buffer, sizeof(buffer), "%FT%T.000Z", timeinfo);
#else
  #if 1
  timeinfo = gmtime(&rawtime);  //Fill struct tm as UTC time (i.e., the time at the GMT timezone).
  strftime(buffer, sizeof(buffer), "%FT%T.000Z", timeinfo);
  #else
  timeinfo = localtime(&rawtime); //Fill struct tm as local timezone.
  strftime(buffer, sizeof(buffer), "%FT%T.000%z", timeinfo);
  #endif
#endif

  timestamp = buffer;

  return timestamp;
}

std::string trimStr(std::string aStr, const char* delimiters)
{
  // Allocation memory.
  char* tmpStr = NULL;
  tmpStr = (char*)realloc(tmpStr, aStr.length()+1);
  if (NULL == tmpStr)
    return "";

  // Copy string content.
  strncpy(tmpStr, aStr.c_str(), aStr.length());
  tmpStr[aStr.length()] = '\0';

  // Trim string.
  char* pch;
  pch = strtok(tmpStr, delimiters);
  if (NULL == pch)
    return "";

  // Create new string.
  std::string newStr(pch, strlen(pch));

  // free
  free(tmpStr);

  return newStr;
}

