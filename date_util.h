#pragma once
#include <string>

std::string today();   // 返回今天日期，格式 YYYY-MM-DD
int daysSince(const std::string& date);   // 今天 - date = 隔了几天