cmake_minimum_required (VERSION 3.0)

project (TombRaiderChronicles_PSX${TARGET_ARCH})

#Extract current source folder name.
get_filename_component(PLATFORM_SPECIFIC_FOLDER_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#Required to build platform specific code properly
OPTIONAL_DEFINE(PSX_VERSION "Enable PSX code building" ON)

#Will make use of CD io if set.
OPTIONAL_DEFINE(DISC_VERSION "Enable/Disable CD code" ON)

#Will build all changes specific to the internal beta version.
OPTIONAL_DEFINE(BETA_VERSION "Enable/Disable Internal Beta code" OFF)

#Enable NTSC mode
OPTIONAL_DEFINE(NTSC_VERSION "Enable/Disable NTSC Mode" ON)

#Enable relocatable code
OPTIONAL_DEFINE(RELOC "Enable/Disable Relocatable code modules" ON)

#Setup platform specific / game code include folder
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GAME_CODE_DIR})

#Additional library include directories
include_directories("c:/psyq/include")
link_directories("c:/psyq/lib")

#Recursively locate the source files for SPEC_PSX.
file(GLOB_RECURSE PLATFORM_SPECIFIC_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.C  ${CMAKE_CURRENT_SOURCE_DIR}/*.H ${CMAKE_CURRENT_SOURCE_DIR}/*.CUR ${CMAKE_CURRENT_SOURCE_DIR}/*.RC)

#Group solution source files to correct folders.
source_group("GAME" FILES ${GAME_SRCS})
source_group(${PLATFORM_SPECIFIC_FOLDER_NAME} FILES ${PLATFORM_SPECIFIC_SRCS})

add_executable(
${PROJECT_NAME}
${GAME_SRCS}
${PLATFORM_SPECIFIC_SRCS}
)

BuildPreProcessorDefinitions()

set_target_properties(
${PROJECT_NAME} PROPERTIES OUTPUT_NAME "MAIN"
${PROJECT_NAME} PROPERTIES FOLDER "Build Targets/PlayStation"
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