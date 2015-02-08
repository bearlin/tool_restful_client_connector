set(Tools_ROOT ${CMAKE_CURRENT_LIST_DIR} CACHE STRING "Tools root directory")
  #message(STATUS "*** Tools_ROOT = ${Tools_ROOT}")
  
# ThirdParty 
add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty
	${CMAKE_CURRENT_BINARY_DIR}/ThirdParty)
    
