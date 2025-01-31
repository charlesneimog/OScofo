project(o.scofo~ C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE OBJ_SOURCES "*.cpp" "*.h")
pd_add_external(o.scofo~ "${OBJ_SOURCES}")

# ╭──────────────────────────────────────╮
# │           PureData Objects           │
# ╰──────────────────────────────────────╯

target_include_directories(o.scofo_tilde
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/fftw-3.3.10/api")

if(NOT APPLE AND NOT EMSCRIPTEN)
    target_compile_options(o.scofo_tilde PRIVATE -static-libstdc++ -static-libgcc
                                                 -Wl,-allow-multiple-definition)
    target_link_options(o.scofo_tilde PRIVATE -static-libstdc++ -static-libgcc
                        -Wl,-allow-multiple-definition)
endif()

target_compile_options(
    o.scofo_tilde
    PRIVATE -Wall
            -Wextra
            -Wpedantic
            -Wno-unused-parameter
            $<$<CONFIG:Debug>:-g
            -O0>
            $<$<CONFIG:Release>:-O3
            -DNDEBUG>)

target_link_libraries(o.scofo_tilde PRIVATE OScofo)

pd_add_datafile(o.scofo_tilde "${CMAKE_CURRENT_SOURCE_DIR}/../../README.md")
pd_add_datafile(o.scofo_tilde "${CMAKE_CURRENT_SOURCE_DIR}/../../Resources/o.scofo~-help.pd")
