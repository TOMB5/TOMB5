cmake_minimum_required (VERSION 3.0)

project (TOMB5)

#Store the path to our CMAKE module folder in "CMAKE_MODULE_PATH".
#This is used by platform specific CMake scripts to correctly use external libraries.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMAKE")

#Toggles debug code on/off
set(DEBUG_VERSION 0 CACHE BOOL "Debug Version")

#Store the path to our game code folder in "GAME_CODE_DIR".
#This is used by platform specific CMake scripts to add this directory as an include directory.
string(CONCAT GAME_CODE_DIR ${CMAKE_CURRENT_SOURCE_DIR} "/GAME")

#Find all source files in the game folder.
file(GLOB_RECURSE GAME_SRCS ${GAME_CODE_DIR}/*.C  ${GAME_CODE_DIR}/*.H)

#Treat each platform specific directory as a sub-project.
add_subdirectory(SPEC_PC)
add_subdirectory(SPEC_PSX)
add_subdirectory(SPEC_PSXPC)