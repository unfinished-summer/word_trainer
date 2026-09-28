cmake_minimum_required(VERSION 3.10)

project(word-trainer LANGUAGES CXX)

# 用到 std::filesystem，必须 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(word-trainer
    word_trainer.cpp
    wordbank.cpp
    ui.cpp
    console.cpp
    date_util.cpp
    path_util.cpp
)

# 把词库复制到构建目录（exe 旁边），程序按 exe 目录找 words.csv
configure_file(words.csv ${CMAKE_CURRENT_BINARY_DIR}/words.csv COPYONLY)
