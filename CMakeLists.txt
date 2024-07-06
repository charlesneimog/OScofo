cmake_minimum_required(VERSION 3.20)

set(PDCMAKE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources/pd.cmake/"
    CACHE PATH "Path to pd.cmake")
include(${PDCMAKE_DIR}/pd.cmake)

project(o.scofo~)

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
# │               Library                │
# ╰──────────────────────────────────────╯
file(GLOB SCOFO_SRC "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp")
pd_add_external(o.scofo~ "${SCOFO_SRC}" TARGET oscofo)
target_include_directories(
  oscofo PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/fftw-3.3.10/api")
target_link_libraries(oscofo PUBLIC fftw3)

# ╭──────────────────────────────────────╮
# │              Data Files              │
# ╰──────────────────────────────────────╯
pd_add_datafile(oscofo "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
pd_add_datafile(oscofo "${CMAKE_CURRENT_SOURCE_DIR}/o.scofo~-help.pd")
