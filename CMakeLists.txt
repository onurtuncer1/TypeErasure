cmake_minimum_required(VERSION 3.22)
project(types LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Geometry/D2/Intersect.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    TypeErasure
)
