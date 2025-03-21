#pragma once

#include "TurnOnDiscordRpcDialogPage.g.h"

namespace winrt::CspDiscordRpc::implementation
{
    struct TurnOnDiscordRpcDialogPage : TurnOnDiscordRpcDialogPageT<TurnOnDiscordRpcDialogPage>
    {
        TurnOnDiscordRpcDialogPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
    };
}

namespace winrt::CspDiscordRpc::factory_implementation
{
    struct TurnOnDiscordRpcDialogPage : TurnOnDiscordRpcDialogPageT<TurnOnDiscordRpcDialogPage, implementation::TurnOnDiscordRpcDialogPage>
    {
    };
}
