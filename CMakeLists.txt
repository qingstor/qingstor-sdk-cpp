CMAKE_MINIMUM_REQUIRED(VERSION 3.2.3)

PROJECT(libQingStor)

SET(CMAKE_VERBOSE_MAKEFILE ON CACHE STRING "Verbose build." FORCE)

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

INCLUDE(Functions)
INCLUDE(Options)

IF (WIN32) 
	INCLUDE(ExternalProject)
	ADD_DEFINITIONS(-DWIN32)
ELSE ()
	INCLUDE(FindCURL)
	INCLUDE(FindOpenSSL)
	if(NOT CURL_FOUND)
		message(FATAL_ERROR "Could not find curl")
	endif()
	if(NOT OPENSSL_FOUND)
		message(FATAL_ERROR "Could not find openssl")
	endif()
	OPTION (INSTALL_SDK_HEADERS "Request installation of headers." ON)
	OPTION (OPTIMIZE_SPACE "Build with size-optimized options to reduce code size." OFF)
ENDIF()  

# add preprocesser macro
ADD_DEFINITIONS(-DCURL_STATICLIB)
ADD_DEFINITIONS(-DYAML_DECLARE_STATIC)

IF (WIN32) 
ADD_SUBDIRECTORY(3rdparty) 
ENDIF() 
ADD_SUBDIRECTORY(src lib)




