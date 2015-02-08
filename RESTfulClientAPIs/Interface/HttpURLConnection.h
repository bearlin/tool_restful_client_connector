//! @file HttpURLConnection.h
//!
//! @brief
//!

#ifndef _HTTPURLCONNECTION_H_
#define _HTTPURLCONNECTION_H_

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <cstdlib>
#include <cstring>
#include <map>

struct TMemoryStructGET {
  char *memory;
  size_t size;
};

struct TMemoryStructPOSTPUT {
  //http://curl.haxx.se/libcurl/c/post-callback.html
  const char *data;
  size_t size;
};

class CHttpURLConnection
{
protected:
  CURL* iCurl;
  CURLcode iRes;

private:
  std::string iUrl;
  FILE* iFdPUT;

  struct curl_slist* iHeaderList;

  // [Callback functions]
  //! @brief                This function gets called by libcurl as soon as there is data received that needs to be saved.
  //!                       The size of the data pointed to by ptr is size multiplied with nmemb, it will not be zero terminated.
  //! @param[in]  ptr       Pointer to the array of elements to be written, converted to a const void*.
  //! @param[in]  size      Size in bytes of each element to be written.
  //! @param[in]  nmemb     Number of elements, each one with a size of size bytes.
  //! @param[in]  userdata  Pointer to a FILE object that specifies an output stream.
  //! @return               Return the number of bytes actually taken care of. If that amount differs from the amount passed to your function, it'll signal an error to the library. 
  //!                       This will abort the transfer and return CURLE_WRITE_ERROR.
  static size_t write_data_to_file(void* ptr, size_t size, size_t nmemb, void* userdata);

  //! @brief                This function gets called by libcurl as soon as there is data received that needs to be saved.
  //!                       The size of the data pointed to by ptr is size multiplied with nmemb, it will not be zero terminated.
  //! @param[in]  ptr       Pointer to the array of elements to be written, converted to a const void*.
  //! @param[in]  size      Size in bytes of each element to be written.
  //! @param[in]  nmemb     Number of elements, each one with a size of size bytes.
  //! @param[in]  userdata  Pointer to a memory buffer that specifies an output stream.
  //! @return               Return the number of bytes actually taken care of. If that amount differs from the amount passed to your function, it'll signal an error to the library. 
  //!                       This will abort the transfer and return CURLE_WRITE_ERROR.
  static size_t write_data_to_memory(void* ptr, size_t size, size_t nmemb, void* userdata);

  //! @brief                This function gets called by libcurl as soon as it needs to read data in order to send it to the peer.
  //!                       The data area pointed at by the pointer ptr may be filled with at most size multiplied with nmemb number of bytes. 
  //! @param[in]  ptr       Pointer to a block of memory with a size of at least (size*nmemb) bytes, converted to a void*.
  //! @param[in]  size      Size, in bytes, of each element to be read.
  //! @param[in]  nmemb     Number of elements, each one with a size of size bytes.
  //! @param[in]  userdata  Pointer to a FILE object that specifies an input stream.
  //! @return               Return the actual number of bytes that you stored in that memory area. 
  //!                       Return 0 means end-of-file to the library and cause it to stop the current transfer.
  static size_t read_data_from_file(void* ptr, size_t size, size_t nmemb, void* userdata);

  //! @brief                This function gets called by libcurl as soon as it needs to read data in order to send it to the peer.
  //!                       The data area pointed at by the pointer ptr may be filled with at most size multiplied with nmemb number of bytes. 
  //! @param[in]  ptr       Pointer to a block of memory with a size of at least (size*nmemb) bytes, converted to a void*.
  //! @param[in]  size      Size, in bytes, of each element to be read.
  //! @param[in]  nmemb     Number of elements, each one with a size of size bytes.
  //! @param[in]  userdata  Pointer to a memory buffer that specifies an input stream.
  //! @return               Return the actual number of bytes that you stored in that memory area. 
  //!                       Return 0 means end-of-file to the library and cause it to stop the current transfer.
  static size_t read_data_from_memory(void *ptr, size_t size, size_t nmemb, void *userdata);
  
public:
  CHttpURLConnection();
  virtual ~CHttpURLConnection();

