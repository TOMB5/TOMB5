if(ANDROID)

Message("Compiling for Android!")

include_directories(${ROOT_DIR}/EXTERNAL/SDL/include)

set(SDL2MAIN_LIBRARY SDL2main)
set(SDL2_LIBRARY SDL2)
set(GLES3_LIBRARY GLESv3)
set(EGL_LIBRARY EGL)

target_link_libraries(${PROJECT_NAME}
  ${SDL2MAIN_LIBRARY}
  ${SDL2_LIBRARY}
  ${GLES3_LIBRARY}
  ${EGL_LIBRARY}
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-error=format-security -Wno-narrowing -Wno-nonportable-include-path")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wno-error=format-security -Wno-narrowing -Wno-nonportable-include-path")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wno-error=format-security -Wno-narrowing -Wno-nonportable-include-path")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=format-security -Wno-narrowing -Wno-nonportable-include-path")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-error=format-security -Wno-narrowing -Wno-nonportable-include-path")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wno-error=format-security -Wno-narrowing -Wno-nonportable-include-path")

endif()