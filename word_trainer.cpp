#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;
#include "word.h"
#include "wordbank.h"
#include "ui.h"
#include "console.h"
#include "date_util.h"

int main(int argc,char* argv[])
{
    system("chcp 65001");

    // 没有参数：默认进入背词模式
    if (argc == 1) {
        return playMode();
    }

    // 第一个参数是 --manage：进入管理模式
    if (string(argv[1]) == "--manage") {
        return manageMode();
    }

    return 0;
}



