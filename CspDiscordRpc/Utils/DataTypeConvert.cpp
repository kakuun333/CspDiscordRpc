#include "pch.h"
#include "DataTypeConvert.h"

namespace util
{

std::wstring MultiByteToWString(const std::string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), NULL, 0);
	std::wstring wstr(size_needed, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), &wstr[0], size_needed);
	return wstr;
}

std::wstring StringToWString(const std::string& input)
{
	int size = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, nullptr, 0);
	std::wstring result(size, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, &result[0], size);
	return result;
}

std::string WStringToString(const std::wstring& wstr)
{
	int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	std::string str(bufferSize - 1, 0);  // 減去一個字元大小來避免空終止符重複
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], bufferSize, nullptr, nullptr);
	return str;
}

} // namespace util