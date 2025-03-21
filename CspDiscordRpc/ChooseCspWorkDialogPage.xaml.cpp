#include "pch.h"
#include "ChooseCspWorkDialogPage.xaml.h"
#if __has_include("ChooseCspWorkDialogPage.g.cpp")
#include "ChooseCspWorkDialogPage.g.cpp"
#endif

namespace winrt
{
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
}

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CspDiscordRpc::implementation
{


ChooseCspWorkDialogPage::ChooseCspWorkDialogPage()
{
    // Xaml objects should not call InitializeComponent during construction.
    // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
}

winrt::IObservableVector<winrt::CspDiscordRpc::CspWorkCacheData> ChooseCspWorkDialogPage::CspWorkCacheData() const
{
	return m_cspWorkCacheData;
}

winrt::CspDiscordRpc::CspWorkCacheData ChooseCspWorkDialogPage::SelectedCspWorkCacheData() const
{
    return m_selectedCspWorkCacheData;
}

void ChooseCspWorkDialogPage::SelectedCspWorkCacheData(winrt::CspDiscordRpc::CspWorkCacheData const& value)
{
	m_selectedCspWorkCacheData = value;
}


void ChooseCspWorkDialogPage::InitializeComponent()
{
    // Call base InitializeComponent() to register with the Xaml runtime
    ChooseCspWorkDialogPageT::InitializeComponent();
    // Can now access Xaml properties

    m_cspWorkCacheData = winrt::single_threaded_observable_vector<winrt::CspDiscordRpc::CspWorkCacheData>();
}

void ChooseCspWorkDialogPage::GridView_ClipFileItem_ItemClick(winrt::IInspectable const& sender, winrt::ItemClickEventArgs const& e)
{
    winrt::CspDiscordRpc::CspWorkCacheData clickedItem = e.ClickedItem().as<winrt::CspDiscordRpc::CspWorkCacheData>();
    m_selectedCspWorkCacheData = clickedItem;
}


} // namespace winrt::CspDiscordRpc::implementation

