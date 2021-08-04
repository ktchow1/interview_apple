cmake_minimum_required(VERSION 3.18.2)
project(siri)


set(CMAKE_C_COMPILER /usr/bin/gcc-10)
set(CMAKE_CXX_COMPILER /usr/bin/g++-10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions(-std=c++20)
add_definitions(-g)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_C_FLAGS   "-g -O0")
    set(CMAKE_CXX_FLAGS "-g -O0")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set(CMAKE_C_FLAGS   "-g -O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS "-g -O3 -DNDEBUG")
endif()


###################
### (1) include ###
###################
include_directories(
    include
)

##################
### (2) source ###
##################
file(GLOB SOURCES
     "src/*.cpp"
)
add_executable(Test ${SOURCES})

##################################
### (3) link path and link lib ###
##################################
target_link_libraries(Test -L/lib/x86_64-linux-gnu)





