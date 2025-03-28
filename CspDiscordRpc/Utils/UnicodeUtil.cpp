#include "pch.h"
#include "UnicodeUtil.h"

std::string operator"" _s(const char8_t* value, size_t size)
{
	return std::string(reinterpret_cast<const char*>(value), size);
}

std::ostream& operator<<(std::ostream& os, const std::u8string& str)
{
	os << reinterpret_cast<const char*>(str.data());
	return os;
}

namespace util
{

const char* Char8ToChar(const char8_t* char8)
{
	return reinterpret_cast<const char*>(char8);
}

std::string U8StringToString(std::u8string const& input)
{
	return std::string(reinterpret_cast<const char*>(input.c_str()));
}

std::u8string StringToU8String(std::string const& input)
{
	return std::u8string(reinterpret_cast<const char8_t*>(input.c_str()));
}

} // namespace util