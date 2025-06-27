#include "pch.h"
#include "TrayDialogPage.xaml.h"
#if __has_include("TrayDialogPage.g.cpp")
#include "TrayDialogPage.g.cpp"
#endif

namespace winrt
{
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::Foundation;
}


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CspDiscordRpc::implementation
{

int32_t TrayDialogPage::MyProperty()
{
    throw hresult_not_implemented();
}

void TrayDialogPage::MyProperty(int32_t /* value */)
{
    throw hresult_not_implemented();
}

void TrayDialogPage::RadioButton_MinimizeToSystemTray_Checked(winrt::IInspectable const& sender, winrt::RoutedEventArgs const& e)
{
	Config* config = Config::GetInstance();
	config->MinimizeToSystemTray = true;
	config->WriteToJson();
}

void TrayDialogPage::RadioButton_Exit_Checked(winrt::IInspectable const& sender, winrt::RoutedEventArgs const& e)
{
	Config* config = Config::GetInstance();
	config->MinimizeToSystemTray = false;
	config->WriteToJson();
}

void TrayDialogPage::CheckBox_DoNotShowAgain_Checked(winrt::IInspectable const& sender, winrt::RoutedEventArgs const& e)
{
	Config* config = Config::GetInstance();
	config->DoNotShowAgain_ClickingCloseButton = true;
	config->WriteToJson();
}

void TrayDialogPage::CheckBox_DoNotShowAgain_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	Config* config = Config::GetInstance();
	config->DoNotShowAgain_ClickingCloseButton = false;
	config->WriteToJson();
}


} // namespace winrt::CspDiscordRpc::implementation