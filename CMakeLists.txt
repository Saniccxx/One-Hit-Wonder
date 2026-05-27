cmake_minimum_required(VERSION 4.2.2)
project(major_jam)

set(CMAKE_CXX_STANDARD 20)

add_executable(major_jam
        cpps/main.cpp
        cpps/renderer.cpp
        headers/renderer.h
        headers/game.h
        cpps/game.cpp
        headers/combat_display.h
        cpps/combat_display.cpp
        headers/start_display.h
        cpps/start_display.cpp
        headers/display.h
        headers/combat_player.h
        cpps/combat_player.cpp
        headers/camera.h
        cpps/camera.cpp
        cpps/combat_display.cpp
        cpps/assets.cpp
        headers/assets.h
        headers/combat_obstacle.h
        cpps/combat_obstacle.cpp
        headers/assets.h
        cpps/Button.cpp
        headers/Button.h
        headers/config.h
        headers/sequence.h
        cpps/sequence.cpp
        cpps/jeff_the_display.cpp
        headers/jeff_the_display.h
        cpps/map_player.cpp
        headers/map_player.h
        cpps/map_object.cpp
        headers/map_object.h)

# Dependencies
set(RAYLIB_VERSION 6.0)
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

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Resources
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources
)

# Apply static linking only for Windows
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
else()
    # Use dynamic linking on Linux and ensure Wayland support
    set(CMAKE_EXE_LINKER_FLAGS "") # Remove static linking
    set(GLFW_USE_WAYLAND ON)
    set(GLFW_BUILD_X11 OFF) # Disable X11 support hihihiha
endif()