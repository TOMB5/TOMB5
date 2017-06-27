cmake_minimum_required (VERSION 2.6)
project (TOMB5)

#set(CMAKE_CXX_STARNDARD 11)

MESSAGE(STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})

#Platform override
set(PLATFORM_PSX 0 CACHE BOOL "Tomb Raider: 5 PlayStation")
set(PLATFORM_PSXPC 0 CACHE BOOL "Tomb Raider: 5 PlayStation (PC)")
set(PLATFORM_PC 0 CACHE BOOL "Tomb Raider: 5 PC")

file(GLOB_RECURSE TOMB5_SRCS "GAME/*.h" "GAME/*.c" "SPEC_PSX/*.h" "SPEC_PSX/*.c")

#Exe
add_executable(
TOMB5
WIN32
${TOMB5_SRCS}
)

#Platform specific
if (PLATFORM_PSX)
set_target_properties(
TOMB5
PROPERTIES OUTPUT_NAME "MAIN.EXE"
)
add_definitions(-DPSX)
#Recursively add all source files (.h, .cpp)
#file(GLOB_RECURSE TOMB5_SRCS "GAME/*.h" "GAME/*.c" "SPEC_PSX/*.h" "SPEC_PSX/*.c")
endif (PLATFORM_PSX)

if (PLATFORM_PSXPC)
set_target_properties(
TOMB5
PROPERTIES OUTPUT_NAME "MAIN.EXE"
)
add_definitions(-DPSXPC)

#Recursively add all source files (.h, .cpp)
#file(GLOB_RECURSE TOMB5_SRCS "GAME/*.h" "GAME/*.c" "SPEC_PSXPC/*.h" "SPEC_PSXPC/*.c")

endif (PLATFORM_PSXPC)

if (PLATFORM_PC)
set_target_properties(
TOMB5
PROPERTIES OUTPUT_NAME "MAIN.EXE"
)
add_definitions(-DPC)

#Recursively add all source files (.h, .cpp)
#file(GLOB_RECURSE TOMB5_SRCS "GAME/*.h" "GAME/*.c" "SPEC_PC/*.h" "SPEC_PC/*.c")
endif (PLATFORM_PC)


#This will be a console application, alter linker subsystem accordingly or main method won't be found
if(WIN32)
   set_target_properties(TOMB5 PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
   set_target_properties(TOMB5 PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
   set_target_properties(TOMB5 PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
   set_target_properties(TOMB5 PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")
   set_target_properties(TOMB5 PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
   set_target_properties(TOMB5 PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:CONSOLE")
endif(WIN32)

MESSAGE(STATUS "TARGET_FILE_NAME: " ${TARGET_FILE_NAME})

