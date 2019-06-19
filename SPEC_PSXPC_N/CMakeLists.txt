cmake_minimum_required (VERSION 3.0)

project (TombRaiderChronicles_PSXPC_N${TARGET_ARCH})

set(OPT_DEFINITIONS "")

#Extract current source folder name.
get_filename_component(PLATFORM_SPECIFIC_FOLDER_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#Find required libs for PSXPC_N
set(GLEW_USE_STATIC_LIBS ON)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

#Toggles debug code on/off
OPTIONAL_DEFINE(DEBUG_VERSION "Enable/Disable Debug Code" OFF)

#Required to build platform specific code properly
OPTIONAL_DEFINE(PSX_VERSION "Enable PSX code building" ON)

#Will make use of CD io if set.
OPTIONAL_DEFINE(DISC_VERSION "Enable/Disable CD code" OFF)

#Will build all changes specific to the internal beta version.
OPTIONAL_DEFINE(BETA_VERSION "Enable/Disable Internal Beta code" OFF)

#Enable NTSC mode
OPTIONAL_DEFINE(NTSC_VERSION "Enable/Disable NTSC Mode" ON)

#Enable PSXPC test code
OPTIONAL_DEFINE(PSXPC_TEST "Enable/Disable PSXPC Test Code" ON)

#Enable relocatable code
OPTIONAL_DEFINE(RELOC "Enable/Disable Relocatable code modules" OFF)

#Setup platform specific / game code include folder
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GAME_CODE_DIR})

#Additional library include directories
include_directories(${ROOT_DIR}/EMULATOR)
link_directories(${ROOT_DIR}/BUILD/EMULATOR/${CMAKE_BUILD_TYPE})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIR})

#Recursively locate the source files for SPEC_PSX.
file(GLOB_RECURSE PLATFORM_SPECIFIC_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.C  ${CMAKE_CURRENT_SOURCE_DIR}/*.MIP ${CMAKE_CURRENT_SOURCE_DIR}/*.H ${CMAKE_CURRENT_SOURCE_DIR}/*.CUR ${CMAKE_CURRENT_SOURCE_DIR}/*.RC)

#Group solution source files to correct folders.
source_group("GAME" FILES ${GAME_SRCS})
source_group(${PLATFORM_SPECIFIC_FOLDER_NAME} FILES ${PLATFORM_SPECIFIC_SRCS})

add_executable(
${PROJECT_NAME}
${GAME_SRCS}
${PLATFORM_SPECIFIC_SRCS}
)

BuildPreProcessorDefinitions()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU OR UNIX)
add_dependencies(${PROJECT_NAME} Emulator_)
set(PSX_LIB libPSX.a)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
add_dependencies(${PROJECT_NAME} Emulator_Win32)
set(PSX_LIB PSX.lib)
endif()

#Link against required libraries
target_link_libraries(
${PROJECT_NAME}
${PSX_LIB}
${SDL2_LIBRARY}
${OPENGL_gl_LIBRARY}
${GLEW_LIBRARY}
)

set_target_properties(
${PROJECT_NAME} PROPERTIES OUTPUT_NAME "MAIN"
${PROJECT_NAME} PROPERTIES FOLDER "Build Targets/PlayStation"
)

#Someone should actually fix these errors at some point
if(UNIX)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-narrowing")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wno-narrowing")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wno-narrowing")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-narrowing")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-narrowing")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wno-narrowing")
endif()

set(TARGET_BINARY_DIR "${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}")

#This will be a console application, alter linker subsystem accordingly or main method won't be found
if(MSVC)
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /BASE:0x400000 /DYNAMICBASE:NO /FIXED")
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