#pragma once

class ConsoleManager : public TSingletonMutex<ConsoleManager>
{
private:
	bool m_isConsoleExist = false;
public:
	/*
	* 創建一個控制台，必須在任何一個 `std::cout` 輸出之前使用`ConsoleManager::BlockStdIO()`
	* @param CodePage - 頁碼
	*/
	void Create(std::wstring const& consoleName = L"Console", UINT const& codePage = CP_UTF8);

	void Destroy();

	void BlockStdIO();

	void FreeStdIO();
public:
	inline bool IsConsoleExist() { return m_isConsoleExist; }
private:
	void RedirectIOToConsole();
};

