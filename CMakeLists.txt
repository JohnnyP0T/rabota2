cmake_minimum_required(VERSION 2.8)

project(cmake_example_1)
# ${PROJECT_NAME}
# set(CMAKE_CXX_STANDART 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
#list(APPEND CMAKE_CXX_FLAGS "-pthread -std=c++11 ${CMAKE_CXX_FLAGS}")
file(GLOB
            CPPS "*.cpp")

add_executable(${PROJECT_NAME} ${CPPS})
