project(RESTfulClientAPIs_Test_Unittest_CHttpURLConnectionTest)
  message(STATUS "*** PROJECT_NAME = ${PROJECT_NAME}")

set(RESTfulClientAPIs_Test_Unittest_CHttpURLConnectionTest_ROOT ${CMAKE_CURRENT_LIST_DIR}
    CACHE STRING "RESTfulClientAPIs_Test_Unittest_CHttpURLConnectionTest_ROOT root directory")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Specify include directories.
include_directories(
    ${RESTfulClientAPIs_API_INCLUDES}
    ${ThirdParty_googlemock_libgtest_API_INCLUDES}
    ${ThirdParty_googlemock_libgmock_API_INCLUDES}
    )

# Core tests
file(GLOB UNITTEST_FILES_CPP ${RESTfulClientAPIs_Test_Unittest_CHttpURLConnectionTest_ROOT}/*.cpp)
file(GLOB UNITTEST_FILES_H ${RESTfulClientAPIs_Test_Unittest_CHttpURLConnectionTest_ROOT}/*.h)

#append all source files
list(APPEND COMMON_UNITTEST_FILES
	${UNITTEST_FILES_CPP}
	${UNITTEST_FILES_H}
	)

# Test executable
add_executable(${PROJECT_NAME} ${COMMON_UNITTEST_FILES})

target_link_libraries(${PROJECT_NAME}
    RESTfulClientAPIs
    gmock_main
    )
