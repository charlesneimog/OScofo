cmake_minimum_required(VERSION 3.15)
include(${CMAKE_CURRENT_SOURCE_DIR}/Resources/pd.build/pd.cmake) # pd.build
project(pd-follower)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

#╭──────────────────────────────────────╮
#│                 KFR                  │
#╰──────────────────────────────────────╯
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Kfr)

#╭──────────────────────────────────────╮
#│               Library                │
#╰──────────────────────────────────────╯
file(GLOB FOLLOWER "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp") 
if (NEIMOG_LIBRARY)
    add_library(pd-follower STATIC ${FOLLOWER})
    # target_link_libraries(pd-follower kfr)
    # target_link_libraries(pd-follower kfr_dft)
else()
	set_pd_external_path(${CMAKE_CURRENT_SOURCE_DIR}/)
    add_pd_external(pd-follower follower~ ${FOLLOWER})
    # target_link_libraries(pd-follower kfr)
    # target_link_libraries(pd-follower kfr_dft)
endif()






