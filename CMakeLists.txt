# --- Top-Level CMakeLists.txt ---

cmake_minimum_required(VERSION 3.10)

# --- Project definition ---
project(Pathfinder VERSION 1.0 LANGUAGES CXX)

# --- C++ Standard ---
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Source and include directories ---
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(EXTERNAL_INCLUDES "${PROJECT_SOURCE_DIR}/externals/SDL2-2.32.10/include")
set(INTERNAL_INCLUDES
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/src/renderer"
    "${PROJECT_SOURCE_DIR}/src/simulation"
    "${PROJECT_SOURCE_DIR}/app"
)

set(SDL2_LIB_AND_DLL_DIR "${PROJECT_SOURCE_DIR}/externals/SDL2-2.32.10/lib/x64")

file(GLOB_RECURSE SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/renderer/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/simulation/*.cpp"
    "${PROJECT_SOURCE_DIR}/app/*.cpp"
)

# --- Configuration ---
include_directories(
    ${EXTERNAL_INCLUDES}
    ${INTERNAL_INCLUDES}
)

link_directories(${SDL2_LIB_AND_DLL_DIR})

set(SDL_LIBRARIES
    SDL2
    SDL2main
)

# --- Build the Executable ---
add_executable(${PROJECT_NAME}
    ${SOURCE_FILES}
    "${PROJECT_SOURCE_DIR}/src/main.cpp"
)

target_link_libraries(${PROJECT_NAME}
    ${SDL_LIBRARIES}
)

# --- Output Directories ---
# Place binaries under /build/Debug or /build/Release
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)

# Set Visual Studio debugger working directory to the runtime output
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)

# --- Visual Studio Setup ---
# Make sure Visual Studio runs "Pathfinder" instead of ALL_BUILD
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Hide extra meta-targets like ZERO_CHECK
set(CMAKE_SUPPRESS_REGENERATION true)

# --- Assets and Deployment ---
# Copy SDL2.dll next to the executable
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_LIB_AND_DLL_DIR}/SDL2.dll"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    COMMENT "Copying SDL2.dll to the build directory"
)

# Copy assets folder next to the executable
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
