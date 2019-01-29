#
# Find GLEW
#
# Try to find GLEW : The OpenGL Extension Wrangler Library.
# This module defines the following variables:
# - GLEW_INCLUDE_DIRS
# - GLEW_LIBRARIES
# - GLEW_DEFINITIONS
# - GLEW_FOUND
#
# The following variables can be set as arguments for the module.
# - GLEW_ROOT_DIR : Root library directory of GLEW
# - GLEW_USE_STATIC_LIBS : Specifies to use static version of GLEW library (Windows only)
#
# References:
# - https://github.com/progschj/OpenGL-Examples/blob/master/cmake_modules/FindGLEW.cmake
# - https://code.google.com/p/nvidia-texture-tools/source/browse/trunk/cmake/FindGLEW.cmake
# - Mitsuba Renderer
#

# Additional modules
include(FindPackageHandleStandardArgs)

# Dependencies
# GLEW depends on OpenGL
find_package(OpenGL)

if (WIN32)
	# Find include files
	find_path(
		GLEW_INCLUDE_DIR
		NAMES GL/glew.h
		PATHS
		$ENV{PROGRAMFILES}/include
		${GLEW_ROOT_DIR}/include
		DOC "The directory where GL/glew.h resides")

	# Use glew32s.lib for static library
	# Define additional compiler definitions
	if (GLEW_USE_STATIC_LIBS)
		set(GLEW_LIBRARY_NAME glew32s)
		set(GLEW_DEFINITIONS -DGLEW_STATIC)
	else()
		set(GLEW_LIBRARY_NAME glew32)
	endif()

	# Find library files
	find_library(
		GLEW_LIBRARY
		NAMES ${GLEW_LIBRARY_NAME}
		PATHS
		$ENV{PROGRAMFILES}/GLEW/lib
		${GLEW_ROOT_DIR}/lib
		DOC "The GLEW library")

	unset(GLEW_LIBRARY_NAME)
else()
	# Find include files
	find_path(
		GLEW_INCLUDE_DIR
		NAMES GL/glew.h
		PATHS
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		${GLEW_ROOT_DIR}/include
		DOC "The directory where GL/glew.h resides")

	# Find library files
	# Try to use static libraries
	find_library(
		GLEW_LIBRARY
		NAMES libGLEW.a GLEW
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		${GLEW_ROOT_DIR}/lib
		DOC "The GLEW library")
endif()

# Handle REQUIRD argument, define *_FOUND variable
find_package_handle_standard_args(GLEW DEFAULT_MSG GLEW_INCLUDE_DIR GLEW_LIBRARY)

# Define GLEW_LIBRARIES and GLEW_INCLUDE_DIRS
if (GLEW_FOUND)
	set(GLEW_LIBRARIES ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})
	set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
endif()

# Hide some variables
mark_as_advanced(GLEW_INCLUDE_DIR GLEW_LIBRARY)