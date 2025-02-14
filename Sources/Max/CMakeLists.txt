cmake_minimum_required(VERSION 3.25)
project(max_o.scofo)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (APPLE)
	set(CMAKE_OSX_DEPLOYMENT_TARGET "14")
	# check if I am on arm64 or x86_64
	execute_process(COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE)
	if (${ARCHITECTURE} STREQUAL "x86_64")
		set(CMAKE_OSX_ARCHITECTURES "x86_64")
	else()
		set(CMAKE_OSX_ARCHITECTURES "arm64")
	endif()
	message(STATUS "Architecture: ${ARCHITECTURE}")
endif()

set(C74_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/max")
install(FILES "./o.scofo~.maxhelp" DESTINATION "${C74_LIBRARY_OUTPUT_DIRECTORY}")
include(${CMAKE_CURRENT_SOURCE_DIR}/max-sdk-base/script/max-pretarget.cmake)
set("${PROJECT_NAME}_EXTERN_OUTPUT_NAME" "o.scofo~")

add_library(${PROJECT_NAME} MODULE "o.scofo~.cpp;maxlua.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE OScofo)
target_include_directories(${PROJECT_NAME} PRIVATE ${MAX_SDK_INCLUDES})
target_include_directories(${PROJECT_NAME} PRIVATE ${MAX_SDK_MSP_INCLUDES})

include(${CMAKE_CURRENT_SOURCE_DIR}/max-sdk-base/script/max-posttarget.cmake)