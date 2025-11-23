cmake_minimum_required(VERSION 3.10)
project(ab_rick)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Paths ----

# raylib-cpp base directory
set(RAYLIB_CPP_DIR "/run/media/rick/8b5b9054-ef1c-4785-aa10-f6a2608b67c8/ArchLinux/work/raylib-cpp")

# Lua 5.1.5
add_subdirectory(externals/lua-5.1.5)

# ---- Include Directories ----


include_directories(externals/rlImGui)
include_directories(externals/imgui)
include_directories(externals/lua-5.1.5)


    # Add sources
set(IMGUI_SOURCES
    ./externals/imgui/imgui.cpp
    ./externals/imgui/imgui_draw.cpp
    ./externals/imgui/imgui_tables.cpp
    ./externals/imgui/imgui_widgets.cpp
    ./externals/rlImGui/rlImGui.cpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/script

    # raylib-cpp and raylib headers
    ${RAYLIB_CPP_DIR}/include
    ${RAYLIB_CPP_DIR}/build/_deps/raylib-src/src

    # Lua 5.1.5 headers
    ${CMAKE_SOURCE_DIR}/externals/lua-5.1.5/src

    # Bullet Physics
    /usr/local/include/bullet
    /usr/local/include
)

# ---- Link Directories ----
#link_directories(
 #   /usr/lib
  #  /usr/local/lib
#)

# ---- Executable ----
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/physics.cpp
    src/ETC/global_var.cpp
    src/Controls/camera.cpp
    src/3dObjects/objects.cpp
    src/3dObjects/elements.cpp
    src/script/script.cpp
    src/NPC/person.cpp
    src/3dObjects/model_obj.cpp
    src/3dObjects/Models.cpp
    externals/rlImGui/rlImGui.h
    externals/imgui/imgui.h
    src/player.cpp
    src/related/file.cpp
    src/menu/menu.cpp
    src/level/player/player.cpp
    ${IMGUI_SOURCES}
    )

# ---- Linking ----
target_link_libraries(${PROJECT_NAME}
    # Your static raylib build
    ${RAYLIB_CPP_DIR}/build/_deps/raylib-build/raylib/libraylib.a

    # Lua 5.1.5 static lib
    lua_static

    # Bullet Physics
    BulletDynamics
    BulletCollision
    LinearMath

    # System libraries
    pthread m dl rt GL X11

    # Optional stdlib
    stdc++
)


# Copy assets to build directory
add_custom_command(
    TARGET ab_rick POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/assets
            ${CMAKE_CURRENT_BINARY_DIR}/assets
)

# Copy scripts to build directory
add_custom_command(
    TARGET ab_rick POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/script
            ${CMAKE_CURRENT_BINARY_DIR}/script
)

