cmake_minimum_required(VERSION 2.8)

project(RESTfulClientConnector)
  message(STATUS "*** PROJECT_NAME = ${PROJECT_NAME}")

# -------------------------------------------------------------------
## -fPIC: http://stackoverflow.com/questions/5311515/gcc-fpic-option
## -m32: http://stackoverflow.com/questions/2426478/when-should-m32-option-of-gcc-be-used

# Build x86 binary 
set(CMAKE_CXX_FLAGS "-Wall -Werror -m32 -fPIC") 
set(CMAKE_C_FLAGS "-Wall -Werror -m32 -fPIC") 
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/lib/i386-linux-gnu) # This is important to tell CMAKE to find those 64-bits libraries.

# Build x64 binary 
#set(CMAKE_CXX_FLAGS "-Wall -Werror -m64 -fPIC") 
#set(CMAKE_C_FLAGS "-Wall -Werror -m64 -fPIC") 
#set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/lib/x86_64-linux-gnu) # This is important to tell CMAKE to find those 64-bits libraries.
# -------------------------------------------------------------------

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(${CMAKE_CURRENT_LIST_DIR}/Util-Conf.cmake)

set(RESTfulClientConnector_ROOT ${CMAKE_CURRENT_LIST_DIR} CACHE STRING "RESTfulClientConnector root directory")
  message(STATUS "*** RESTfulClientConnector_ROOT = ${RESTfulClientConnector_ROOT}")

# Tools 
add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/Tools 
	${CMAKE_CURRENT_BINARY_DIR}/Tools)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/RESTfulClientAPIs
	${CMAKE_CURRENT_BINARY_DIR}/RESTfulClientAPIs)

