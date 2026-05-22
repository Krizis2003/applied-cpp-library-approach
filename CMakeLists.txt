cmake_minimum_required(VERSION 3.10)
project(applied_cpp_library_approach)

# Общие настройки для всех примеров серии
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем части серии по мере готовности
add_subdirectory(01_strong_types)

# add_subdirectory(02_tag_dispatching) # Для будущих выпусков
