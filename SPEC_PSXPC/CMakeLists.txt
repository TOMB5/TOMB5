cmake_minimum_required (VERSION 3.0)

project (TombRaiderChronicles_PSXPC${TARGET_ARCH})

#Extract current source folder name.
get_filename_component(PLATFORM_SPECIFIC_FOLDER_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#Will make use of CD io if set.
set(DISC_VERSION 1 CACHE BOOL "Enable/Disable CD code")

#Will build all changes specific to the internal beta version.
set(BETA_VERSION 0 CACHE BOOL "Enable/Disable Internal Beta code")

#Enable NTSC mode
set(NTSC_VERSION 1 CACHE BOOL "Enable/Disable NTSC Mode")

#Platform specific defs
add_definitions(-DPSXPC_VERSION)

if(BETA_VERSION)
	add_definitions(-DBETA_VERSION)
endif(BETA_VERSION)

if(DISC_VERSION)
	add_definitions(-DDISC_VERSION)
endif(DISC_VERSION)

if(NTSC_VERSION)
	add_definitions(-DNTSC_VERSION)
endif(NTSC_VERSION)

#Find required libs for PSXPC
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

#Setup platform specific / game code include folder
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GAME_CODE_DIR})

#Additional library include directories
include_directories(${SDL2_INCLUDE_DIR})

#Recursively locate the source files for SPEC_PSXPC.
file(GLOB_RECURSE PLATFORM_SPECIFIC_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.C  ${CMAKE_CURRENT_SOURCE_DIR}/*.H ${CMAKE_CURRENT_SOURCE_DIR}/*.CUR ${CMAKE_CURRENT_SOURCE_DIR}/*.RC)

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
${PROJECT_NAME} PROPERTIES OUTPUT_NAME "MAIN"
${PROJECT_NAME} PROPERTIES FOLDER "Build Targets/Windows"
)

set(TARGET_BINARY_DIR "${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}")

#This will be a console application, alter linker subsystem accordingly or main method won't be found
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	set_target_properties(
	${PROJECT_NAME}
	PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
	PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE"
	PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE"
	PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:CONSOLE"
	PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${TARGET_BINARY_DIR}
	)
endif(MSVC)