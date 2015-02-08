project(RESTfulClientAPIs_Test)
  message(STATUS "*** PROJECT_NAME = ${PROJECT_NAME}")

set(RESTfulClientAPIs_Test_ROOT ${CMAKE_CURRENT_LIST_DIR} CACHE STRING "RESTfulClientAPIs_Test_ROOT root directory")
  message(STATUS "*** RESTfulClientAPIs_Test_ROOT = ${RESTfulClientAPIs_Test_ROOT}")

#if(UNIT_TESTS)
  add_subdirectory(
	  ${CMAKE_CURRENT_SOURCE_DIR}/Unittest
	  ${CMAKE_CURRENT_BINARY_DIR}/Unittest
  )
#endif(UNIT_TESTS)

# Add this project as a custom target, and add its dependency targets.
add_custom_target(${PROJECT_NAME} COMMENT "RESTfulClientAPIs_Test custom target")
add_dependencies(${PROJECT_NAME} RESTfulClientAPIs_Test_Unittest)
