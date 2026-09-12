cmake_minimum_required(VERSION 3.15)
project(strong_types_examples CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

enable_testing()

function(add_example NAME SOURCE)
    add_executable(${NAME} ${SOURCE})
    add_test(NAME ${NAME} COMMAND ${NAME})
endfunction()

add_example(demo         src/demo.cpp)
add_example(alternatives src/alternatives.cpp)
