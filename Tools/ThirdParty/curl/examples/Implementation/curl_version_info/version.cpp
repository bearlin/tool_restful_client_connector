// cURL get version exmaple

#include <iostream>
#include <curl/curl.h>

int main(int, char*[]) 
{
  curl_global_init(CURL_GLOBAL_ALL);
  
  std::cout << "cURL version :" << curl_version() << std::endl;

  //http://curl.haxx.se/libcurl/c/curl_version_info.html
  //---------------------------------------------------
  curl_version_info_data* data;
  data = curl_version_info(CURLVERSION_NOW);
  printf("data->age:%d\n", data->age);

  if (data->age >= 0)
  {
    printf("data->version:%s\n", data->version);
    printf("data->version_num:0x%x\n", data->version_num);
    printf("data->host:%s\n", data->host);
    printf("data->features:0x%x\n", data->features);
    printf("data->ssl_version:%s\n", data->ssl_version);
    printf("data->ssl_version_num:%ld\n", data->ssl_version_num);
    printf("data->libz_version:%s\n", data->libz_version);

    printf("data->protocols[]: ");
    int i = 0;
    const char* proto = NULL;
    for (proto = data->protocols[i]; NULL != proto; i++)
    {
      proto = data->protocols[i];
      printf("%s, ", proto);
    }
    printf("\n");
  }
  if (data->age >= 1)
  {
    printf("data->ares:%s\n", data->ares);
    printf("data->ares_num:%d\n", data->ares_num);
  }
  if (data->age >= 2)
  {
    printf("data->libidn:%s\n", data->libidn);
  }
  if (data->age >= 3)
  {
    printf("data->iconv_ver_num:%d\n", data->iconv_ver_num);
    printf("data->libssh_version:%s\n", data->libssh_version);
  }
  //---------------------------------------------------
  
  return 0;
}
