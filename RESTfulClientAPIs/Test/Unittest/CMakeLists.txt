project(RESTfulClientAPIs_Test_Unittest)
  #message(STATUS "*** PROJECT_NAME = ${PROJECT_NAME}")

set(RESTfulClientAPIs_Test_Unittest_ROOT ${CMAKE_CURRENT_LIST_DIR} CACHE STRING "RESTfulClientAPIs_Test_Unittest_ROOT root directory")
  #message(STATUS "*** RESTfulClientAPIs_Test_Unittest_ROOT = ${RESTfulClientAPIs_Test_Unittest_ROOT}")

add_subdirectory(
  ${CMAKE_CURRENT_SOURCE_DIR}/CHttpURLConnectionTest
  ${CMAKE_CURRENT_BINARY_DIR}/CHttpURLConnectionTest
)

add_subdirectory(
  ${CMAKE_CURRENT_SOURCE_DIR}/CRestResourceTest
  ${CMAKE_CURRENT_BINARY_DIR}/CRestResourceTest
)

add_subdirectory(
  ${CMAKE_CURRENT_SOURCE_DIR}/CCloudServerTest
  ${CMAKE_CURRENT_BINARY_DIR}/CCloudServerTest
)

add_subdirectory(
  ${CMAKE_CURRENT_SOURCE_DIR}/CServerResponseTest
  ${CMAKE_CURRENT_BINARY_DIR}/CServerResponseTest
)

add_subdirectory(
  ${CMAKE_CURRENT_SOURCE_DIR}/CRestClientTest
  ${CMAKE_CURRENT_BINARY_DIR}/CRestClientTest
)

# List of LocationTransferProtocol_Unittest targets
list(APPEND RESTfulClientAPIs_Test_Unittest_LIST
  RESTfulClientAPIs_Test_Unittest_CHttpURLConnectionTest
  RESTfulClientAPIs_Test_Unittest_CRestResourceTest
  RESTfulClientAPIs_Test_Unittest_CCloudServerTest
  RESTfulClientAPIs_Test_Unittest_CServerResponseTest
  RESTfulClientAPIs_Test_Unittest_CRestClientTest)

# Add this project as a custom target, and add its dependency targets.
add_custom_target(${PROJECT_NAME} DEPENDS ${RESTfulClientAPIs_Test_Unittest_LIST} COMMENT "RESTfulClientAPIs_Test_Unittest custom target")

