cmake_minimum_required (VERSION 3.0)

project (TOMB5)

macro(OPTIONAL_DEFINE DEFNAME DESCRIPTION VALUE)
	option(${DEFNAME} ${DESCRIPTION} ${VALUE})
	list(APPEND OPT_DEFINITIONS ${DEFNAME})
endmacro()

macro(BuildPreProcessorDefinitions)
	foreach(DEF ${OPT_DEFINITIONS})
		if(${${DEF}} STREQUAL "ON")
			target_compile_definitions(${PROJECT_NAME} PRIVATE ${DEF}=1)
		else()
			target_compile_definitions(${PROJECT_NAME} PRIVATE ${DEF}=0)
		endif()
	endforeach()
endmacro()

#Store the path to our CMAKE module folder in "CMAKE_MODULE_PATH".
#This is used by platform specific CMake scripts to correctly use external libraries.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMAKE")

#include(GetGitRevisionDescription)
#get_git_head_revision(GIT_REFSPEC GIT_SHA1)

#Stores root external lib folder.
set(EXTERN_LIB_PATH ${EXTERN_LIB_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/EXTERNAL")

#Toggles debug code on/off
OPTIONAL_DEFINE(DEBUG_VERSION "Enable/Disable Debug Code" ON)

#Store the path to our game code folder in "GAME_CODE_DIR".
#This is used by platform specific CMake scripts to add this directory as an include directory.
string(CONCAT GAME_CODE_DIR ${CMAKE_CURRENT_SOURCE_DIR} "/GAME")

#Config version file
#configure_file("${GAME_CODE_DIR}/VERSION.C.IN" "${GAME_CODE_DIR}/VERSION.C" @ONLY)

#Find all source files in the game folder.
file(GLOB_RECURSE GAME_SRCS ${GAME_CODE_DIR}/*.C  ${GAME_CODE_DIR}/*.H)

#Extract target architecture (MSVC only)
if (MSVC)
    if (CMAKE_CL_64)
        set(TARGET_ARCH "Win64")
    else()
        set(TARGET_ARCH "Win32")
    endif()
endif()

#We want to be able to group projects in folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#Treat each platform specific directory as a sub-project.
#Note: Travis/Appveyor ci only build PSXPC for now.
if(NOT(DEFINED ENV{TRAVIS} OR DEFINED ENV{APPVEYOR}))
	add_subdirectory(SPEC_PSX)
	add_subdirectory(SPEC_PC)
	add_subdirectory(SPEC_PC_N)
	#add_subdirectory(SPEC_PS2)
	#add_subdirectory(SPEC_CE)
	add_subdirectory(TOOLS)
endif()

#Default
add_subdirectory(SPEC_PSXPC)