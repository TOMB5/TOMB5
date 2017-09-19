cmake_minimum_required (VERSION 3.0)

project (PSXPCTOMB5)

#Extract current source folder name.
get_filename_component(PLATFORM_SPECIFIC_FOLDER_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#Internal Beta
set(INTERNAL 0 CACHE BOOL "Internal")

#Platform specific defs
add_definitions(-DPSXPC_VERSION)

#Find required libs for PSXPC
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

#Create platform specific code directory string
string(CONCAT PLATFORM_SPECIFIC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Setup platform specific / game code include folder
include_directories(${PLATFORM_SPECIFIC_DIR})
include_directories(${GAME_CODE_DIR})

#Additional library include directories
include_directories(${SDL2_INCLUDE_DIR})

#Recursively locate the source files for SPEC_PSXPC.
file(GLOB_RECURSE PLATFORM_SPECIFIC_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.C  ${CMAKE_CURRENT_SOURCE_DIR}/*.H ${PLATFORM_SPECIFIC_DIR}/*.CUR ${PLATFORM_SPECIFIC_DIR}/*.RC)

#Group solution source files to correct folders.
source_group("GAME" FILES ${GAME_SRCS})
source_group(${PLATFORM_SPECIFIC_FOLDER_NAME} FILES ${PLATFORM_SPECIFIC_SRCS})

add_executable(
${PROJECT_NAME}
${GAME_SRCS}
${PLATFORM_SPECIFIC_SRCS}
)

#Link against required libraries
target_link_libraries(
${PROJECT_NAME}
${SDL2_LIBRARY}
${OPENGL_gl_LIBRARY}
)

set_target_properties(
${PROJECT_NAME}
PROPERTIES OUTPUT_NAME "MAIN"
)

#This will be a console application, alter linker subsystem accordingly or main method won't be found
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:CONSOLE")
endif(MSVC)