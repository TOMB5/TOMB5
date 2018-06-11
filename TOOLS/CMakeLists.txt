cmake_minimum_required (VERSION 3.0)

#Store the path to our tools folder folder in "TOOL_ROOT_DIR".
set(TOOL_ROOT_DIR ${TOOL_ROOT_DIR} "${CMAKE_CURRENT_SOURCE_DIR}")

get_filename_component(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

set(SPEC_PSX_DIR ${ROOT_DIR}/SPEC_PSX "${SPEC_PSX_DIR}")
set(SPEC_PSXPC_DIR ${ROOT_DIR}/SPEC_PSXPC "${SPEC_PSXPC_DIR}")
set(SPEC_PC_DIR ${ROOT_DIR}/SPEC_PC "${SPEC_PC_DIR}")

#Add each tool project
if(NOT(DEFINED ENV{TRAVIS} OR DEFINED ENV{APPVEYOR}))
	add_subdirectory(GAMEWAD_Unpack)
	add_subdirectory(GAMEWAD_Pack)
endif()