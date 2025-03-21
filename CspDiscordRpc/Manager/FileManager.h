#pragma once

class FileManager : public TSingletonMutex<FileManager>
{
public:
	/**
	* 讀取 json 檔的內容到 json 物件裡。
	* @param path - 讀取的 json 檔路徑
	* @return json - json 物件
	*/
	json ReadJson(const std::filesystem::path& path);

	[[maybe_unused]] std::string ReadFile(const std::filesystem::path& path);

	/**
	* 如果資料夾不存在，會嘗試建立目錄。
	* @param path - 要寫入的檔案完整路徑
	* @param stringToWrite - 要寫入字串
	*/
	void WriteFile(const std::filesystem::path& path, std::string_view stringToWrite);
};