cmake_minimum_required(VERSION 3.19)

include(${CMAKE_CURRENT_SOURCE_DIR}/max-sdk-base/script/max-pretarget.cmake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES x86_64;arm64)  # Enable Apple silicon builds

include_directories(
	"${MAX_SDK_INCLUDES}"
	"${MAX_SDK_MSP_INCLUDES}"
	"${MAX_SDK_JIT_INCLUDES}"
)

add_library(
	"${PROJECT_NAME}"
	MODULE
	"o.scofo~.cpp")


include(${CMAKE_CURRENT_SOURCE_DIR}/max-sdk-base/script/max-posttarget.cmake)