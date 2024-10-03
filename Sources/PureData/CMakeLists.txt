project(o.scofo~ C CXX)

if(EMSCRIPTEN)
  set(PD_TARGET_OBJ o.scofo_tilde)
else()
  set(PD_TARGET_OBJ PdOScofo)
endif()

pd_add_external(${PD_TARGET_OBJ} o.scofo~.cpp)

target_include_directories(
  ${PD_TARGET_OBJ}
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/fftw-3.3.10/api")

if(NOT APPLE)
  target_compile_options(
    ${PD_TARGET_OBJ} PRIVATE -static-libstdc++ -static-libgcc
                             -Wl,-allow-multiple-definition)
  target_link_options(${PD_TARGET_OBJ} PRIVATE -static-libstdc++ -static-libgcc
                      -Wl,-allow-multiple-definition)
endif()

target_link_libraries(${PD_TARGET_OBJ} PRIVATE OScofo)

pd_add_datafile(${PD_TARGET_OBJ} "${CMAKE_CURRENT_SOURCE_DIR}/../../README.md")
pd_add_datafile(${PD_TARGET_OBJ}
                "${CMAKE_CURRENT_SOURCE_DIR}/../../Resources/o.scofo~-help.pd")
