cmake_minimum_required(VERSION 2.8)

project(match)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fPIC -std=c++0x")

ADD_EXECUTABLE(match search_match.cpp)

