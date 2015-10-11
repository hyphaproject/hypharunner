cmake_minimum_required(VERSION 2.8.11)

project(hypharunner)

	add_subdirectory( alarm )
    add_subdirectory( dooropener )
	add_subdirectory( serverstatus )
    add_subdirectory( videocontrol )
IF(WIN32)
elseif(UNIX)
    add_subdirectory( blechuhr )

else()
ENDIF()

