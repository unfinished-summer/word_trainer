#include <filesystem>
namespace fs = std::filesystem;

#include "path_util.h"

//代码里写 `__FILE__`，**编译器在编译时**会把它替换成一个字符串 —— 当前源文件的路径。
std::string cppDir() {
    //fs::path默认按GBK解读，然而我使用了/utf-8编译,所以要用u8path(在C++20中使用 char8_t 构造告诉它按 UTF-8 解码)
    return fs::path(reinterpret_cast<const char8_t*>(__FILE__)).parent_path().string();
}