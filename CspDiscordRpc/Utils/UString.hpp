#pragma once

// STL
#include <vector>
#include <locale> // for std::use_facet and std::ctype

// Windows API
#ifdef _WIN32
    #include <Windows.h>
#endif

using ASCICHAR  =   char;
using WIDECHAR  =   wchar_t;
using CHAR32    =   char32_t;

#ifdef _WIN32
    using UNI_CHAR = WIDECHAR;
    #define UTEXT(str) L##str  // Windows: L"string"
#else
    using UNI_CHAR = CHAR32;
    #define UTEXT(str) U##str  // Linux/macOS: U"string"
#endif

//#ifdef _WIN64
//    using SIZE_T    =   unsigned __int64; // Declares unsigned 64-bit integer
//    using SSIZE_T   =   __int64;
//#else
//    using SIZE_T    =   unsigned long
//    using SSIZE_T   =   long;
//#endif


class UString
{

public: // Constructor

    /** Default constructor */
    UString()
    {
    }

    /** Constructor from ( UNI_CHAR* ) */
    UString(const UNI_CHAR* str)
    {
        size_t Length = std::char_traits<UNI_CHAR>::length(str);
        M_Data.assign(str, str + Length + 1);  // Copy string, include null character
    }

public:

    /** Get C-Style string */
    const UNI_CHAR* Data() const
    {
        return M_Data.data();
    }

    /** Get string length */
    size_t Length() const
    {
        return M_Data.size() - 1; // Minus null character
    }

    /** Convert to std::string */
    std::string ToString() const
    {
        #ifdef _WIN32
            // Windows: 使用 WideCharToMultiByte 進行轉換
            int requiredSize = WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<LPCWSTR>(M_Data.data()), -1, nullptr, 0, nullptr, nullptr);
            std::string result(requiredSize - 1, '\0');
            WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<LPCWSTR>(M_Data.data()), -1, &result[0], requiredSize, nullptr, nullptr);
            return result;
        #else
            // UTF-32 轉換到 UTF-8
            throw std::runtime_error("Other platforms are not support yet");
        #endif
    }

public: // Operator overloading

    /** 
    * Concat string
    * 串接字串
    */
    UString operator+(const UString& other) const
    {
        UString Result;
        Result.M_Data = this->M_Data;
        Result.M_Data.pop_back(); // 移除原字串的 null character
        Result.M_Data.insert(Result.M_Data.end(), other.M_Data.begin(), other.M_Data.end());
        return Result;
    }

    /**
    * Append a string to the current string (in-place concatenation)
    * 將另一個字串追加到當前字串（原地串接）
    */
    UString& operator+=(const UString& other)
    {
        // 1. 移除當前字串的 \0 （如果存在）
        if (!M_Data.empty())
        {
            M_Data.pop_back();
        }

        // 2. 將另一個字串的內容追加到當前字串
        M_Data.insert(M_Data.end(), other.M_Data.begin(), other.M_Data.end());

        // 3. 返回當前物件的引用（支持鏈式調用，如 a += b += c）
        return *this;
    }

public:

    bool IsEmpty() const
    {   
        return M_Data.size() <= 1;
    }

    /** To upper-case */
    UString ToUpper() const
    {
        UString result = *this;

        #ifdef _WIN32
            if (!result.M_Data.empty())
            {
                CharUpperBuffW(reinterpret_cast<LPWSTR>(result.M_Data.data()), result.M_Data.size() - 1);
            }
        #else
            std::locale loc("");
            auto& facet = std::use_facet<std::ctype<UNI_CHAR>>(loc);

            for (auto& ch : result.M_Data)
            {
                // Avoid to convert null character
                if (ch != 0) 
                {
                    ch = facet.toupper(ch);
                }
            }
        #endif

        return result;
    }

    /** To lower-case */
    UString ToLower() const
    {
        UString result = *this;

        #ifdef _WIN32
            if (!result.M_Data.empty())
            {
                CharLowerBuffW(reinterpret_cast<LPWSTR>(result.M_Data.data()), result.M_Data.size() - 1);
            }
        #else
            std::locale loc("");
            auto& facet = std::use_facet<std::ctype<UNI_CHAR>>(loc);

            for (auto& ch : result.M_Data)
            {
                // avoid to convert null character
                if (ch != 0) 
                {
                    ch = facet.tolower(ch);
                }
            }
        #endif

        return result;
    }

    
    bool StartsWith(const UString& prefix) const
    {
        // 檢查前綴長度是否大於字串本身
        if (prefix.Length() > this->Length())
        {
            return false;
        }

        // 比較前綴字元
        for (size_t i = 0; i < prefix.Length(); ++i)
        {
            if (M_Data[i] != prefix.M_Data[i])
            {
                return false;
            }
        }

        return true;
    }

    /** Check UNI_CHAR is whitespace or not */
    bool IsWhitespace(UNI_CHAR ch) const
    {
        // Unicode 空白字符檢查
        return ch == ' '   // 標準空格
            || ch == '\t' // 製表符
            || ch == '\n' // LF (Line Feed) 換行符
            || ch == '\r' // CR (Carriage Return)
            || ch == 0x3000 // 全形空格（CJK）
            || ch == 0x00A0 // 不間斷空格
            || (ch >= 0x2000 && ch <= 0x200B); // 各種寬度的空白
    }

    /** Removes whitespace from the beginning of string */
    UString TrimStart() const
    {
        UString result = *this;

        while (!result.M_Data.empty() && IsWhitespace(result.M_Data[0]) && result.M_Data[0] != '\0')
        {
            result.M_Data.erase(result.M_Data.begin());
        }

        return result;
    }

    /** Removes whitespace from the end of string */
    UString TrimEnd() const
    {
        UString result = *this;

        while (!result.M_Data.empty())
        {
            size_t lastIndex = result.M_Data.size() - 1;

            // 檢查倒數第二個字符（假設最後一個是 \0）
            if (lastIndex >= 1)  // 確保至少有 2 個字符（1 個字符 + \0）
            {
                UNI_CHAR& prevChar = result.M_Data[lastIndex - 1];

                if (IsWhitespace(prevChar) && prevChar != '\0')
                {
                    // 移除倒數第二個字符（保留 \0）
                    result.M_Data.erase(result.M_Data.end() - 2);
                }
                else
                {
                    break; // 遇到 非空白字符 或 \0 時停止
                }
            }
            else
            {
                break; // 只有 \0 或 空字符串 時停止
            }
        }

        return result;
    }

    /** Removes whitespace from both sides of string */
    UString Trim() const
    {
        return TrimStart().TrimEnd();
    }

private:

    /** Store character data */
    std::vector<UNI_CHAR> M_Data;

};

/** 為了允許重新定義，所以加上 inline */
inline std::ostream& operator<<(std::ostream& os, const UString& str)
{
    os << str.ToString();
    return os;
}

/** 為了允許重新定義，所以加上 inline */
inline std::wostream& operator<<(std::wostream& os, const UString& str)
{
    os << str.Data();
    return os;
}