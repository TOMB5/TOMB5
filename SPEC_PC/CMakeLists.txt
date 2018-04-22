cmake_minimum_required (VERSION 3.0)

project (TombRaiderChronicles_PC${TARGET_ARCH})

#Extract current source folder name.
get_filename_component(PLATFORM_SPECIFIC_FOLDER_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#Required to build platform specific code properly
OPTIONAL_DEFINE(PC_VERSION "Enable PC code building" ON)

#Setup platform specific / game code include folder
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GAME_CODE_DIR})

#Recursively locate the source files for SPEC_PC.
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

#Link against required libraries
#target_link_libraries(
#${PROJECT_NAME}
#)

set_target_properties(
${PROJECT_NAME} PROPERTIES OUTPUT_NAME "PCTOMB5"
${PROJECT_NAME} PROPERTIES FOLDER "Build Targets/Windows"
)

set(TARGET_BINARY_DIR "${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}")

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	set_target_properties(
	${PROJECT_NAME}
	PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS"
	PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:WINDOWS"
	PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS"
	PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS"
	PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${TARGET_BINARY_DIR}
	)
	add_definitions(-TC -U__cplusplus)
	#include_directories($\(WindowsSDK_IncludePath\))
	#include_directories($\(DXSDK_DIR\)include)
	#link_directories(\\$\(WindowsSDK_LibraryPath_x86\))
	#link_directories(\\$\(DXSDK_DIR\)lib\\x86)
	# target_link_libraries(
	# ${PROJECT_NAME}
	# ddraw.lib
	# dxguid.lib
	# dsound.lib
	# d3dx9.lib
	# dinput.lib
	# )
	#set(CMAKE_CXX_FLAGS "-TC -U __cplusplus")
	#set(CMAKE_C_FLAGS "-TC -U __cplusplus")
endif(MSVC)