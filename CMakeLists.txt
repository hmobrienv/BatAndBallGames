cmake_minimum_required(VERSION 3.3)
project(BatAndBallGamesC__)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(BatAndBallGamesC__ ${SOURCE_FILES})