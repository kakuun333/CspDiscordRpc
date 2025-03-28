#include "pch.h"
#include "FileManager.h"


json FileManager::ReadJson(const std::filesystem::path& path)
{
    // 檢查檔案是否存在
    if (std::filesystem::exists(path))
    {
        std::ifstream inputFile(path);

        if (inputFile.is_open())
        {
            json jsonInput;
            inputFile >> jsonInput;
            inputFile.close();
            return jsonInput;
        }
        else
        {
            std::cout << u8"無法開啟檔案："s << path.string() << std::endl;
        }
    }
    else
    {
        std::cout << u8"檔案不存在："s << path.string() << std::endl;
    }

    return {}; // 如果失敗，返回一個空的 JSON 物件
}

[[maybe_unused]] std::string FileManager::ReadFile(const std::filesystem::path& path)
{
    // 檢查檔案是否存在
    if (std::filesystem::exists(path))
    {
        std::ifstream inputFile(path, std::ios::in | std::ios::binary);

        if (inputFile.is_open())
        {
            // 將文件內容讀取為字串
            std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
            inputFile.close();
            return fileContent;
        }
        else
        {
            std::cout << u8"無法開啟檔案："s << path.string() << std::endl;
        }
    }
    else
    {
        std::cout << u8"檔案不存在："s << path.string() << std::endl;
    }

    return {}; // 如果失敗，返回一個空字串
}

void FileManager::WriteFile(const std::filesystem::path& path, std::string_view stringToWrite)
{
    try
    {
        // 如果資料夾不存在，嘗試建立目錄
        if (!std::filesystem::exists(path.parent_path()))
        {
            std::filesystem::create_directories(path.parent_path());
        }

        // 寫入 string 資料
        std::ofstream outputFile(path);
        if (outputFile.is_open())
        {
            outputFile << stringToWrite << std::endl;
            outputFile.close();
            std::cout << u8"成功寫入："s << path.string() << std::endl;
        }
        else
        {
            std::cout << u8"無法開啟檔案進行寫入："s << path.string() << std::endl;
        }
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cout << u8"檔案系統錯誤："s << path.string() << std::endl;
    }
}
