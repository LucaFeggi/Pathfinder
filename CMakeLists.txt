cmake_minimum_required(VERSION 3.10)
project(Pathfinder VERSION 1.0 LANGUAGES CXX)

# --- C++ Standard ---
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Source files ---
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/renderer/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/simulation/*.cpp"
    "${PROJECT_SOURCE_DIR}/app/*.cpp"
)

# --- Internal include directories ---
set(INTERNAL_INCLUDES
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/src/renderer"
    "${PROJECT_SOURCE_DIR}/src/simulation"
    "${PROJECT_SOURCE_DIR}/app"
)

# --- SDL2 Setup ---
if(WIN32)
    # Windows: use bundled SDL2
    set(EXTERNAL_INCLUDES "${PROJECT_SOURCE_DIR}/externals/SDL2-2.32.10/include")
    set(SDL2_LIB_AND_DLL_DIR "${PROJECT_SOURCE_DIR}/externals/SDL2-2.32.10/lib/x64")
    
    set(SDL_LIBRARIES SDL2 SDL2main)

elseif(UNIX)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 sdl2)

    if(NOT SDL2_FOUND)
        message(STATUS "SDL2 not found. Attempting to install...")

        if(UNIX AND NOT APPLE)
            # Linux (Debian/Ubuntu)
            execute_process(COMMAND sudo apt-get update)
            execute_process(COMMAND sudo apt-get install -y libsdl2-dev)
        elseif(APPLE)
            # macOS
            execute_process(COMMAND brew install sdl2)
        endif()

        # Retry finding SDL2
        pkg_check_modules(SDL2 sdl2 REQUIRED)
    endif()

    set(SDL_LIBRARIES ${SDL2_LIBRARIES})
endif()

# --- Create executable ---
add_executable(${PROJECT_NAME} ${SOURCE_FILES} "${PROJECT_SOURCE_DIR}/src/main.cpp")

# --- Include directories per target ---
target_include_directories(${PROJECT_NAME} PRIVATE ${INTERNAL_INCLUDES})

if(WIN32)
    target_include_directories(${PROJECT_NAME} PRIVATE ${EXTERNAL_INCLUDES})
    link_directories(${SDL2_LIB_AND_DLL_DIR})
elseif(UNIX)
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
    link_directories(${SDL2_LIBRARY_DIRS})
endif()

# --- Link libraries ---
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL_LIBRARIES})

# --- Output directories ---
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)

# --- Visual Studio specific ---
if(WIN32)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    set(CMAKE_SUPPRESS_REGENERATION true)

    # Copy SDL2.dll next to executable
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_LIB_AND_DLL_DIR}/SDL2.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMENT "Copying SDL2.dll to build directory"
    )
endif()

# --- Copy assets (all platforms) ---
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMENT "Copying assets folder"
)

# --- Install (optional) ---
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT Runtime
)
