#pragma once

namespace util
{

const char* Char8ToChar(const char8_t* char8);

std::string U8StringToString(std::u8string const& input);

std::u8string StringToU8String(std::string const& input);

std::wstring MultiByteToWString(const std::string& str);

std::wstring StringToWString(const std::string& input);

std::string WStringToString(const std::wstring& wstr);

} // namespace util