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
        cpps/map_display.cpp
        headers/map_display.h
        cpps/map_player.cpp
        headers/map_player.h
        cpps/interaction_object.cpp
        headers/interaction_object.h
        headers/settings_display.h
        cpps/settings_display.cpp
        headers/collision_object.h
        cpps/collision_object.cpp
        cpps/settings_display.cpp
        headers/pause_display.h
        cpps/pause_display.cpp
        headers/dialog.h
        cpps/dialog.cpp
        headers/particles/particle.h
        cpps/particles/particle.cpp
        headers/particles/particle_generator.h
        cpps/particles/particle_generator.cpp
        headers/particles/particle_system.h
        cpps/particles/particle_system.cpp
        cpps/config.cpp
        cpps/map_display_save_load.cpp)

# Dependencies
set(RAYLIB_VERSION 6.0)

# Enable raylib web backend when using Emscripten
if (EMSCRIPTEN)
    set(PLATFORM Web CACHE STRING "" FORCE)
    # Web builds typically use an HTML launcher
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)
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


target_link_libraries(${PROJECT_NAME} raylib nlohmann_json::nlohmann_json)
# Copy assets for native builds
if (NOT EMSCRIPTEN)
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/Resources
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources
    )
endif()

# Web build flags and asset preloading
if (EMSCRIPTEN)
    target_link_options(${PROJECT_NAME} PRIVATE
            "-sUSE_GLFW=3"
            "-sALLOW_MEMORY_GROWTH=1"
            "-sASSERTIONS=1"
            "-sEXIT_RUNTIME=0"
            "-sASYNCIFY=1"
            "--preload-file" "${CMAKE_CURRENT_SOURCE_DIR}/Resources@/Resources"
    )
elseif(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
else()
    # Use dynamic linking on Linux and ensure Wayland support
    set(CMAKE_EXE_LINKER_FLAGS "") # Remove static linking
    set(GLFW_USE_WAYLAND ON)
    set(GLFW_BUILD_X11 OFF) # Disable X11 support hihihiha
endif()