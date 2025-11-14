cmake_minimum_required(VERSION 3.16)
project(equity_calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O2)
endif()

add_executable(equity_calculator
main.cpp
deck.cpp
hand.cpp
utils.cpp
game_state.cpp)
