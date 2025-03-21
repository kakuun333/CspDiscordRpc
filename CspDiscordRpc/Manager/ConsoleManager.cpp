#include "pch.h"
#include "ConsoleManager.h"

void ConsoleManager::Create(std::wstring const& consoleName, UINT const& codePage)
{
	if (this->m_isConsoleExist) return;
	this->m_isConsoleExist = true;

	this->FreeStdIO();

	if (!AttachConsole(ATTACH_PARENT_PROCESS))
	{
		AllocConsole();
		SetConsoleTitle(consoleName.c_str());
	}

	// 設置 CodePage
	SetConsoleOutputCP(codePage);

	// 獲取標準輸出句柄
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// 啟用處理 ANSI 轉譯碼的模式
	DWORD mode;
	GetConsoleMode(hConsole, &mode);
	SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

	// 重定向標準輸出流
	this->RedirectIOToConsole();


	std::cout << util::Char8ToChar(u8"成功創建控制台") << std::endl;
}

void ConsoleManager::Destroy()
{
	if (!this->m_isConsoleExist) return;

	this->BlockStdIO();

	// 獲取當前控制台視窗句柄
	HWND consoleWindow = GetConsoleWindow();
	if (consoleWindow != nullptr)
	{
		// 調用 FreeConsole 函式釋放控制台
		FreeConsole();

		// 關閉控制台視窗句柄
		PostMessage(consoleWindow, WM_CLOSE, 0, 0);
	}

	this->m_isConsoleExist = false;
}

void ConsoleManager::RedirectIOToConsole()
{
	// 重定向 STDIN
	FILE* pCin;
	freopen_s(&pCin, "CONIN$", "r", stdin);

	// 重定向 STDOUT
	FILE* pCout;
	freopen_s(&pCout, "CONOUT$", "w", stdout);

	// 重定向 STDERR
	FILE* pCerr;
	freopen_s(&pCerr, "CONOUT$", "w", stderr);

	// 重新同步 C++ 標準輸入輸出流
	std::ios::sync_with_stdio(true);
}

void ConsoleManager::BlockStdIO()
{
	/*
	* https://stackoverflow.com/questions/30184998/how-to-disable-cout-output-in-the-runtime
	* Putting the stream in fail state will make it silently discard any output, until the failbit is cleared.
	* 
	* 將 stream 狀態設置成 fail 使其拋棄所有輸出
	* 這樣才不會在 Console 創建之前輸出
	* 
	*/
	std::cout.setstate(std::ios_base::failbit);
}

void ConsoleManager::FreeStdIO()
{
	std::cout.clear();
}