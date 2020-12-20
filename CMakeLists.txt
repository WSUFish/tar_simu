cmake_minimum_required(VERSION 3.13)
project(tar_simu2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK")

add_executable(tar_simu2 main.cpp Block.cpp Block.h Header.cpp Header.h Archive.cpp Archive.h ConvertGBK.cpp)