  // [Basic HTTP actions]
  //! @brief            Global libcurl initialisation, start a libcurl easy session, and set actual URL to deal with.
  //! @param[in]  aUrl  The actual URL to deal with, aUrl must be URL-encoded with format scheme://host:port/path.
  //! @return           Return true if success, else return false.
  virtual bool OpenConnection(std::string aUrl);

  //! @brief    Invoke this function after successfully OpenConnection() and all the HttpSetXXX() calls are made, and will perform the transfer as described in the options. 
  //! @return   Return true if success, else return false.
  virtual bool Perform();

  // [For HTTP options before perform]
  //! @brief                Set the aFollow to true to tells the library to follow any Location: header that the server sends as part of a HTTP header.
  //!                       This means that the library will re-send the same request on the new location and follow new Location: headers all the way until no more such headers are returned.
  //! @param[in]  aFollow   Enable/Disable follow. 
  //! @return               Return true if successfully set the value, else return false.
  bool HttpSetFollowRedirection(bool aFollow);

  //! @brief                Set the aVerbose to true to get the library to display a lot of verbose information about its operations.
  //! @param[in]  aVerbose  Enable/Disable verbose information. 
  //! @return               Return true if successfully set the value, else return false.
  bool HttpSetVerbose(bool aVerbose);

  //! @brief                  This function can be used to store the HTTP Header and Body datas(received from server) to file descriptors. 
  //! @param[out] aHeaderFd   A file descriptors which will contain the Header data received from server. 
  //! @param[out] aBodyFd     A file descriptors which will contain the Body data received from server. 
  //! @return                 Return true if successfully set the value, else return false.
  bool HttpSetOutputHeaderBodyToSeparateFiles(FILE *aHeaderFd, FILE *aBodyFd);

  //! @brief                    This function can be used to store the HTTP Header and Body datas(received from server) to memory buffers. 
  //! @param[out] aHeaderChunk  A memory data buffer which will contain the Header data received from server. 
  //! @param[out] aBodyChunk    A memory data buffer which will contain the Body data received from server. 
  //! @return                   Return true if successfully set the value, else return false.
  bool HttpSetOutputHeaderBodyToSeparateMemorys(struct TMemoryStructGET* aHeaderChunk, struct TMemoryStructGET* aBodyChunk);

  //! @brief                          Pass HTTP headers strings to the server and/or proxy in your HTTP request.
  //!                                 Pass all fields with NULL will reset back to no custom headers.
  //! @param[in] aHeaderAccept        Header string 1.
  //! @param[in] aHeaderContentType   Header string 2.
  //! @param[in] aExpect              Header string 3.
  //! @param[in] aCustom              Header string 4.
  //! @return                         Return true if successfully set the value, else return false.
  bool HttpSetHeader(const char* aHeaderAccept, const char* aHeaderContentType, const char* aExpect, const char* aCustom);

  //! @brief                  Pass HTTP headers to the server and/or proxy in your HTTP request.
  //!                         Pass a empty map will reset back to no custom headers.
  //! @param[in] aHeadersMap  A map of HTTP headers <key,value> pairs.
  //! @return                 Return true if successfully set the value, else return false.
  bool HttpSetHeaderFromMap(std::map<std::string, std::string>& aHeadersMap);

  //! @brief                Tells the library to prepare for an upload, and to use HTTP PUT to transfer data from a file descriptor.
  //! @param[in] aFilePath  A file descriptor contain the data for PUT. 
  //! @return               Return true if successfully set the value, else return false.
  bool HttpSetPUTFromFile(const char* aFilePath);

  //! @brief                  Tells the library to prepare for an upload, and to use HTTP PUT to transfer data in memory buffer.
  //! @param[in] memoryChunk  A memory data buffer contain the data for PUT. 
  //! @return                 Return true if successfully set the value, else return false.
  bool HttpSetPUTFromBuffer(struct TMemoryStructPOSTPUT& memoryChunk);

  //! @brief                  Tells the library to do a regular HTTP POST with data in memory buffer.
  //! @param[in] memoryChunk  A memory data buffer contain the data for POST. 
  //! @return                 Return true if successfully set the value, else return false.
  bool HttpSetPOSTFromBuffer(struct TMemoryStructPOSTPUT& memoryChunk);

