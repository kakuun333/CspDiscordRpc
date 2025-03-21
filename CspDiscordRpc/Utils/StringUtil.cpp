#include "pch.h"
#include "StringUtil.h"

namespace util
{

std::string ConvertMillisecondsToDHMS(const int64_t& milliseconds)
{
    int64_t total_seconds = milliseconds / 1000;  // 轉換成秒
    int days = total_seconds / 86400;             // 1 天 = 86400 秒
    int hours = (total_seconds % 86400) / 3600;   // 1 小時 = 3600 秒
    int minutes = (total_seconds % 3600) / 60;    // 1 分鐘 = 60 秒
    int seconds = total_seconds % 60;             // 剩餘秒數

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << days << ":"
        << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;

    return oss.str();
}

};

