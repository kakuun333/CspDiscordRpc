#include "pch.h"
#include "Path.h"


namespace util
{

std::filesystem::path GetAppDataPath()
{
    wchar_t path[MAX_PATH];
    if (GetEnvironmentVariableW(L"APPDATA", path, MAX_PATH)) // 利用環境變數獲取 %appdata% 的路徑
    {
        return std::filesystem::path{ path };
    }
    return {}; // 取得失敗回傳空 path
}

std::filesystem::path GetLocalFolderPath()
{
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);
    return std::filesystem::path(exePath).parent_path();
}

std::filesystem::path FindFirstFolderWithFile(const std::filesystem::path& rootPath)
{
    try
    {
        if (!std::filesystem::exists(rootPath) || !std::filesystem::is_directory(rootPath))
        {
            std::cerr << util::Char8ToChar(u8"錯誤: 目錄不存在或不是資料夾\n");
            return "";
        }

        for (const auto& entry : std::filesystem::recursive_directory_iterator(rootPath))
        {
			if (!std::filesystem::is_directory(entry)) continue; // 確保是資料夾

            bool hasFile = false;

            // 檢查該資料夾內是否有檔案
            for (const auto& subEntry : std::filesystem::directory_iterator(entry))
            {
                if (std::filesystem::is_regular_file(subEntry)) // 有檔案
                {
                    hasFile = true;
                    break;
                }
            }

            if (hasFile)
            {
                return entry.path(); // 回傳第一個有檔案的資料夾
            }
            
        }
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << util::Char8ToChar(u8"發生錯誤: ") << e.what() << '\n';
    }

    return ""; // 若未找到則回傳空字串
}

}
