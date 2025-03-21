#pragma once

#include "ChooseCspWorkDialogPage.g.h"

namespace winrt::CspDiscordRpc::implementation
{
    struct ChooseCspWorkDialogPage : ChooseCspWorkDialogPageT<ChooseCspWorkDialogPage>
    {
    public:

        ChooseCspWorkDialogPage();
        void InitializeComponent();

        // CspWorkCacheData
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::CspDiscordRpc::CspWorkCacheData> CspWorkCacheData() const;

        // SelectedCspWorkCacheData
		winrt::CspDiscordRpc::CspWorkCacheData SelectedCspWorkCacheData() const;
        void SelectedCspWorkCacheData(winrt::CspDiscordRpc::CspWorkCacheData const& value);

    private:

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::CspDiscordRpc::CspWorkCacheData> m_cspWorkCacheData;
		winrt::CspDiscordRpc::CspWorkCacheData m_selectedCspWorkCacheData;

    public:
        void GridView_ClipFileItem_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::ItemClickEventArgs const& e);
    };
}

namespace winrt::CspDiscordRpc::factory_implementation
{
    struct ChooseCspWorkDialogPage : ChooseCspWorkDialogPageT<ChooseCspWorkDialogPage, implementation::ChooseCspWorkDialogPage>
    {
    };
}
