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
    # Percorsi per SDL2 su Windows
    set(SDL2_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/externals/SDL2-2.32.10/include")
    set(SDL2_LIB_DIR "${PROJECT_SOURCE_DIR}/externals/SDL2-2.32.10/lib/x64")

    # Verifica presenza file .lib
    if(NOT EXISTS "${SDL2_LIB_DIR}/SDL2.lib")
        message(FATAL_ERROR "SDL2.lib non trovato in ${SDL2_LIB_DIR}")
    endif()

    # Librerie da linkare (percorso completo)
    set(SDL2_LIBRARIES
        "${SDL2_LIB_DIR}/SDL2.lib"
        "${SDL2_LIB_DIR}/SDL2main.lib"
    )

elseif(UNIX)
    # Linux: trova SDL2 tramite pkg-config o scarica se non presente
    find_package(PkgConfig)
    if(PkgConfig_FOUND)
        pkg_check_modules(SDL2 sdl2)
    endif()

    if(NOT SDL2_FOUND)
        message(STATUS "SDL2 non trovato, download automatico tramite FetchContent...")

        include(FetchContent)
        FetchContent_Declare(
            SDL2
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-2.30.9 # o versione stabile più recente
        )
        FetchContent_MakeAvailable(SDL2)

        set(SDL2_INCLUDE_DIR ${sdl2_SOURCE_DIR}/include)
        set(SDL2_LIBRARIES SDL2)
    else()
        set(SDL2_INCLUDE_DIR ${SDL2_INCLUDE_DIRS})
        set(SDL2_LIBRARIES ${SDL2_LIBRARIES})
    endif()
endif()

# --- Create executable ---
add_executable(${PROJECT_NAME} ${SOURCE_FILES} "${PROJECT_SOURCE_DIR}/src/main.cpp")

# --- Include directories ---
target_include_directories(${PROJECT_NAME} PRIVATE
    ${INTERNAL_INCLUDES}
    ${SDL2_INCLUDE_DIR}
)

# --- Link libraries ---
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

# --- Output directories ---
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)

# --- Visual Studio specific ---
if(WIN32)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    set(CMAKE_SUPPRESS_REGENERATION true)

    # Copia SDL2.dll accanto all'eseguibile
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_LIB_DIR}/SDL2.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMENT "Copying SDL2.dll to build directory"
    )
endif()

# --- Copy assets ---
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
