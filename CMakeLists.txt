cmake_minimum_required(VERSION 3.10)

project(word-trainer LANGUAGES CXX)

# MSVC 按 UTF-8 解读源码（源文件是 UTF-8 无 BOM）
if(MSVC)
    add_compile_options(/utf-8)
endif()

# 用到 std::filesystem，必须 C++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(word-trainer
    word_trainer.cpp
    wordbank.cpp
    ui.cpp
    console.cpp
    date_util.cpp
    path_util.cpp
)

# raylib：V2.0 图形界面依赖。
# 不用 vcpkg（已知问题），改用 FetchContent 拉官方源码编译。
include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(raylib)

target_link_libraries(word-trainer PRIVATE raylib)

# 定义宏，把源码目录传进程序
target_compile_definitions(word-trainer PRIVATE PROJECT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