  //! @brief                Pass a long as parameter containing the maximum time in seconds that you allow the http transfer operation to take.
  //!                       Default timeout is 0 (zero) which means it never times out.
  //! @param[in] aSeconds   The maximum time in seconds. 
  //! @return               Return true if successfully set the value, else return false.
  bool HttpSetTimeout(long aSeconds);

  //! @brief                    An alternative to HttpSetTimeout() but takes number of milliseconds instead.
  //!                           If both HttpSetTimeout() and HttpSetTimeoutMs() are set, the value set last will be used.
  //! @param[in] aMilliseconds  The maximum time in milliseconds. 
  //! @return                   Return true if successfully set the value, else return false.
  bool HttpSetTimeoutMs(long aMilliseconds);

  // [For HTTP informations after perform]
  //! @brief                  Pass a pointer to a char pointer to receive the last used effective URL.
  //! @param[out] aRespcode   Pointer to a char pointer to receive last used effective URL.
  //! @return                 Return true if successfully get the required information, else return false.
  bool HttpGetEffectiveUrl(char** aUrl);

  //! @brief                  Pass a pointer to a long to receive the last received HTTP, FTP or SMTP response code.
  //! @param[out] aRespcode   Pointer to a long to receive response code.
  //! @return                 Return true if successfully get the required information, else return false.
  bool HttpGetResponseCode(long* aRespcode);

  //! @brief                    Pass a pointer to a long to receive the total number of redirections that were actually followed.
  //! @param[out] aRedirectCnt  Pointer to a long to receive total redirections.
  //! @return                   Return true if successfully get the required information, else return false.
  bool HttpGetRedirectCount(long* aRedirectCnt);

  //! @brief            Pass a pointer to a char pointer to receive the URL a redirect would take you to if you would enable HttpSetFollowRedirection().
  //! @param[out] aUrl  Pointer to a char pointer to receive the redirect URL.
  //! @return           Return true if successfully get the required information, else return false.
  bool HttpGetRedirectUrl(char** aUrl);

  //! @brief                    Pass a pointer to a char pointer to receive the content-type of the downloaded object. 
  //!                           This is the value read from the Content-Type: field. 
  //!                           If you get NULL, it means that the server didn't send a valid Content-Type header or that the protocol used doesn't support this.
  //! @param[out] aContentType  Pointer to a char pointer to receive the content-type.
  //! @return                   Return true if successfully get the required information, else return false.
  bool HttpGetContentType(char** aContentType);

  // [Some handy APIs]
  //! @brief                  This function converts the given input string to an URL encoded string and returns that as a new allocated string. 
  //!                         You must UrlFreeEncodeDecodeStringBuffer() the returned string when you're done with it.
  //! @param[in] aStr         Pointer to a string need to be percent encoded.
  //! @param[in] aLength      If the aLength argument is set to 0 (zero), strlen() will be used on the input aStr string to find out the size.
  //! @return                 A pointer to a zero terminated string or NULL if it failed.
  char* UrlEncoding(const char* aStr, int aLength);

  //! @brief                    This function converts the given URL encoded input string to a "plain string" and returns that in an allocated memory area.
  //!                           You must UrlFreeEncodeDecodeStringBuffer() the returned string when you're done with it.
  //! @param[in]  aStr          Pointer to a string need to be percent decoded.
  //! @param[in]  aInLength     If the aInLength argument is set to 0 (zero), strlen() will be used on the input aStr string to find out the size.
  //! @param[out] aOutLength    If the aOutLength is non-NULL, the function will write the length of the returned string in the integer it points to.
  //! @return                   A pointer to a zero terminated string or NULL if it failed.
  char* UrlDecoding(const char* aStr, int aInLength, int* aOutLength);

  //! @brief            Reclaim memory that has been obtained  through UrlEncoding/UrlDecoding.
  //! @param[in] aStr   String pointer need to be free.
  //! @return           Void.
  void UrlFreeEncodeDecodeStringBuffer(char* aStr);

  //! @brief    Get current error codes in libcurl.
  //! @return   libcurl error codes.
  int getRespondCode();
};

#endif //_HTTPURLCONNECTION_H_
