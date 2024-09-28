find_package(Python REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${pybind11_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Sources)
pybind11_add_module(_OScofo PyOScofo.cpp)
target_link_libraries(_OScofo PRIVATE OScofo ${PYTHON_LIBRARIES})

set_target_properties(
  _OScofo
  PROPERTIES CXX_STANDARD 11
             CXX_STANDARD_REQUIRED YES
             CXX_EXTENSIONS NO)
if(NOT APPLE)
  target_compile_options(_OScofo PRIVATE -static-libstdc++ -static-libgcc
                                         -Wl,-allow-multiple-definition)
  target_link_options(_OScofo PRIVATE -static-libstdc++ -static-libgcc
                      -Wl,-allow-multiple-definition)
endif()
install(TARGETS _OScofo
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Python/OScofo/)