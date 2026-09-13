cmake_minimum_required(VERSION 4.2)
project(poker)
set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

add_executable(poker main.cpp)

target_include_directories(poker PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(poker PRIVATE ${OpenCV_LIBS} darkhelp)

