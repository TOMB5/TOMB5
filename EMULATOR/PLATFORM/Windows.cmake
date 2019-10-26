if(MSVC)

Message("Compiling for Windows!")

#Find libs
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

#We want to link GLEW statically
set(GLEW_USE_STATIC_LIBS ON)

#Setup project include directories
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIR})

endif()