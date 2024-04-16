cmake_minimum_required(VERSION 3.15)
include(${CMAKE_CURRENT_SOURCE_DIR}/Resources/pd.build/pd.cmake) # pd.build
project(pd-follower)

#╭──────────────────────────────────────╮
#│           Library Sources            │
#╰──────────────────────────────────────╯
file(GLOB FOLLOWER "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp") 
message(status "FOLLOWER: ${FOLLOWER}")

if (NEIMOG_LIBRARY)
    add_library(pd-follower STATIC ${FOLLOWER})
    set_target_properties(pd-follower PROPERTIES CXX_STANDARD 20)
else()
	set_pd_external_path(${CMAKE_CURRENT_SOURCE_DIR}/)
    add_pd_external(pd-follower follower ${FOLLOWER})
    set_target_properties(pd-follower PROPERTIES CXX_STANDARD 20)
endif()






