cmake_minimum_required(VERSION 3.20)
project(Timber LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Manually set SFML paths
set(SFML_DIR /opt/homebrew/lib/cmake/SFML)
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(timber main.cpp)

target_link_libraries(timber PRIVATE sfml-graphics sfml-window sfml-system)