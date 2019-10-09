cmake_minimum_required(VERSION 3.14)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chess main.cpp piece.hpp point.hpp piece.cpp board.cpp board.hpp chess.cpp chess.hpp)