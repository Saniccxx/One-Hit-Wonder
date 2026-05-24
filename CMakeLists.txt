cmake_minimum_required(VERSION 4.3)
project(major_jam)

set(CMAKE_CXX_STANDARD 20)

add_executable(major_jam
        main.cpp
        renderer.cpp)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build examples
    endif()
endif()


target_link_libraries(${PROJECT_NAME} raylib)


# Apply static linking only for Windows
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
else()
    # Use dynamic linking on Linux and ensure Wayland support
    set(CMAKE_EXE_LINKER_FLAGS "") # Remove static linking
    set(GLFW_USE_WAYLAND ON)
    set(GLFW_BUILD_X11 OFF) # Disable X11 support hihihiha
endif()