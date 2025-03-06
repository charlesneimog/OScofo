cmake_minimum_required(VERSION 3.25)
project(OScofo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_PY_MODULE "Build Python Module" OFF)
option(BUILD_PD_OBJECT "Build PureData Object" ON)
option(BUILD_MAX_OBJECT "Build Max Object" OFF)
option(BUILD_ALL "Build Python Module and PureData Object" OFF)
option(BUILD_WITH_LUA "Build Lua Module embbeded on OScofo" ON)
option(UPDATE_OSCOFO_LANGUAGE "Update OScofo language grammar.js" OFF)

# check if it is EMSCRIPTEN
if(EMSCRIPTEN)
    message(STATUS "Emscripten compilation")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_BOOST_HEADERS=1")
endif()

if(BUILD_ALL)
    set(BUILD_PY_MODULE ON)
    set(BUILD_PD_OBJECT ON)
    if(NOT LINUX)
        set(BUILD_MAX_OBJECT ON)
    endif()
endif()

if(BUILD_ALL_OBJECTS)
    set(BUILD_PD_OBJECT ON)
    if(NOT LINUX)
        set(BUILD_MAX_OBJECT ON)
    endif()
endif()

if(BUILD_PD_OBJECT)
    set(PDCMAKE_DIR
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources/pd.cmake/"
        CACHE PATH "Path to pd.cmake")
    include(${PDCMAKE_DIR}/pd.cmake)
endif()

# ╭──────────────────────────────────────╮
# │                FFTW3                 │
# ╰──────────────────────────────────────╯
cmake_policy(SET CMP0135 NEW)
option(BUILD_SHARED_LIBS OFF)
option(BUILD_TESTS OFF)
set(FFTW3_FILE ${CMAKE_BINARY_DIR}/fftw-3.3.10.tar.gz)
if(NOT EXISTS ${FFTW3_FILE})
    message(STATUS "Downloading FFTW3")
    file(
        DOWNLOAD https://www.fftw.org/fftw-3.3.10.tar.gz ${FFTW3_FILE}
        SHOW_PROGRESS
        STATUS DOWNLOAD_STATUS)
endif()

file(ARCHIVE_EXTRACT INPUT ${CMAKE_BINARY_DIR}/fftw-3.3.10.tar.gz DESTINATION
     ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/)

