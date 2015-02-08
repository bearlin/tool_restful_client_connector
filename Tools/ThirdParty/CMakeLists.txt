set(Tools_ThirdParty_ROOT ${CMAKE_CURRENT_LIST_DIR} CACHE STRING "Tools ThirdParty root directory")
  #message(STATUS "*** Tools_ThirdParty_ROOT = ${Tools_ThirdParty_ROOT}")

# c-ares is being used by libcurl
add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/cares 
	${CMAKE_CURRENT_BINARY_DIR}/cares )
  
# curl
add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/curl 
	${CMAKE_CURRENT_BINARY_DIR}/curl)
  
# rapidjson 
add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/rapidjson 
	${CMAKE_CURRENT_BINARY_DIR}/rapidjson)

# gtest and gmock 
add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/googlemock 
	${CMAKE_CURRENT_BINARY_DIR}/googlemock)