set(ThirdParty_cares_ROOT ${CMAKE_CURRENT_LIST_DIR} CACHE STRING "ThirdParty_cares_ROOT directory")
  #message(STATUS "*** ThirdParty_cares_ROOT = ${ThirdParty_cares_ROOT}")
  
# libcares 
add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/libcares 
	${CMAKE_CURRENT_BINARY_DIR}/libcares)
