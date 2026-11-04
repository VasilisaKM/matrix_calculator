cmake_minimum_required(VERSION 3.20)
project(Matrix_Calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# сборка с предупреждениями
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

include_directories(include)

# Создаем исполняемый файл из двух .cpp
add_executable(matrix_calculator src/main.cpp src/matrix.cpp)
enable_testing()
add_subdirectory(tests)