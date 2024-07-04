cmake_minimum_required(VERSION 3.20)

set(PDCMAKE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources/pd.cmake/"
    CACHE PATH "Path to pd.cmake")
include(${PDCMAKE_DIR}/pd.cmake)

project(follower~)

# ╭──────────────────────────────────────╮
# │                FFTW3                 │
# ╰──────────────────────────────────────╯

cmake_policy(SET CMP0135 NEW)
option(BUILD_SHARED_LIBS OFF)
option(BUILD_TESTS OFF)
# option(DISABLE_FORTRAN ON)

# check if fftw-3.3.10.tar.gz has been downloaded
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
file(GLOB FOLLOWER "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp")

if(NEIMOG_LIBRARY)
  add_library(pd-follower STATIC ${FOLLOWER})
  target_include_directories(
    pd-follower PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/fftw-3.3.10/api")
else()
  pd_add_external(follower~ "${FOLLOWER}" TARGET follower_tilde)
  target_include_directories(
    follower_tilde
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/fftw-3.3.10/api")
  target_link_libraries(follower_tilde PRIVATE fftw3)

  # Ensure proper compilation definitions
  # target_compile_definitions(follower_tilde PRIVATE FFTW3)

endif()
