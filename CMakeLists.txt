cmake_minimum_required (VERSION 2.6)

project (TOMB5)

#User input, used to switch current platform specific code.
set(PLATFORM_PSX 0 CACHE BOOL "Tomb Raider: 5 PlayStation")
set(PLATFORM_PSXPC 1 CACHE BOOL "Tomb Raider: 5 PlayStation (PC)")
set(PLATFORM_PC 0 CACHE BOOL "Tomb Raider: 5 PC")

#Internal Beta
set(INTERNAL 0 CACHE BOOL "Internal")
#MESSAGE(STATUS "PLATFORM_PSXPC: TRUE" ${PLATFORM_PSXPC})

#Tell CMAKE where to find the additional modules this project requires.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMAKE")

#Required libs for PLATFORM_PSXPC
if (PLATFORM_PSXPC)
	find_package(SDL2 REQUIRED)
	find_package(OpenGL)
endif (PLATFORM_PSXPC)

#Create platform specific code directory string
if (PLATFORM_PSX)
	string(CONCAT PLATFORM_SPECIFIC_DIR ${CMAKE_CURRENT_SOURCE_DIR} "/SPEC_PSX")
	add_definitions(-DPSX_VERSION)
endif (PLATFORM_PSX)

if (PLATFORM_PSXPC)
	string(CONCAT PLATFORM_SPECIFIC_DIR ${CMAKE_CURRENT_SOURCE_DIR} "/SPEC_PSXPC")
	add_definitions(-DPSXPC_VERSION)
	#add_library(SETUP SHARED ${PLATFORM_SPECIFIC_DIR}/SETUP.C ${PLATFORM_SPECIFIC_DIR}/GAMEWAD.C ${PLATFORM_SPECIFIC_DIR}/MALLOC.C ${PLATFORM_SPECIFIC_DIR}/LOAD_LEV.C ${PLATFORM_SPECIFIC_DIR}/ROOMLOAD.C ...)
endif (PLATFORM_PSXPC)

if (PLATFORM_PC)
	string(CONCAT PLATFORM_SPECIFIC_DIR ${CMAKE_CURRENT_SOURCE_DIR} "/SPEC_PC")
	add_definitions(-DPC_VERSION)
endif (PLATFORM_PC)

#Internal beta pre-processor definition
if (INTERNAL)
	add_definitions(-DINTERNAL)
endif (INTERNAL)

string(CONCAT GAME_CODE_DIR ${CMAKE_CURRENT_SOURCE_DIR} "/GAME")

#Setup platform specific / game code include folder
include_directories(${PLATFORM_SPECIFIC_DIR})
include_directories(${GAME_CODE_DIR})

#Additional library include directories
include_directories(${SDL2_INCLUDE_DIR})

#Add all GAME/SPEC* source files recursively.
file(GLOB_RECURSE GAME_SRCS ${GAME_CODE_DIR}/*.C  ${GAME_CODE_DIR}/*.H)
file(GLOB_RECURSE PLATFORM_SPECIFIC_SRCS ${PLATFORM_SPECIFIC_DIR}/*.C  ${PLATFORM_SPECIFIC_DIR}/*.H ${PLATFORM_SPECIFIC_DIR}/*.cur ${PLATFORM_SPECIFIC_DIR}/*.RC)
		 
#MESSAGE(STATUS "GAME_SRCS: " ${GAME_SRCS})
#MESSAGE(STATUS "PLATFORM_SPECIFIC_SRCS: " ${PLATFORM_SPECIFIC_SRCS})

add_executable(
TOMB5
${GAME_SRCS}
${PLATFORM_SPECIFIC_SRCS}
)

#Link against required libraries
target_link_libraries(
TOMB5
${SDL2_LIBRARY}
${OPENGL_gl_LIBRARY}
)

set_target_properties(
TOMB5
PROPERTIES OUTPUT_NAME "MAIN"
)

#This will be a console application, alter linker subsystem accordingly or main method won't be found
if(PLATFORM_PSXPC)
   if(MSVC)
      add_definitions(-D_CRT_SECURE_NO_WARNINGS)
      set_target_properties(TOMB5 PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
      set_target_properties(TOMB5 PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
      set_target_properties(TOMB5 PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
      set_target_properties(TOMB5 PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:CONSOLE")
   endif(MSVC)
endif(PLATFORM_PSXPC)

if(PLATFORM_PC)
   if(MSVC)
      add_definitions(-D_CRT_SECURE_NO_WARNINGS)
      set_target_properties(TOMB5 PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
      set_target_properties(TOMB5 PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:WINDOWS")
      set_target_properties(TOMB5 PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
      set_target_properties(TOMB5 PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
      add_definitions(-TC -U__cplusplus)
      #include_directories($\(WindowsSDK_IncludePath\))
      #include_directories($\(DXSDK_DIR\)include)
      #link_directories(\\$\(WindowsSDK_LibraryPath_x86\))
      #link_directories(\\$\(DXSDK_DIR\)lib\\x86)
     # target_link_libraries(
     # TOMB5
     # ddraw.lib
     # dxguid.lib
     # dsound.lib
     # d3dx9.lib
     # dinput.lib
     # )
      #set(CMAKE_CXX_FLAGS "-TC -U __cplusplus")
      #set(CMAKE_C_FLAGS "-TC -U __cplusplus")
      
   endif(MSVC)
endif(PLATFORM_PC)