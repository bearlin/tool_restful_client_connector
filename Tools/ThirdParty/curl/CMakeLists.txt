set(ThirdParty_curl_ROOT ${CMAKE_CURRENT_LIST_DIR} CACHE STRING "ThirdParty_curl_ROOT directory")
  #message(STATUS "*** ThirdParty_curl_ROOT = ${ThirdParty_curl_ROOT}")
  
# libcurl 
add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/libcurl 
	${CMAKE_CURRENT_BINARY_DIR}/libcurl)

# examples 
add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/examples 
	${CMAKE_CURRENT_BINARY_DIR}/examples)
