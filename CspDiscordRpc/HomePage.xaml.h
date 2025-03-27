#pragma once

#include "HomePage.g.h"

namespace winrt::CspDiscordRpc::implementation
{
    struct HomePage : HomePageT<HomePage>
    {

    public:
        HomePage();
        void InitializeComponent();

        // BEGIN - HomePage Property
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
        // END - HomePage Property

    private:

        /** 獲取 CSP 作品快取路徑 */
        std::vector<std::filesystem::path> GetCspWorkCachePaths();

        /**
		* 獲取 CSP 作品快取資料。
		* @param cspWorkCachePath CSP 作品快取路徑
        */
		winrt::CspDiscordRpc::CspWorkCacheData GetCspWorkCacheData(const std::filesystem::path& cspWorkCachePath);

        /**
		* 根據 rpcTextLanguage 和 rpcTextType 獲取 Discord RPC 文字格式，方便後續使用 std::vformat。
		* @param rpcTextLanguage Discord RPC 文字語言
		* @param rpcTextType Discord RPC 文字類型
		* @return Discord RPC 文字格式
        */
		winrt::hstring GetRpcFormatText(const ERpcTextLanguage& rpcTextLanguage, const ERpcTextType& rpcTextType);

        /**
		* 設置 HomePage 的 Discord RPC 屬性。
		* @param cspWorkCacheData CSP 作品快取資料
        */
        void SetRpcProperties(const winrt::CspDiscordRpc::CspWorkCacheData& cspWorkCacheData = winrt::CspDiscordRpc::CspWorkCacheData{});

    private: // Static inline constant

        static inline const std::filesystem::path CSP_WORKS_CACHE_ROOT_PATH = (util::GetAppDataPath() / "CELSYSUserData/CELSYS/CLIPStudioCommon/Document");

    private: // Member variable

        // BEGIN - For Discord RPC (HomePage Property)
        winrt::hstring m_state;
        winrt::hstring m_details;
        winrt::hstring m_largeImageText;
		winrt::hstring m_smallImageSource;
		winrt::hstring m_smallImageText;
        // END - For Discord RPC

        winrt::Microsoft::UI::Xaml::Controls::ContentDialog m_chooseCspWorkContentDialog{};
        CspDiscordRpc::ChooseCspWorkDialogPage m_chooseCspWorkDialogPage{};

	public: // Xmal Event Handler
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
