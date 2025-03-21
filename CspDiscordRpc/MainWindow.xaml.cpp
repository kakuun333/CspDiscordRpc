#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif


namespace winrt
{
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;
}

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CspDiscordRpc::implementation
{

MainWindow::MainWindow()
{
    // Xaml objects should not call InitializeComponent during construction.
    // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
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

	const winrt::hstring VERSION = L"1.0.0";
    // 添加版本編號
    TitleBarTextBlock().Text(winrt::format(L"{} v{}", TitleBarTextBlock().Text(), VERSION));
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
