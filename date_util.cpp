#include <chrono>
#include <format>
using namespace std::chrono;

#include "date_util.h"

std::string today() {
    auto now = system_clock::now();
    auto ymd = year_month_day{ floor<days>(now) };
    return std::format("{:%Y-%m-%d}", ymd);
}

int daysSince(const std::string& date) {
    // ① 用 substr 切字符串："2026-09-24"
    //    位置是固定的：年=0-3，-，月=5-6，-，日=8-9
    int y = stoi(date.substr(0, 4));    // "2026" → 2026
    unsigned m = static_cast<unsigned>(stoi(date.substr(5, 2)));    // "09" → 9
    unsigned d = static_cast<unsigned>(stoi(date.substr(8, 2)));    // "24" → 24

    // ② 用 "/" 运算符拼接成年月日（C++20 特色语法！）
    year_month_day then = year{ y } / month{ m } / day{ d };

    // ③ 把"日历日期"转回"第 N 天"，今天也转，相减
    auto thenDays = sys_days{ then };                                // 那天 = 第几天
    auto todayDays = sys_days{ floor<days>(system_clock::now()) };    // 今天 = 第几天

    return (todayDays - thenDays).count();   // 相减 = 过了几天（整数）
}