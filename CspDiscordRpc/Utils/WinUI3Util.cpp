#include "pch.h"
#include "WinUI3Util.h"

namespace winrt
{
using namespace Microsoft::UI;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Windowing;
using namespace Windows::Graphics;
}



namespace util
{

HWND GetWindowHandle(winrt::Microsoft::UI::Xaml::Window const& window)
{
    auto windowNative{ window.try_as<::IWindowNative>() };
    HWND hWnd{ 0 };
    windowNative->get_WindowHandle(&hWnd);
    return hWnd;
}

HWND GetWindowHandleByName(const std::string& windowName)
{
    // 使用 Win32 API 查找窗口
    HWND hWnd = FindWindow(NULL, util::StringToWString(windowName).c_str());

    if (hWnd == NULL)
    {
        std::cout << UString(UTEXT("未找到 CaptureWindow\n"));
    }

    return hWnd;
}

void AddTrayIcon(const std::wstring& trayIconTitle, HWND hwnd, NOTIFYICONDATA nid, const UINT& callbackMessage)
{
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    nid.uCallbackMessage = callbackMessage;

    HICON hIcon = static_cast<HICON>(LoadImageW(
        nullptr,
        L"Assets/CspDiscordRpc.ico",  // 跟執行檔同目錄
        IMAGE_ICON,
        0, 0,
        LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED
    ));

    if (hIcon)
    {
        nid.hIcon = hIcon;
    }
    else
    {
		nid.hIcon = LoadIcon(nullptr, IDI_APPLICATION); // 如果載入失敗，使用預設圖示
    }

    wcscpy_s(nid.szTip, trayIconTitle.c_str());

    Shell_NotifyIcon(NIM_ADD, &nid);
}

void RemoveTrayIcon(NOTIFYICONDATA nid)
{
    Shell_NotifyIcon(NIM_DELETE, &nid);
}

} // namespace util