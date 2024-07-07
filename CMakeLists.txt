cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(OScofo LANGUAGES CXX)

set(PDCMAKE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources/pd.cmake/"
    CACHE PATH "Path to pd.cmake")
include(${PDCMAKE_DIR}/pd.cmake)

option(BUILD_PY_MODULE "Build Python Module" OFF)
option(BUILD_PD_OBJECT "Build PureData Object" OFF)
option(BUILD_ALL "Build Python Module and PureData Object" OFF)

if(BUILD_ALL)
    set(BUILD_PY_MODULE ON)
    set(BUILD_PD_OBJECT ON)
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

file(ARCHIVE_EXTRACT INPUT ${CMAKE_BINARY_DIR}/fftw-3.3.10.tar.gz DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/)

add_subdirectory(Libraries/fftw-3.3.10 EXCLUDE_FROM_ALL)
set_target_properties(fftw3 PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set_target_properties(fftw3 PROPERTIES POSITION_INDEPENDENT_CODE ON)

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
target_include_directories(OScofo PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/fftw-3.3.10/api")

# ╭──────────────────────────────────────╮
# │            Python Module             │
# ╰──────────────────────────────────────╯
if(BUILD_PY_MODULE)
    find_package(Python REQUIRED COMPONENTS Interpreter Development)
    find_package(pybind11 REQUIRED)
    include_directories(${PYTHON_INCLUDE_DIRS})
    include_directories(${pybind11_INCLUDE_DIR})
    pybind11_add_module(_OScofo Sources/Python/PyOScofo.cpp)
    target_link_libraries(_OScofo PRIVATE OScofo ${PYTHON_LIBRARIES})
    set_target_properties(
        _OScofo
        PROPERTIES CXX_STANDARD 11
                   CXX_STANDARD_REQUIRED YES
                   CXX_EXTENSIONS NO)
    if(NOT APPLE)
        target_compile_options(_OScofo PRIVATE -static-libstdc++ -static-libgcc -Wl,-allow-multiple-definition)
        target_link_options(_OScofo PRIVATE -static-libstdc++ -static-libgcc -Wl,-allow-multiple-definition)
    endif()
    install(TARGETS _OScofo DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Python/OScofo/)
endif()

# ╭──────────────────────────────────────╮
# │           PureData Object            │
# ╰──────────────────────────────────────╯
if(BUILD_PD_OBJECT)
    project(o.scofo~)
    pd_add_external(o.scofo~ Sources/PureData/o.scofo~.cpp TARGET PdOScofo)
    target_include_directories(PdOScofo PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/fftw-3.3.10/api")
    if(NOT APPLE)
        target_compile_options(PdOScofo PRIVATE -static-libstdc++ -static-libgcc -Wl,-allow-multiple-definition)
        target_link_options(PdOScofo PRIVATE -static-libstdc++ -static-libgcc -Wl,-allow-multiple-definition)
    endif()
    target_link_libraries(PdOScofo PRIVATE OScofo)

    pd_add_datafile(pdOScofo "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
    pd_add_datafile(pdOScofo "${CMAKE_CURRENT_SOURCE_DIR}/Resources/o.scofo~-help.pd")
endif()
