cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES x86_64;arm64)  # Enable Apple silicon builds

# IF MAC, USE APPLE CLANG
if(APPLE)
  set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
  set(CMAKE_C_COMPILER "/usr/bin/clang")
endif()

project(OScofo  LANGUAGES C CXX)

set(PDCMAKE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources/pd.cmake/"
    CACHE PATH "Path to pd.cmake")
include(${PDCMAKE_DIR}/pd.cmake)

option(BUILD_PY_MODULE "Build Python Module" OFF)
option(BUILD_PD_OBJECT "Build PureData Object" OFF)
option(BUILD_MAX_OBJECT "Build Max Object" OFF)
option(BUILD_ALL "Build Python Module and PureData Object" OFF)

if(BUILD_ALL)
  set(BUILD_PY_MODULE ON)
  set(BUILD_PD_OBJECT ON)
  set(BUILD_MAX_OBJECT ON)
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
  file(DOWNLOAD https://www.fftw.org/fftw-3.3.10.tar.gz ${FFTW3_FILE})
endif()

file(ARCHIVE_EXTRACT INPUT ${CMAKE_BINARY_DIR}/fftw-3.3.10.tar.gz DESTINATION
     ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/)

add_subdirectory(Libraries/fftw-3.3.10 EXCLUDE_FROM_ALL)
set_target_properties(fftw3 PROPERTIES LIBRARY_OUTPUT_DIRECTORY
                                       ${CMAKE_SOURCE_DIR})
set_target_properties(fftw3 PROPERTIES POSITION_INDEPENDENT_CODE ON)

# ╭──────────────────────────────────────╮
# │             Tree-Sitter              │
# ╰──────────────────────────────────────╯
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(Libraries/tree-sitter/lib/ EXCLUDE_FROM_ALL)
find_program(TREE_SITTER_EXECUTABLE tree-sitter)

if(TREE_SITTER_EXECUTABLE)
  message(STATUS "Tree-sitter executable found at ${TREE_SITTER_EXECUTABLE}")
  execute_process(
    COMMAND ${TREE_SITTER_EXECUTABLE} generate
    WORKING_DIRECTORY
      ${CMAKE_CURRENT_SOURCE_DIR}/Sources/OScofo/tree-sitter-score/
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error_output)
else()
  message(
    FATAL_ERROR "Tree-sitter executable not found. Please install Tree-sitter.")
endif()

add_library(score_parser STATIC Sources/OScofo/tree-sitter-score/src/parser.c)
include_directories(Libraries/tree-sitter/include)

# ╭──────────────────────────────────────╮
# │                OScofo                │
# ╰──────────────────────────────────────╯
list(APPEND SCofoSrc Sources/OScofo/mdp.cpp)
list(APPEND SCofoSrc Sources/OScofo/mir.cpp)
list(APPEND SCofoSrc Sources/OScofo/score.cpp)
list(APPEND SCofoSrc Sources/OScofo/OScofo.cpp)
add_library(OScofo STATIC ${SCofoSrc})
target_link_libraries(OScofo PUBLIC fftw3)
set_target_properties(OScofo PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(
  OScofo PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/fftw-3.3.10/api")
target_compile_options(OScofo PRIVATE $<$<CONFIG:DEBUG>:-g -O0>)
target_link_libraries(OScofo PRIVATE tree-sitter score_parser)

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