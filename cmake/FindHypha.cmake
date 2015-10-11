# - finds the Hypha C++ libraries
# This module finds the Hypha libraries.
# It supports the following components:
#
# utils (loaded by default)
# Foundation 

#
# Usage:
#	set(ENV{Hypha_DIR} path/to/hypha/sdk)
#	find_package(Hypha REQUIRED OSP Data Crypto) 
#
# On completion, the script defines the following variables:
#	
#	- Compound variables:
#   Hypha_FOUND 
#		- true if all requested components were found.
#	Hypha_LIBRARIES 
#		- contains release (and debug if available) libraries for all requested components.
#		  It has the form "optimized LIB1 debug LIBd1 optimized LIB2 ...", ready for use with the target_link_libraries command.
#	Hypha_INCLUDE_DIRS
#		- Contains include directories for all requested components.
#
#	- Component variables:
#   Hypha_Xxx_FOUND 
#		- Where Xxx is the properly cased component name (eg. 'Util', 'OSP'). 
#		  True if a component's library or debug library was found successfully.
#	Hypha_Xxx_LIBRARY 
#		- Library for component Xxx.
#	Hypha_Xxx_LIBRARY_DEBUG 
#		- debug library for component Xxx
#   Hypha_Xxx_INCLUDE_DIR
#		- include directory for component Xxx
#
#  	- OSP BundleCreator variables: (i.e. bundle.exe on windows, bundle on unix-likes)
#		(is only discovered if OSP is a requested component)
#	Hypha_OSP_Bundle_EXECUTABLE_FOUND 
#		- true if the bundle-creator executable was found.
#	Hypha_OSP_Bundle_EXECUTABLE
#		- the path to the bundle-creator executable.
#
# Author: Andreas Stahl andreas.stahl@tu-dresden.de, Christian Müller

set(Hypha_HINTS
	../hypha/build
	/usr/local
	C:/Dev
	${Hypha_DIR} 
	$ENV{Hypha_DIR}
)

if(NOT Hypha_ROOT_DIR)
	# look for the root directory, first for the source-tree variant
	find_path(Hypha_ROOT_DIR 
		NAMES utils/include/hypha/utils.h
		HINTS ${Hypha_HINTS}
	)
	if(NOT Hypha_ROOT_DIR)
		# this means hypha may have a different directory structure, maybe it was installed, let's check for that
		message(STATUS "Looking for Hypha install directory structure.")
		find_path(Hypha_ROOT_DIR 
			NAMES include/hypha/hypha.h
			HINTS ${Hypha_HINTS}
		)
		if(NOT Hypha_ROOT_DIR) 
			# hypha was still not found -> Fail
			if(Hypha_FIND_REQUIRED)
				message(FATAL_ERROR "Hypha: Could not find Hypha install directory")
			endif()
			if(NOT Hypha_FIND_QUIETLY)
				message(STATUS "Hypha: Could not find Hypha install directory")
			endif()
			return()
		else()
			# Hypha was found with the make install directory structure
			message(STATUS "Assuming Hypha install directory structure at ${Hypha_ROOT_DIR}.")
			set(Hypha_INSTALLED true)
		endif()
	endif()
endif()

# add dynamic library directory
if(WIN32)
	find_path(Hypha_RUNTIME_LIBRARY_DIRS
		NAMES HyphaUtils.dll
		HINTS ${Hypha_ROOT_DIR}
		PATH_SUFFIXES 
			bin
			lib
	)
endif()

# if installed directory structure, set full include dir
if(Hypha_INSTALLED)
	set(Hypha_INCLUDE_DIRS ${Hypha_ROOT_DIR}/include/ CACHE PATH "The global include path for Hypha")
endif()

# append the default minimum components to the list to find
list(APPEND components 
	${Hypha_FIND_COMPONENTS} 
	# default components:
	"Utils"
)
list(REMOVE_DUPLICATES components) # remove duplicate defaults

