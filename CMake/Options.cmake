OPTION(BUILD_STATICLIB "Set to ON to build libqingstor with static linking." OFF)
OPTION(BUILD_SHAREDLIB "Set to ON to build libqingstor with shared linking." ON)
OPTION(BUILD_C_STYLE_INTERFACE "Set to ON to build c style interface." OFF)
OPTION (INSTALL_SDK_HEADERS "Request installation of headers." ON)
IF (NOT WIN32)
	# must also specify with CMAKE_BUILD_TYPE=Release 
	OPTION (OPTIMIZE_SPACE "Build with size-optimized options to reduce code size." OFF)
ENDIF()
