cmake_minimum_required(VERSION 3.24)
project(BSM)

set(CMAKE_CXX_STANDARD 17)

add_executable(BSM main.cpp Reading.cpp OptionsPricing.cpp OptionsPricing.h Parsing.h Parsing.cpp)