foreach( component ${components} )
	string( TOLOWER "${component}" component_lower )
	#if(NOT Hypha_${component}_FOUND)
		
	# include directory for the component
	if(NOT Hypha_${component}_INCLUDE_DIR)

		find_path(Hypha_${component}_INCLUDE_DIR
			NAMES 
				hypha/${component_lower}.h 	# e.g. utils.h
				hypha/${component_lower}/${component_lower}.h # e.g. OSP/OSP.h utils/utils.h
			HINTS
				${Hypha_ROOT_DIR}
			PATH_SUFFIXES
				include
				${component_lower}/include
		)
	endif()
	if(NOT Hypha_${component}_INCLUDE_DIR)
		message(FATAL_ERROR "Hypha_${component}_INCLUDE_DIR NOT FOUND")
	else()
		list(APPEND Hypha_INCLUDE_DIRS ${Hypha_${component}_INCLUDE_DIR})
	endif()

	# release library
	if(NOT Hypha_${component}_LIBRARY)
		find_library(
			Hypha_${component}_LIBRARY 
			NAMES Hypha${component} 
			HINTS ${Hypha_ROOT_DIR}
			PATH_SUFFIXES
				lib
				bin
		)
		if(Hypha_${component}_LIBRARY)
			message(STATUS "Found Hypha ${component}: ${Hypha_${component}_LIBRARY}")
		endif()
	endif()
	if(Hypha_${component}_LIBRARY)
		list(APPEND Hypha_LIBRARIES "optimized" ${Hypha_${component}_LIBRARY} )
		mark_as_advanced(Hypha_${component}_LIBRARY)
	endif()

	# debug library
	if(NOT Hypha_${component}_LIBRARY_DEBUG)
		find_library(
			Hypha_${component}_LIBRARY_DEBUG
			Names Hypha${component}d
			HINTS ${Hypha_ROOT_DIR}
			PATH_SUFFIXES
				lib
				bin
		)
		if(Hypha_${component}_LIBRARY_DEBUG)
			message(STATUS "Found Hypha ${component} (debug): ${Hypha_${component}_LIBRARY_DEBUG}")
		endif()
	endif(NOT Hypha_${component}_LIBRARY_DEBUG)
	if(Hypha_${component}_LIBRARY_DEBUG)
		list(APPEND Hypha_LIBRARIES "debug" ${Hypha_${component}_LIBRARY_DEBUG})
		mark_as_advanced(Hypha_${component}_LIBRARY_DEBUG)
	endif()

	# mark component as found or handle not finding it
	if(Hypha_${component}_LIBRARY_DEBUG OR Hypha_${component}_LIBRARY)
		set(Hypha_${component}_FOUND TRUE)
	elseif(NOT Hypha_FIND_QUIETLY)
		message(FATAL_ERROR "Could not find Hypha component ${component}!")
	endif()
endforeach()

if(DEFINED Hypha_LIBRARIES)
	set(Hypha_FOUND true)
endif()

if(${Hypha_OSP_FOUND})
	# find the osp bundle program
	find_program(
		Hypha_OSP_Bundle_EXECUTABLE 
		NAMES bundle
		HINTS 
			${Hypha_RUNTIME_LIBRARY_DIRS}
			${Hypha_ROOT_DIR}
		PATH_SUFFIXES
			bin
			OSP/BundleCreator/bin/Darwin/x86_64
			OSP/BundleCreator/bin/Darwin/i386
		DOC "The executable that bundles OSP packages according to a .bndlspec specification."
	)
	if(Hypha_OSP_Bundle_EXECUTABLE)
		set(Hypha_OSP_Bundle_EXECUTABLE_FOUND true)
	endif()
	# include bundle script file
	find_file(Hypha_OSP_Bundles_file NAMES HyphaBundles.cmake HINTS ${CMAKE_MODULE_PATH})
	if(${Hypha_OSP_Bundles_file})
		include(${Hypha_OSP_Bundles_file})
	endif()
endif()

message(STATUS "Found Hypha: ${Hypha_LIBRARIES}")


