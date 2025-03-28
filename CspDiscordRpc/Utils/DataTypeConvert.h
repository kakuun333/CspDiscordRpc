#pragma once

namespace util
{

std::wstring MultiByteToWString(const std::string& str);

std::wstring StringToWString(const std::string& input);

std::string WStringToString(const std::wstring& wstr);

} // namespace util