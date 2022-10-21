cmake_minimum_required(VERSION 3.16)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")

project(PA1)
add_executable(
	PA1
	main.cpp
)
