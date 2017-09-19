cmake_minimum_required (VERSION 3.0)

project (PCTOMB5)

#Extract current source folder name.
get_filename_component(PLATFORM_SPECIFIC_FOLDER_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#Platform specific defs
add_definitions(-DPC_VERSION)

#Create platform specific code directory string
string(CONCAT PLATFORM_SPECIFIC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Setup platform specific / game code include folder
include_directories(${PLATFORM_SPECIFIC_DIR})
include_directories(${GAME_CODE_DIR})

#Additional library include directories
include_directories(${SDL2_INCLUDE_DIR})

#Recursively locate the source files for SPEC_PC.
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
#target_link_libraries(
#${PROJECT_NAME}
#)

set_target_properties(
${PROJECT_NAME}
PROPERTIES OUTPUT_NAME "PCTOMB5"
)

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:WINDOWS")
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
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