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

    // MainWindow ��l�ƮɾɦV HomePage
    ContentFrame().Navigate(winrt::xaml_typename<winrt::CspDiscordRpc::HomePage>(), nullptr);
}

void MainWindow::MainNavigationView_ItemInvoked(winrt::NavigationView const& sender, winrt::NavigationViewItemInvokedEventArgs const& args)
{
    winrt::TypeName pageTypeName{ winrt::hstring() }; // ��l�� TypeName

    if (args.InvokedItem() == MainWindowHomeItem().Content())
    {
        pageTypeName = winrt::xaml_typename<winrt::CspDiscordRpc::HomePage>();
    }
    else if (args.IsSettingsInvoked())
    {
        pageTypeName = winrt::xaml_typename<winrt::CspDiscordRpc::SettingsPage>();
    }

    // �ˬd��e�����O�_�w�g�O�ؼЭ���
    if (ContentFrame().CurrentSourcePageType().Name != pageTypeName.Name)
    {
        ContentFrame().Navigate(pageTypeName, nullptr);
    }
}


}
