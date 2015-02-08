project(gmock_examples)
  message(STATUS "*** PROJECT_NAME = ${PROJECT_NAME}")

set(Tools_ThirdParty_googlemock_examples_gmock_ROOT ${CMAKE_CURRENT_LIST_DIR} CACHE STRING "Tools_ThirdParty_googlemock_examples_gmock_ROOT root directory")
  #message(STATUS "*** Tools_ThirdParty_googlemock_examples_gmock_ROOT = ${Tools_ThirdParty_googlemock_examples_gmock_ROOT}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
  
# Definition of the googlemock_examples include files
set(Tools_ThirdParty_googlemock_examples_gmock_API_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/Interface
    ${CMAKE_CURRENT_LIST_DIR}/Implementation
    ${CMAKE_CURRENT_LIST_DIR}/Implementation/samples
    CACHE STRING "Tools_ThirdParty_googlemock_examples_gmock_API_INCLUDES path")
  #message(STATUS "*** using variable 'Tools_ThirdParty_googlemock_examples_gmock_API_INCLUDES'=${Tools_ThirdParty_googlemock_examples_gmock_API_INCLUDES}")
  
# Make a list of the source files we use.
file(GLOB SOURCE_FILES_EX1 ${CMAKE_CURRENT_LIST_DIR}/Implementation/samples/sample1.cc ${CMAKE_CURRENT_LIST_DIR}/Implementation/samples/sample1_*.cc)

# Make a list of the header (h) files we use.
file(GLOB HEADER_FILES_EX1 ${CMAKE_CURRENT_LIST_DIR}/Implementation/samples/sample1*.h)
  #message(">>>>>  SOURCE_FILES_EX1 = ${SOURCE_FILES_EX1}")
  #message(">>>>>  HEADER_FILES_EX1 = ${HEADER_FILES_EX1}")

# Specify resulting executable.
add_executable( ${PROJECT_NAME}_sample1_unittest ${HEADER_FILES_EX1} ${SOURCE_FILES_EX1})

# Specify include directories.
include_directories( ${CMAKE_CURRENT_LIST_DIR}/include )
include_directories(
    ${Tools_ThirdParty_googlemock_examples_gmock_API_INCLUDES}
    ${ThirdParty_googlemock_libgtest_API_INCLUDES} 
    ${ThirdParty_googlemock_libgmock_API_INCLUDES} 
    )
  #message(STATUS "*** using variable 'ThirdParty_googlemock_libgtest_API_INCLUDES'=${ThirdParty_googlemock_libgtest_API_INCLUDES}")
  #message(STATUS "*** using variable 'ThirdParty_googlemock_libgmock_API_INCLUDES'=${ThirdParty_googlemock_libgmock_API_INCLUDES}")

# Specify link libs.
target_link_libraries(${PROJECT_NAME}_sample1_unittest gmock_main)

#disable_warnings_as_errors_on_target(${PROJECT_NAME}_sample1_unittest)


