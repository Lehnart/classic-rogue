cmake_minimum_required(VERSION 3.5)

project(cpp-old-rogue LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(/W3)

add_executable(cpp-old-rogue src/main.cpp src/window.cpp src/renderer.cpp src/block.cpp src/hero.cpp)

target_include_directories(cpp-old-rogue PUBLIC "include/")
target_link_libraries(cpp-old-rogue "${CMAKE_CURRENT_LIST_DIR}/lib/x86/SDL2.lib" "${CMAKE_CURRENT_LIST_DIR}/lib/x86/SDL2Main.lib")
