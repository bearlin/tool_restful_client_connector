project(cares)
  message(STATUS "*** PROJECT_NAME = ${PROJECT_NAME}")

set(ThirdParty_cares_libcurl_ROOT ${PROJECT_SOURCE_DIR} CACHE STRING "ThirdParty_cares_libcurl_ROOT directory")

# Select x86 or x64 cares.
set(ImplementationDir "Implementation/Linux_x86") # already configured as x86.
#set(ImplementationDir "Implementation/Linux_x64") # already configured as x64.

# Definition of the C-Ares API INCLUDES
set(ThirdParty_cares_libcares_API_INCLUDES
  ${ThirdParty_cares_libcurl_ROOT}/${ImplementationDir}/c-ares
  CACHE STRING "C_ARES API INCLUDES path")

#Include path
include_directories( ${ThirdParty_cares_libcares_API_INCLUDES} )

# Header files
file_glob( C_ARES_HEADER_FILES ${ThirdParty_cares_libcurl_ROOT}/${ImplementationDir}/c-ares/*.h)

# Core files
file_glob( C_ARES_CORE ${ThirdParty_cares_libcurl_ROOT}/${ImplementationDir}/c-ares/*.c)

# Append all C_ARES files
list(APPEND C_ARES_FILES ${C_ARES_CORE})

add_definitions(-DHAVE_CONFIG_H)

# C_ARES - build static library.
add_library(${PROJECT_NAME} STATIC ${C_ARES_FILES} ${C_ARES_HEADER_FILES})

disable_warnings_as_errors_on_target(${PROJECT_NAME})

if (WIN32)
	#this method adds the necessary compiler flag
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0x0501")
	#this adds a preprocessor definition to the project
	add_definitions(-D_WIN32_WINNT=0x0501)
    
	add_definitions(-DCARES_STATICLIB)
        
	add_msvc_perforce_properties()
	set_target_msvc_solution_folder(${PROJECT_NAME} "ThirdParty/C_ARES")

endif (WIN32)
