cmake_minimum_required (VERSION 3.0)

project (Emulator_${TARGET_ARCH})

set(OPT_DEFINITIONS "")

#Extract current source folder name.
get_filename_component(PLATFORM_SPECIFIC_FOLDER_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#Enable NTSC mode
OPTIONAL_DEFINE(NTSC_VERSION "Enable/Disable NTSC Mode" ON)

#Find required libs for PSXPC
if(NOT(EMSCRIPTEN))
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
set(GLEW_USE_STATIC_LIBS ON)
find_package(GLEW REQUIRED)
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 --emrun -s ASSERTIONS=1 --std=c++11 -s ALLOW_MEMORY_GROWTH=1 -s GLOBAL_BASE=1048576 -s USE_WEBGL2=1 -s FULL_ES3=1")
set(SDL2_LIBRARIES "-s USE_SDL=2")
endif()

#Setup platform specific / game code include folder
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GAME_CODE_DIR})

#Additional library include directories
if(NOT(EMSCRIPTEN))
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIR})
endif()

#Recursively locate the source files for SPEC_PSX.
file(GLOB_RECURSE EMULATOR_SPECIFIC_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.C  ${CMAKE_CURRENT_SOURCE_DIR}/*.S ${CMAKE_CURRENT_SOURCE_DIR}/*.H ${CMAKE_CURRENT_SOURCE_DIR}/*.CUR ${CMAKE_CURRENT_SOURCE_DIR}/*.RC)

#Group solution source files to correct folders.
source_group("GAME" FILES ${GAME_SRCS})
source_group(${PLATFORM_SPECIFIC_FOLDER_NAME} FILES ${EMULATOR_SPECIFIC_SRCS})

add_library(
${PROJECT_NAME}
STATIC
${EMULATOR_SPECIFIC_SRCS}
)

BuildPreProcessorDefinitions()

target_compile_definitions(${PROJECT_NAME} PRIVATE GLEW_STATIC)

#Someone should actually fix these errors at some point
if(UNIX)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-narrowing -std=c++11")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wno-narrowing -std=c++11")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wno-narrowing -std=c++11")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-narrowing -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-narrowing -std=c++11")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wno-narrowing -std=c++11")
endif()

set_target_properties(
${PROJECT_NAME} PROPERTIES OUTPUT_NAME "PSX"
${PROJECT_NAME} PROPERTIES FOLDER "Libs"
)
