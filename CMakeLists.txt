cmake_minimum_required(VERSION 3.15)
include(${CMAKE_CURRENT_SOURCE_DIR}/Resources/pd.build/pd.cmake) # pd.build
project(pd-follower)

#╭──────────────────────────────────────╮
#│             Static FFTW3             │
#╰──────────────────────────────────────╯
set(BUILD_SHARED_LIBS OFF)
set(BUILD_TESTS OFF)
set(DISABLE_FORTRAN ON)
# set(ENABLE_FLOAT ON)

# check if fftw-3.3.10.tar.gz has been downloaded
set(FFTW3_FILE ${CMAKE_BINARY_DIR}/fftw-3.3.10.tar.gz)
if (NOT EXISTS ${FFTW3_FILE})
    message(STATUS "Downloading FFTW3")
    file(DOWNLOAD https://www.fftw.org/fftw-3.3.10.tar.gz ${FFTW3_FILE})
endif()

file(ARCHIVE_EXTRACT
    INPUT ${CMAKE_BINARY_DIR}/fftw-3.3.10.tar.gz
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/
)

add_subdirectory(Libraries/fftw-3.3.10)
set_target_properties(fftw3 PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set_target_properties(fftw3 PROPERTIES POSITION_INDEPENDENT_CODE ON)

#╭──────────────────────────────────────╮
#│                Aubio                 │
#╰──────────────────────────────────────╯
set(HAVE_CONFIG_H ON)
set(HAVE_STDLIB_H ON)
set(HAVE_STDIO_H ON)
set(HAVE_MATH_H ON)
set(HAVE_STRING_H ON)
set(HAVE_LIMITS_H ON)
set(HAVE_STDARG_H ON)
set(HAVE_GETOPT_H ON)
set(HAVE_UNISTD_H ON)
set(HAVE_C99_VARARGS_MACROS ON)
set(HAVE_WAVREAD OFF)
set(HAVE_WAVWRITE OFF)
set(HAVE_MEMCPY_HACKS ON)
set(HAVE_ERRNO_H ON)
add_definitions(-DHAVE_CONFIG_H)
add_definitions(-DHAVE_FFTW3)
add_definitions(-DAUBIO_UNSTABLE)
add_definitions(-DHAVE_AUBIO_DOUBLE)
configure_file(Resources/AubioConfig.h.in config.h)

# Collect source files from different directories
file(GLOB AUBIO_SOURCES "Libraries/aubio/src/*.c")
file(GLOB AUBIO_UTILS "Libraries/aubio/src/utils/*.c")
file(GLOB AUBIO_FFT "Libraries/aubio/src/spectral/*.c")
file(GLOB AUBIO_TEMPORAL "Libraries/aubio/src/temporal/*.c")
file(GLOB AUBIO_PITCH "Libraries/aubio/src/pitch/*.c")

add_library(aubio STATIC ${AUBIO_SOURCES} ${AUBIO_PITCH} ${AUBIO_UTILS} ${AUBIO_FFT} ${AUBIO_TEMPORAL})
target_link_libraries(aubio PUBLIC fftw3)
target_include_directories(aubio PUBLIC "${PROJECT_BINARY_DIR}"
                                        "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/aubio/src")
set_target_properties(aubio PROPERTIES POSITION_INDEPENDENT_CODE ON)

#╭──────────────────────────────────────╮
#│               Library                │
#╰──────────────────────────────────────╯
file(GLOB FOLLOWER "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp") 

if (NEIMOG_LIBRARY)
    add_library(pd-follower STATIC ${FOLLOWER})
    set_target_properties(pd-follower PROPERTIES CXX_STANDARD 20)
    target_include_directories(pd-follower PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/fftw-3.3.10/api")
    target_link_libraries(pd-follower aubio)
else()
	set_pd_external_path(${CMAKE_CURRENT_SOURCE_DIR}/)
    add_pd_external(pd-follower follower~ ${FOLLOWER})
    set_target_properties(pd-follower PROPERTIES CXX_STANDARD 20)
    target_include_directories(pd-follower PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/fftw-3.3.10/api")
    target_link_libraries(pd-follower aubio)
endif()






