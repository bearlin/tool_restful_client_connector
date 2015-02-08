project(curl_examples)
  message(STATUS "*** PROJECT_NAME = ${PROJECT_NAME}")

set(ThirdParty_curl_examples_ROOT ${CMAKE_CURRENT_LIST_DIR} CACHE STRING "ThirdParty_curl_examples_ROOT directory")
  #message(STATUS "*** ThirdParty_curl_examples_ROOT = ${ThirdParty_curl_examples_ROOT}")
  
set(CURL_EX1 "curl_version_info")
set(CURL_EX2 "simpleHTTP")
set(CURL_EX3 "simpleHTTPS")
set(CURL_EX4 "getHTTPWithHeadersSeparate")
set(CURL_EX5 "cacertinmem")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
  
# Definition of include files
set(ThirdParty_curl_examples_API_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/Interface
    CACHE STRING "ThirdParty_curl_examples_API_INCLUDES path")
  #message(STATUS "*** using variable 'ThirdParty_curl_examples_API_INCLUDES'=${ThirdParty_curl_examples_API_INCLUDES}")

# Make a list of the source files we use.
file(GLOB SOURCE_FILES_EX1 ${CMAKE_CURRENT_LIST_DIR}/Implementation/${CURL_EX1}/*.cpp)
file(GLOB SOURCE_FILES_EX2 ${CMAKE_CURRENT_LIST_DIR}/Implementation/${CURL_EX2}/*.cpp)
file(GLOB SOURCE_FILES_EX3 ${CMAKE_CURRENT_LIST_DIR}/Implementation/${CURL_EX3}/*.cpp)
file(GLOB SOURCE_FILES_EX4 ${CMAKE_CURRENT_LIST_DIR}/Implementation/${CURL_EX4}/*.cpp)
file(GLOB SOURCE_FILES_EX5 ${CMAKE_CURRENT_LIST_DIR}/Implementation/${CURL_EX5}/*.cpp)
# Make a list of the header (h) files we use.
file(GLOB HEADER_FILES_EX1 ${CMAKE_CURRENT_LIST_DIR}/Implementation/${CURL_EX1}/*.h)
file(GLOB HEADER_FILES_EX2 ${CMAKE_CURRENT_LIST_DIR}/Implementation/${CURL_EX2}/*.h)
file(GLOB HEADER_FILES_EX3 ${CMAKE_CURRENT_LIST_DIR}/Implementation/${CURL_EX3}/*.h)
file(GLOB HEADER_FILES_EX4 ${CMAKE_CURRENT_LIST_DIR}/Implementation/${CURL_EX4}/*.h)
file(GLOB HEADER_FILES_EX5 ${CMAKE_CURRENT_LIST_DIR}/Implementation/${CURL_EX5}/*.h)
  #message(">>>>>  SOURCE_FILES_EX1 = ${SOURCE_FILES_EX1}")
  #message(">>>>>  HEADER_FILES_EX1 = ${HEADER_FILES_EX1}")
  #message(">>>>>  SOURCE_FILES_EX2 = ${SOURCE_FILES_EX2}")
  #message(">>>>>  HEADER_FILES_EX2 = ${HEADER_FILES_EX2}")
  #message(">>>>>  SOURCE_FILES_EX3 = ${SOURCE_FILES_EX3}")
  #message(">>>>>  HEADER_FILES_EX3 = ${HEADER_FILES_EX3}")
  #message(">>>>>  SOURCE_FILES_EX4 = ${SOURCE_FILES_EX4}")
  #message(">>>>>  HEADER_FILES_EX4 = ${HEADER_FILES_EX4}")
  #message(">>>>>  SOURCE_FILES_EX5 = ${SOURCE_FILES_EX5}")
  #message(">>>>>  HEADER_FILES_EX5 = ${HEADER_FILES_EX5}")
  
# Specify resulting executable.
add_executable( ${PROJECT_NAME}_${CURL_EX1} ${SOURCE_FILES_EX1} ${HEADER_FILES_EX1})
add_executable( ${PROJECT_NAME}_${CURL_EX2} ${SOURCE_FILES_EX2} ${HEADER_FILES_EX2})
add_executable( ${PROJECT_NAME}_${CURL_EX3} ${SOURCE_FILES_EX3} ${HEADER_FILES_EX3})
add_executable( ${PROJECT_NAME}_${CURL_EX4} ${SOURCE_FILES_EX4} ${HEADER_FILES_EX4})
add_executable( ${PROJECT_NAME}_${CURL_EX5} ${SOURCE_FILES_EX5} ${HEADER_FILES_EX5})

# Specify include directories.
include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/Implementation/
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${ThirdParty_curl_examples_API_INCLUDES}
    ${ThirdParty_curl_libcurl_API_INCLUDES}
    )
  #message(STATUS "*** using variable 'ThirdParty_curl_libcurl_API_INCLUDES'=${ThirdParty_curl_libcurl_API_INCLUDES}")

# We need crypto.
find_library(CRYPTO_LIB crypto)
if (${CRYPTO_LIB} STREQUAL "CRYPTO_LIB-NOTFOUND")
  message(FATAL_ERROR "### ERROR ### Not found variable 'CRYPTO_LIB'.")
else()
  message(STATUS "*** using variable 'CRYPTO_LIB'=${CRYPTO_LIB}")
endif()

# Specify link libs.
target_link_libraries(${PROJECT_NAME}_${CURL_EX1} curl)
target_link_libraries(${PROJECT_NAME}_${CURL_EX2} curl)
target_link_libraries(${PROJECT_NAME}_${CURL_EX3} curl)
target_link_libraries(${PROJECT_NAME}_${CURL_EX4} curl)
target_link_libraries(${PROJECT_NAME}_${CURL_EX5} curl ${CRYPTO_LIB})
