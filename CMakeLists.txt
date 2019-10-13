cmake_minimum_required(VERSION 3.14)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chess src/main.cpp src/piece.hpp src/point.hpp src/piece.cpp src/board.cpp src/board.hpp src/chess.cpp src/chess.hpp)