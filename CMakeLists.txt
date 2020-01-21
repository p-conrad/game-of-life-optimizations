cmake_minimum_required(VERSION 3.14)
project(game_of_life)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FIND_PACKAGE(OpenMP REQUIRED)

add_executable(game_of_life src/main.cpp src/GameField.cpp src/GameField.h src/Presets.h src/SimpleMatrix.h)

target_link_libraries(game_of_life PUBLIC OpenMP::OpenMP_CXX)