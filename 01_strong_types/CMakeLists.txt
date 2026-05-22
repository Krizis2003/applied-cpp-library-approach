cmake_minimum_required(VERSION 3.10)
project(strong_types_examples)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

macro(add_example_test NAME SOURCE)
    add_executable(${NAME} ${SOURCE})
    add_test(NAME ${NAME} COMMAND ${NAME})
endmacro()

add_example_test(example_01_speed_evolution src/01_speed_evolution.cpp)
add_example_test(example_02_logic_and_price src/02_logic_and_price.cpp)
add_example_test(example_03_type_wrapper src/03_type_wrapper.cpp)
add_example_test(example_04_discount_features src/04_discount_features.cpp)
add_example_test(example_05_modern_cpp src/05_modern_cpp_features.cpp)
add_example_test(example_06_parameter_object src/06_parameter_object.cpp)
