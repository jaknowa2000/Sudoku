cmake_minimum_required(VERSION 3.10)  # CMake version check
project(solver)              
set(CMAKE_CXX_STANDARD 20)
set(PYBIND11_PYTHON_VERSION 3.10)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -fPIC")

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)


pybind11_add_module(${PROJECT_NAME} pywrap.cpp sudoku_board.cpp)

target_compile_definitions(${PROJECT_NAME} PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
target_include_directories(${PROJECT_NAME} PRIVATE ${PYBIND11_INCLUDE_DIRS})
# set (CMAKE_GENERATOR "NMake Makefiles" CACHE INTERNAL "" FORCE)