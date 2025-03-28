#include "pch.h"
#include "ConsoleManager.h"

void ConsoleManager::Create(const std::wstring& consoleName/* = L"Console"*/)
{
	if (this->m_hasConsole) return;
	this->m_hasConsole = true;

	// 設置全域 locale 為 UTF-8
	std::locale::global(std::locale("en_US.UTF-8"));

	this->ClearIoState();

	if (!AttachConsole(ATTACH_PARENT_PROCESS))
	{
		AllocConsole();
		SetConsoleTitle(consoleName.c_str());

		// 設置控制台輸出代碼頁為 UTF-8
		SetConsoleOutputCP(CP_UTF8);

		// 啟用 ANSI 編碼的控制台
		SetConsoleCP(CP_UTF8);

		// 重新導向 STDIO 流
		this->RedirectIoToConsole();
	}


	std::cout << "Console was created successfully!" << std::endl;
}

void ConsoleManager::Destroy()
{
	if (!this->m_hasConsole) return;

	// 獲取當前控制台視窗句柄
	HWND consoleWindow = GetConsoleWindow();
	if (consoleWindow != nullptr)
	{
		// 調用 FreeConsole 函式釋放控制台
		FreeConsole();

		// 關閉控制台視窗句柄
		PostMessage(consoleWindow, WM_CLOSE, 0, 0);

		std::locale::global(std::locale("")); // 還原 locale
	}

	this->m_hasConsole = false;
}

bool ConsoleManager::HasConsole()
{
	return m_hasConsole;
}

void ConsoleManager::SetIoState(std::ios_base::iostate state/* = 0*/)
{
	std::cout.setstate(state);
	std::wcout.setstate(state);
}

void ConsoleManager::ClearIoState()
{
	std::cout.clear();
	std::wcout.clear();
}

void ConsoleManager::RedirectIoToConsole()
{
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	freopen_s(&fp, "CONIN$", "r", stdin);
}