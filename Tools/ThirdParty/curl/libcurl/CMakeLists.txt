project(curl)
  message(STATUS "*** PROJECT_NAME = ${PROJECT_NAME}")

set(ThirdParty_curl_libcurl_ROOT ${PROJECT_SOURCE_DIR} CACHE STRING "ThirdParty_curl_libcurl_ROOT directory")

# Select x86 or x64 curl.
if (${ArchType} STREQUAL "x86")
  set(ImplementationDir "Implementation/Linux_x86") # already configured as x86.
else()
  set(ImplementationDir "Implementation/Linux_x64") # already configured as x64.
endif()

# Definition of the cURL API INCLUDES
set(ThirdParty_curl_libcurl_API_INCLUDES
  ${ThirdParty_curl_libcurl_ROOT}/${ImplementationDir}
  ${ThirdParty_curl_libcurl_ROOT}/${ImplementationDir}/curl/
	CACHE STRING "curl API INCLUDES path")

#Include path
include_directories( 
    ${ThirdParty_curl_libcurl_API_INCLUDES} 
    ${ThirdParty_cares_libcares_API_INCLUDES}
)
  #message(STATUS "*** using variable 'ThirdParty_curl_libcurl_API_INCLUDES'=${ThirdParty_curl_libcurl_API_INCLUDES}")
  #message(STATUS "*** using variable 'ThirdParty_cares_libcares_API_INCLUDES'=${ThirdParty_cares_libcares_API_INCLUDES}")

# Header files
file_glob( CURL_HEADER_FILES ${ThirdParty_curl_libcurl_ROOT}/${ImplementationDir}/curl/*.h)

# Core files
file_glob( CURL_CORE ${ThirdParty_curl_libcurl_ROOT}/${ImplementationDir}/curl/*.c)

# Append all Curl files
list(APPEND CURL_FILES ${CURL_CORE})

add_definitions(-DHAVE_CONFIG_H)

# Curl - build static library.
add_library(${PROJECT_NAME} STATIC ${CURL_FILES} ${CURL_HEADER_FILES})

# We need z.
find_library(Z_LIB z)
if (${Z_LIB} STREQUAL "Z_LIB-NOTFOUND")
  message(FATAL_ERROR "### ERROR ### Not found variable 'Z_LIB'.")
else()
  message(STATUS "*** using variable 'Z_LIB'=${Z_LIB}")
endif()

# We need crypto.
find_library(CRYPTO_LIB crypto)
if (${CRYPTO_LIB} STREQUAL "CRYPTO_LIB-NOTFOUND")
  message(FATAL_ERROR "### ERROR ### Not found variable 'CRYPTO_LIB'.")
else()
  message(STATUS "*** using variable 'CRYPTO_LIB'=${CRYPTO_LIB}")
endif()

# We need ssl.
find_library(SSL_LIB ssl)
if (${SSL_LIB} STREQUAL "SSL_LIB-NOTFOUND")
  message(FATAL_ERROR "### ERROR ### Not found variable 'SSL_LIB'.")
else()
  message(STATUS "*** using variable 'SSL_LIB'=${SSL_LIB}")
endif()

# We need rt, the POSIX.1b Realtime Extensions library.
find_library(REALTIME_LIB rt)
if (${REALTIME_LIB} STREQUAL "REALTIME_LIB-NOTFOUND")
  message(FATAL_ERROR "### ERROR ### Not found variable 'REALTIME_LIB'.")
else()
  message(STATUS "*** using variable 'REALTIME_LIB'=${REALTIME_LIB}")
endif()

target_link_libraries(${PROJECT_NAME} 
  ${Z_LIB}
  ${SSL_LIB}
  ${CRYPTO_LIB}
  ${REALTIME_LIB}
  cares     # for cURL be thread safe: check http://curl.haxx.se/libcurl/c/libcurl-tutorial.html.
  )

disable_warnings_as_errors_on_target(${PROJECT_NAME})

if (WIN32)
	add_definitions(-DCURL_STATICLIB -DCURL_DISABLE_LDAP)
	add_msvc_perforce_properties()
	set_target_msvc_solution_folder(${PROJECT_NAME} "ThirdParty/Curl")
endif (WIN32)
