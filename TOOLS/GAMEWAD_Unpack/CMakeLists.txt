cmake_minimum_required (VERSION 3.0)

project (GAMEWAD_Unpack${TARGET_ARCH})

#Setup platform specific / game code include folder
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${SPEC_PSXPC_DIR})

#Recursively locate the source files for GAMEWAD_Unpack.
file(GLOB_RECURSE TOOL_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.CPP ${CMAKE_CURRENT_SOURCE_DIR}/*.C  ${CMAKE_CURRENT_SOURCE_DIR}/*.H ${CMAKE_CURRENT_SOURCE_DIR}/*.CUR ${CMAKE_CURRENT_SOURCE_DIR}/*.RC)

add_executable(
${PROJECT_NAME}
${TOOL_SRCS}
)

set_target_properties(
${PROJECT_NAME} PROPERTIES OUTPUT_NAME "GAMEWAD_Unpack"
${PROJECT_NAME} PROPERTIES FOLDER "Tools/Gamewad"
)

#This will be a console application, alter linker subsystem accordingly or main method won't be found
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	set_target_properties(
	${PROJECT_NAME}
	PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
	PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE"
	PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE"
	PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:CONSOLE"
	PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(TargetDir)"
	)
endif(MSVC)