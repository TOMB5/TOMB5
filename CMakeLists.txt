cmake_minimum_required (VERSION 2.6)

project (TOMB5)

#Platform override
set(PLATFORM_PSX 0 CACHE BOOL "Tomb Raider: 5 PlayStation")
set(PLATFORM_PSXPC 1 CACHE BOOL "Tomb Raider: 5 PlayStation (PC)")
set(PLATFORM_PC 0 CACHE BOOL "Tomb Raider: 5 PC")

#MESSAGE(STATUS "PLATFORM_PSXPC: TRUE" ${PLATFORM_PSXPC})

#Platform specific
if (PLATFORM_PSX)
	string(CONCAT PLATFORM_SPECIFIC_DIR ${CMAKE_CURRENT_SOURCE_DIR} "/SPEC_PSX")
	add_definitions(-DPSX)
endif (PLATFORM_PSX)

if (PLATFORM_PSXPC)
	string(CONCAT PLATFORM_SPECIFIC_DIR ${CMAKE_CURRENT_SOURCE_DIR} "/SPEC_PSXPC")
	add_definitions(-DPSXPC)
endif (PLATFORM_PSXPC)

if (PLATFORM_PC)
	string(CONCAT PLATFORM_SPECIFIC_DIR ${CMAKE_CURRENT_SOURCE_DIR} "/SPEC_PC")
	add_definitions(-DPC)
endif (PLATFORM_PC)

string(CONCAT GAME_CODE_DIR ${CMAKE_CURRENT_SOURCE_DIR} "/GAME")

#Setup platform specific / game code include folder
include_directories(${PLATFORM_SPECIFIC_DIR})
include_directories(${GAME_CODE_DIR})

#Add all GAME/SPEC* source files recursively.
file(GLOB_RECURSE GAME_SRCS ${GAME_CODE_DIR}/*.C  ${GAME_CODE_DIR}/*.H)
file(GLOB_RECURSE PLATFORM_SPECIFIC_SRCS ${PLATFORM_SPECIFIC_DIR}/*.C  ${PLATFORM_SPECIFIC_DIR}/*.H)
		 
#MESSAGE(STATUS "GAME_SRCS: " ${GAME_SRCS})
#MESSAGE(STATUS "PLATFORM_SPECIFIC_SRCS: " ${PLATFORM_SPECIFIC_SRCS})

add_executable(
TOMB5
${GAME_SRCS}
${PLATFORM_SPECIFIC_SRCS}
)

set_target_properties(
TOMB5
PROPERTIES OUTPUT_NAME "MAIN"
)

#This will be a console application, alter linker subsystem accordingly or main method won't be found
if(MSVC)
   add_definitions(-D_CRT_SECURE_NO_WARNINGS)
   set_target_properties(TOMB5 PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
   set_target_properties(TOMB5 PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
   set_target_properties(TOMB5 PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
   set_target_properties(TOMB5 PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:CONSOLE")
endif(MSVC)