add_subdirectory(Libraries/fftw-3.3.10 EXCLUDE_FROM_ALL)
set_target_properties(fftw3 PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set_target_properties(fftw3 PROPERTIES POSITION_INDEPENDENT_CODE ON)

# ╭──────────────────────────────────────╮
# │             Tree-Sitter              │
# ╰──────────────────────────────────────╯
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(Libraries/tree-sitter/lib/ EXCLUDE_FROM_ALL)
set(PARSER_OUTPUT_C ${CMAKE_CURRENT_SOURCE_DIR}/Resources/tree-sitter-scofo/src/parser.c)

if(UPDATE_OSCOFO_LANGUAGE)
    find_program(TREE_SITTER_EXECUTABLE tree-sitter)
    set(TREE_SITTER_WORKING_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources/tree-sitter-scofo)
    if(TREE_SITTER_EXECUTABLE AND NOT MINGW)
        add_custom_command(
            OUTPUT ${PARSER_OUTPUT_C}
            COMMAND ${TREE_SITTER_EXECUTABLE} generate --no-bindings
            WORKING_DIRECTORY ${TREE_SITTER_WORKING_DIR}
            COMMENT "Generating Tree-sitter parser..."
            VERBATIM)
        add_library(score_parser STATIC ${PARSER_OUTPUT_C})
        add_custom_target(generate_tree_sitter_parser DEPENDS ${PARSER_OUTPUT_C})
        add_dependencies(score_parser generate_tree_sitter_parser)
    else()
        message(
            WARNING
                "Tree-sitter executable not found. Parser generation skipped. Please install tree-sitter-cli."
        )
        add_library(score_parser STATIC ${PARSER_OUTPUT_C})
    endif()
else()
    add_library(score_parser STATIC ${PARSER_OUTPUT_C})
endif()

set_target_properties(score_parser PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(score_parser PUBLIC Libraries/tree-sitter/lib/include)

# ╭──────────────────────────────────────╮
# │                 Lua                  │
# ╰──────────────────────────────────────╯
if(BUILD_WITH_LUA)
    if(NOT TARGET lua)
        add_library(lua STATIC "${LIB_DIR}/lua/onelua.c")
        set_target_properties(lua PROPERTIES POSITION_INDEPENDENT_CODE ON C_STANDARD 99)
        target_compile_definitions(lua PUBLIC "-DMAKE_LIB")
        target_include_directories(lua PUBLIC "${LIB_DIR}/lua")
    endif()
    add_definitions(-DOSCOFO_LUA)

else()
    message(STATUS "Lua not included")
endif()

# ╭──────────────────────────────────────╮
# │                OScofo                │
# ╰──────────────────────────────────────╯
list(APPEND ScofoSrc Sources/OScofo/mdp.cpp)
list(APPEND ScofoSrc Sources/OScofo/mir.cpp)
list(APPEND ScofoSrc Sources/OScofo/score.cpp)
list(APPEND ScofoSrc Sources/OScofo/lua.cpp)
list(APPEND ScofoSrc Sources/OScofo/OScofo.cpp)
add_library(OScofo STATIC ${ScofoSrc})

target_include_directories(OScofo
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Resources/tree-sitter-score/src")
target_include_directories(OScofo PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/lua")
target_include_directories(OScofo PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/fftw-3.3.10/api")
target_include_directories(OScofo PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Sources/")

set_target_properties(OScofo PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(OScofo PUBLIC fftw3 tree-sitter score_parser lua)

# Boost Libraries
if(NOT EMSCRIPTEN)
    include(FetchContent)
    set(BOOST_URL "https://archives.boost.io/release/1.87.0/source/boost_1_87_0.tar.bz2")
    set(BOOST_TAR "${CMAKE_BINARY_DIR}/boost_1_87_0.tar.bz2")
    if(NOT EXISTS ${BOOST_TAR})
        message(STATUS "Downloading Boost...")
        file(DOWNLOAD ${BOOST_URL} ${BOOST_TAR} SHOW_PROGRESS)
    endif()
    FetchContent_Declare(boost URL file://${BOOST_TAR})
    FetchContent_MakeAvailable(boost)
    include_directories(${boost_SOURCE_DIR})
endif()

if(LINUX)
    target_compile_options(OScofo PUBLIC -static-libstdc++ -Wl,--exclude-libs,ALL)
endif()

if(NOT EMSCRIPTEN AND NOT MSVC)
    target_compile_options(
        OScofo
        PRIVATE -Wall # Enable all common warnings
                -Wextra # Enable extra warnings -Wpedantic # Enforce strict compliance with
                        # standards
                -Wno-unused-parameter # Suppress unused parameter warnings
                -Wshadow # Warn about shadowed variable declarations
                -Wformat=2 # Enable stricter format string checks
                -Wnull-dereference # Warn on dereferences of null pointers
                # Debug
                $<$<CONFIG:Debug>:
                -g
                -O0
                >
                # Release
                $<$<CONFIG:Release>:
                -O3
                -DNDEBUG
                >)
endif()

# ╭──────────────────────────────────────╮
# │            Python Module             │
# ╰──────────────────────────────────────╯
if(BUILD_PY_MODULE)
    add_subdirectory(Sources/Python)
endif()

# ╭──────────────────────────────────────╮
# │           PureData Object            │
# ╰──────────────────────────────────────╯
if(BUILD_PD_OBJECT)
    add_subdirectory(Sources/PureData)
endif()

# ╭──────────────────────────────────────╮
# │             Max Obj                  │
# ╰──────────────────────────────────────╯
if(BUILD_MAX_OBJECT)
    add_subdirectory(Sources/Max)
endif()
