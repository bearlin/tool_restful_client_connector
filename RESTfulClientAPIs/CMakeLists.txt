project(RESTfulClientAPIs)
  message(STATUS "*** PROJECT_NAME = ${PROJECT_NAME}")

set(RESTfulClientAPIs_ROOT ${CMAKE_CURRENT_LIST_DIR}
    CACHE STRING "RESTfulClientAPIs_ROOT directory")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(RESTfulClientAPIs_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/Interface
    ${CMAKE_CURRENT_LIST_DIR}/Implementation
    CACHE STRING "RESTfulClientAPIs_INCLUDES path")

# Specify include directories.
include_directories(
    ${ThirdParty_curl_libcurl_API_INCLUDES}
    ${ThirdParty_rapidjson_librapidjson_API_INCLUDES}
    ${RESTfulClientAPIs_INCLUDES}
    )

# Make a list of the source files we use.
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_LIST_DIR}/Implementation/*.cpp)

# Make a list of the header (h) files we use.
file(GLOB HEADER_FILES ${CMAKE_CURRENT_LIST_DIR}/Interface/*.h)

# Specify resulting library.
add_library( ${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME}
                      curl
                      rapidjson
                      )

#if(UNIT_TESTS)
  add_subdirectory(
	  ${CMAKE_CURRENT_SOURCE_DIR}/Test
	  ${CMAKE_CURRENT_BINARY_DIR}/Test
  )
#endif(UNIT_TESTS)

