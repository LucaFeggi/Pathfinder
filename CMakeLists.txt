cmake_minimum_required(VERSION 3.23)

project(Pathfinder VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

set(SDL_SHARED OFF CACHE BOOL "Build SDL2 as a shared library" FORCE)
set(SDL_STATIC ON CACHE BOOL "Build SDL2 as a static library" FORCE)
set(SDL_TEST OFF CACHE BOOL "Build the SDL2 test library" FORCE)
set(SDL_TESTS OFF CACHE BOOL "Build SDL2 tests" FORCE)

add_subdirectory(externals/SDL2 EXCLUDE_FROM_ALL)

add_executable(Pathfinder
    src/main.cpp
    src/app/app.cpp
    src/app/input.cpp
    src/app/window.cpp
    src/renderer/renderer.cpp
    src/simulation/a_star.cpp
)

target_compile_features(Pathfinder PRIVATE cxx_std_20)

if(WIN32)
    target_compile_definitions(Pathfinder PRIVATE main=SDL_main)
endif()

target_link_libraries(Pathfinder PRIVATE
    SDL2::SDL2main
    SDL2::SDL2-static
)

add_custom_command(TARGET Pathfinder POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:Pathfinder>/assets"
)
