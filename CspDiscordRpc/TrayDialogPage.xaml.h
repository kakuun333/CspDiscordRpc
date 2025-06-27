#pragma once

#include "TrayDialogPage.g.h"

namespace winrt::CspDiscordRpc::implementation
{
    struct TrayDialogPage : TrayDialogPageT<TrayDialogPage>
    {
        TrayDialogPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void RadioButton_MinimizeToSystemTray_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RadioButton_Exit_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CheckBox_DoNotShowAgain_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CheckBox_DoNotShowAgain_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::CspDiscordRpc::factory_implementation
{
    struct TrayDialogPage : TrayDialogPageT<TrayDialogPage, implementation::TrayDialogPage>
    {
    };
}
