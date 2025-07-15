#pragma once

namespace util
{

HWND GetWindowHandle(winrt::Microsoft::UI::Xaml::Window const& window);

HWND GetWindowHandleByName(const std::string& windowName);

void SetWindowSize(winrt::Microsoft::UI::Xaml::Window const& window, int const& width, int const& height);

void AddTrayIcon(const std::wstring& trayIconTitle, HWND hwnd, NOTIFYICONDATA nid, const UINT& callbackMessage);

void RemoveTrayIcon(NOTIFYICONDATA nid);

} // namespace util