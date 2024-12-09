cmake_minimum_required(VERSION 3.20)
project(OScofoLan)

add_executable(OScofoLan main.cpp)

# Specify the path to the static library
set(TREE_SITTER_HIGHLIGHT_LIB_PATH
    /home/neimog/Documents/Git/OScofo/Libraries/tree-sitter/highlight/build/release/libtree_sitter_highlight.a
)

# Link the static library to your executable
target_link_libraries(OScofoLan PUBLIC ${TREE_SITTER_HIGHLIGHT_LIB_PATH})

target_include_directories(
    OScofoLan PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../Libraries/tree-sitter/lib/include")

target_include_directories(
    OScofoLan PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../Libraries/tree-sitter/highlight/include/")

set(BUILD_SHARED_LIBS OFF)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../../Libraries/tree-sitter/lib/"
                 ${CMAKE_BINARY_DIR}/tree-sitter)

add_library(score_parser STATIC ${CMAKE_CURRENT_SOURCE_DIR}/../tree-sitter-scofo/src/parser.c)
target_link_libraries(OScofoLan PUBLIC score_parser tree-sitter)
target_link_libraries(OScofoLan PUBLIC ${TREE_SITTER_HIGHLIGHT_LIB_PATH})
