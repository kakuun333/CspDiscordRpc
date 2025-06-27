#pragma once

#include "MainWindow.g.h"

namespace winrt::CspDiscordRpc::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        void InitializeComponent();

        winrt::Windows::Foundation::IAsyncAction ShowTrayDialog();

        void MainNavigationView_ItemInvoked(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args);
    };
}

namespace winrt::CspDiscordRpc::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
