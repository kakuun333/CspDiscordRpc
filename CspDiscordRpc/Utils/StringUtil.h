#pragma once
namespace util
{

/**
* 將毫秒轉換成 dd:hh:mm:ss 格式
* @param milliseconds 毫秒
* @return "dd:hh:mm:ss" 格式
*/
std::string ConvertMillisecondsToDHMS(const int64_t& milliseconds);

};

