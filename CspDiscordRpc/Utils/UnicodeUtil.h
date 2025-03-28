#pragma once

/** For operator ""s */
using namespace std::string_literals;

/** const char8_t -> std::string */
std::string operator"" _s(const char8_t* value, size_t size);

/** To make std::cout support std::u8string with << operator */
std::ostream& operator<<(std::ostream& os, const std::u8string& str);

namespace util
{

const char* Char8ToChar(const char8_t* char8);

std::string U8StringToString(std::u8string const& input);

std::u8string StringToU8String(std::string const& input);

} // namespace util