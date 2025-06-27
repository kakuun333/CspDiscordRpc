#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

static constexpr UINT WM_TRAYICON = WM_USER + 1;
static constexpr UINT ID_TRAY_EXIT = 1001; // 自定義的系統通知區域圖示訊息
static constexpr UINT ID_TRAY_SHOW = 1002; // 自定義的系統通知區域圖示訊息

namespace winrt
{
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::ApplicationModel::Resources;
}

LRESULT CALLBACK WindowProcHook(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    if (msg == WM_CLOSE)
    {
		Config* config = Config::GetInstance();

        if (config->DoNotShowAgain_ClickingCloseButton)
        {
            if (config->MinimizeToSystemTray)
            {
                // 如果設定為最小化到系統通知區域，則隱藏視窗
                ShowWindow(hwnd, SW_HIDE);
            }
            else
            {
                // 否則關閉應用程式
                PostQuitMessage(0);
            }
        }
        else
        {
            // 把 dwRefData 還原成 MainWindow*
            auto mainWindow = reinterpret_cast<winrt::CspDiscordRpc::implementation::MainWindow*>(dwRefData);

            auto dispatcher = winrt::Microsoft::UI::Dispatching::DispatcherQueue::GetForCurrentThread();
            dispatcher.TryEnqueue([mainWindow]()
            {
                mainWindow->ShowTrayDialog(); // 這裡會自動跑 async coroutine
            });
        }

        return 0; // 表示已處理
    }
    else if (msg == WM_TRAYICON)
    {
        if (LOWORD(lParam) == WM_LBUTTONUP) // 左鍵點擊托盤圖示 -> 顯示視窗
        {
            ShowWindow(hwnd, SW_RESTORE);       // 還原最小化視窗
        }
        else if (LOWORD(lParam) == WM_RBUTTONUP) // 右鍵點擊托盤圖示 -> 顯示選單
        {
            // 建立右鍵選單
            HMENU hMenu = CreatePopupMenu();
            if (hMenu)
            {
                AppendMenuW(hMenu, MF_STRING, ID_TRAY_SHOW, L"Show");
                AppendMenuW(hMenu, MF_STRING, ID_TRAY_EXIT, L"Exit");

                POINT point;
                GetCursorPos(&point); // 取得目前滑鼠位置
                SetForegroundWindow(hwnd); // 修正選單不會自動消失的 bug

                // 顯示右鍵選單
                int cmd = TrackPopupMenu(
                    hMenu,
                    TPM_RETURNCMD | TPM_BOTTOMALIGN | TPM_LEFTALIGN,
                    point.x,
                    point.y,
                    0,
                    hwnd,
                    nullptr
                );

                DestroyMenu(hMenu);

                // 處理選單指令
                switch (cmd)
                {
                    case ID_TRAY_SHOW:
                    {
                        ShowWindow(hwnd, SW_RESTORE);
                        break;
                    }
                    case ID_TRAY_EXIT:
                    {
                        PostQuitMessage(0);
                        break;
                    }
                }
            }
        }
    }

    return DefSubclassProc(hwnd, msg, wParam, lParam);
}


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.
namespace winrt::CspDiscordRpc::implementation
{

MainWindow::MainWindow()
{
    // Xaml objects should not call InitializeComponent during construction.
    // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

    NOTIFYICONDATA nid = {};

    HWND hwnd = util::GetWindowHandle(*this); // 取得 HWND

    // 設定子類別攔截器
    SetWindowSubclass(hwnd, WindowProcHook, 1, reinterpret_cast<DWORD_PTR>(this)/* 把 MainWindow* 傳進去 */);

    util::AddTrayIcon(L"CspDiscordRpc", hwnd, nid, WM_TRAYICON);
}

void MainWindow::InitializeComponent()
{
    // Call base InitializeComponent() to register with the Xaml runtime
    MainWindowT::InitializeComponent();
    // Can now access Xaml properties

    // Hide system title bar.
    ExtendsContentIntoTitleBar(true);

    // MainWindow 初始化時導向 HomePage
    ContentFrame().Navigate(winrt::xaml_typename<winrt::CspDiscordRpc::HomePage>(), nullptr);

	const winrt::hstring VERSION = L"1.1.0";
    // 添加版本編號
    TitleBarTextBlock().Text(winrt::format(L"{} v{}", TitleBarTextBlock().Text(), VERSION));
}

winrt::Windows::Foundation::IAsyncAction MainWindow::ShowTrayDialog()
{
	Config* config = Config::GetInstance();
    winrt::ResourceLoader resourceLoader = winrt::ResourceLoader::GetForViewIndependentUse();

    winrt::ContentDialog dialog{};
    dialog.XamlRoot(this->Content().XamlRoot());
    dialog.Title(winrt::box_value(resourceLoader.GetString(L"ClickingCloseButton")));
    
    dialog.PrimaryButtonText(L"OK");
    dialog.PrimaryButtonClick([this, config](winrt::ContentDialog const& sender, winrt::ContentDialogButtonClickEventArgs const& args)
    {
		if (config->MinimizeToSystemTray)
		{
			// 如果設定為最小化到系統通知區域，則隱藏視窗
			ShowWindow(util::GetWindowHandle(*this), SW_HIDE);
		}
		else
		{
			// 否則關閉應用程式
            PostQuitMessage(0);
		}
    });

    dialog.SecondaryButtonText(resourceLoader.GetString(L"Cancel"));

    winrt::CspDiscordRpc::TrayDialogPage dialogContent{};
    dialog.Content(dialogContent);

    co_await dialog.ShowAsync();
}

void MainWindow::MainNavigationView_ItemInvoked(winrt::NavigationView const& sender, winrt::NavigationViewItemInvokedEventArgs const& args)
{
    winrt::TypeName pageTypeName{ winrt::hstring() }; // 初始化 TypeName

    if (args.InvokedItem() == MainWindowHomeItem().Content())
    {
        pageTypeName = winrt::xaml_typename<winrt::CspDiscordRpc::HomePage>();
    }
    else if (args.IsSettingsInvoked())
    {
        pageTypeName = winrt::xaml_typename<winrt::CspDiscordRpc::SettingsPage>();
    }

    // 檢查當前頁面是否已經是目標頁面
    if (ContentFrame().CurrentSourcePageType().Name != pageTypeName.Name)
    {
        ContentFrame().Navigate(pageTypeName, nullptr);
    }
}


}
