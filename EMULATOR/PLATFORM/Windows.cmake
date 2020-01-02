if(MSVC)

Message("Compiling for Windows!")

#
list(APPEND CMAKE_PREFIX_PATH ${EXTERN_LIB_PATH}/glew-2.1.0)
list(APPEND CMAKE_LIBRARY_PATH ${EXTERN_LIB_PATH}/glew-2.1.0/lib/Release/Win32)

#Find libs
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
#We want to link GLEW statically
set(GLEW_USE_STATIC_LIBS ON)
find_package(GLEW REQUIRED)

#Setup project include directories
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIR})

endif()