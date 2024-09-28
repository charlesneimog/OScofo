project(o.scofo~  C CXX)

pd_add_external(o.scofo~ o.scofo~.cpp TARGET PdOScofo)

target_include_directories(PdOScofo PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/fftw-3.3.10/api")

if(NOT APPLE)
    target_compile_options(PdOScofo PRIVATE -static-libstdc++ -static-libgcc
                                          -Wl,-allow-multiple-definition)
    target_link_options(PdOScofo PRIVATE -static-libstdc++ -static-libgcc
                      -Wl,-allow-multiple-definition)
endif()


target_link_libraries(PdOScofo PRIVATE OScofo)

pd_add_datafile(pdOScofo "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
pd_add_datafile(pdOScofo
                "${CMAKE_CURRENT_SOURCE_DIR}/Resources/o.scofo~-help.pd")
