#pragma once

#include "HomePage.g.h"

namespace winrt::CspDiscordRpc::implementation
{
    struct HomePage : HomePageT<HomePage>
    {

    public:
        HomePage();
        void InitializeComponent();

        // State
        winrt::hstring State();
		void State(winrt::hstring const& value);

        // Details
        winrt::hstring Details();
        void Details(winrt::hstring const& value);

        // LargeImageText
        winrt::hstring LargeImageText();
        void LargeImageText(winrt::hstring const& value);

        // SmallImageSource
        winrt::hstring SmallImageSource();

		// SmallImageText
        winrt::hstring SmallImageText();

    private:

        std::vector<std::filesystem::path> GetCspWorkCachePaths();
		winrt::CspDiscordRpc::CspWorkCacheData GetCspWorkCacheData(const std::filesystem::path& cspWorkCachePath);
		winrt::hstring GetRpcFormatText(const ERpcTextLanguage& rpcTextLanguage, const ERpcTextType& rpcTextType);

    private: // static variable

        static inline const std::filesystem::path CSP_WORKS_CACHE_ROOT_PATH = (util::GetAppDataPath() / "CELSYSUserData/CELSYS/CLIPStudioCommon/Document");

    private:

        winrt::hstring m_state;
        winrt::hstring m_details;
        winrt::hstring m_largeImageText;
		winrt::hstring m_smallImageSource;
		winrt::hstring m_smallImageText;

        winrt::Microsoft::UI::Xaml::Controls::ContentDialog m_chooseCspWorkContentDialog{};
        CspDiscordRpc::ChooseCspWorkDialogPage m_chooseCspWorkDialogPage{};

    public:
        void DiscordRpcToggleSwitch_Toggled(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        winrt::Windows::Foundation::IAsyncAction Button_ChooseCspWork_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void TextBox_SmallImageSource_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void TextBox_SmallImageText_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void ComboBox_RpcTextLanguage_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        winrt::Windows::Foundation::IAsyncAction Button_UpdateRpc_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::CspDiscordRpc::factory_implementation
{
    struct HomePage : HomePageT<HomePage, implementation::HomePage>
    {
    };
}
