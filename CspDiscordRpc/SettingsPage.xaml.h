#pragma once

#include "SettingsPage.g.h"

namespace winrt::CspDiscordRpc::implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage>
    {
        SettingsPage();

        void InitializeComponent();

        void DebugModeToggleSwitch_Toggled(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void TextBox_ClipStudioCommonRootPath_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e);
    };
}

namespace winrt::CspDiscordRpc::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}
