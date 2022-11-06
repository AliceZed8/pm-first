cmake_minimum_required(VERSION 3.23)
project(Project_SFML)

set(CMAKE_CXX_STANDARD 17)
set(SFML_INCLUDE_DIR "SFML/include/")
set(SFML_LIBRARY_DIR "SFML/lib/")
set(SFML_DIR "SFML/lib/cmake/SFML/")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(Project_SFML main.cpp)
target_link_libraries (Project_SFML sfml-graphics sfml-window sfml-system)

