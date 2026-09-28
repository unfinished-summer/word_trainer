#pragma once
#include <string>
using namespace std;

struct Word
{
    string english;    // 英文
    string chinese;    // 中文
    int right;         // 认识次数
    int wrong;         // 不认识次数
    string lastSeen;   // 上次出现日期，格式 YYYY-MM-DD，如 "2026-09-25"
};