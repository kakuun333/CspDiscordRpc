#include "pch.h"
#include "SettingsPage.xaml.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif

namespace winrt
{
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Navigation;
using namespace Windows::Foundation;
}

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CspDiscordRpc::implementation
{

SettingsPage::SettingsPage()
{
    // Xaml objects should not call InitializeComponent during construction.
    // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    this->NavigationCacheMode(winrt::NavigationCacheMode::Required); // 快取這個 Page，防止重新載入（必須在建構函式中設定）。
}

void SettingsPage::InitializeComponent()
{
    // Call base InitializeComponent() to register with the Xaml runtime
    SettingsPageT::InitializeComponent();
    // Can now access Xaml properties
    Config* config = Config::GetInstance();
    DebugModeToggleSwitch().IsOn(config->DebugMode);
}

void SettingsPage::DebugModeToggleSwitch_Toggled(winrt::IInspectable const& sender, winrt::RoutedEventArgs const& e)
{
    auto toggleSwitch = sender.as<winrt::ToggleSwitch>();

    Config* config = Config::GetInstance();
    ConsoleManager* consoleManager = ConsoleManager::GetInstance();

    if (toggleSwitch.IsOn())
    {
        config->DebugMode = toggleSwitch.IsOn();

        // ConsoleManager
        if (!consoleManager->IsConsoleExist())
        {
            consoleManager->Create();
        }
    }
    else
    {
        config->DebugMode = toggleSwitch.IsOn();

        if (consoleManager->IsConsoleExist())
        {
            consoleManager->Destroy();
        }
    }

    config->WriteToJson();
}

}


