# Find DirectX9

#message("Looking for DirectX9...")

file(GLOB DX9_SEARCH_PATHS
	"$ENV{DXSDK_DIR}/Include"
	"$ENV{PROGRAMFILES}/Microsoft DirectX SDK*/Include"
	"$ENV{PROGRAMFILES}/Microsoft SDKs/Windows/*/Include"
	"C:/Program Files (x86)/Windows Kits/*/include/um"
	"C:/Program Files/Windows Kits/*/include/um"
	"C:/Program Files (x86)/Windows Kits/10/Include/10.0.*.0/um"
	"C:/Program Files/Windows Kits/10/Include/10.0.*.0/um"
)
find_path(DIRECTX_INCLUDE_DIRS
          NAMES d3d9.h
          PATHS ${DX9_SEARCH_PATHS})

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET(DX9_LIBRARY_PATHS
        "$ENV{DXSDK_DIR}/Lib/x64/"
        "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64/"
        "C:/Program Files (x86)/Windows Kits/8.0/Lib/win8/um/x64/"
        "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.14393.0/um/x64/"
        "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10586.0/um/x64/"
		"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.15063.0/um/x64/"
		"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.16299.0/um/x64/"
    )
else()
    SET(DX9_LIBRARY_PATHS
        "$ENV{DXSDK_DIR}/Lib/x86/"
        "C:/Program Files (x86)/Windows Kits/8.1/lib/winv6.3/um/x86/"
        "C:/Program Files (x86)/Windows Kits/8.0/lib/win8/um/x86/"
        "C:/Program Files (x86)/Windows Kits/10/lib/10.0.14393.0/um/x86/"
        "C:/Program Files (x86)/Windows Kits/10/lib/10.0.10586.0/um/x86/"
		"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.15063.0/um/x86/"
		"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.16299.0/um/x86/"
    )
endif()

find_library(DX9_LIB d3dx9 ${DX9_LIBRARY_PATHS} NO_DEFAULT_PATH)
find_library(DX3D9_LIB d3d9 ${DX9_LIBRARY_PATHS} NO_DEFAULT_PATH)
set(DIRECTX_LIBRARIES ${DX9_LIB})

#message("Include: ${DIRECTX_INCLUDE_DIRS}")
#message("Libs: ${DIRECTX_LIBRARIES}")

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(DIRECTX9
    DEFAULT_MSG DIRECTX_ROOT_DIR
    DIRECTX_LIBRARIES DIRECTX_INCLUDE_DIRS
)
mark_as_advanced(DIRECTX_INCLUDE_DIRS DX9_LIB)
