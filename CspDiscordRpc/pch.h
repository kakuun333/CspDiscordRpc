#pragma once
#include <windows.h>
#include <unknwn.h>
#include <restrictederrorinfo.h>
#include <hstring.h>

// Undefine GetCurrentTime macro to prevent
// conflict with Storyboard::GetCurrentTime
#undef GetCurrentTime

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.ApplicationModel.Resources.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.Navigation.h>
#include <winrt/Microsoft.UI.Xaml.Shapes.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winrt/Microsoft.UI.Windowing.h>


// Win32 API / WinUI COM Interop
#include <microsoft.ui.xaml.window.h>

#include <Shellapi.h> // For tray icon
#pragma comment(lib, "Shell32.lib")

#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")

// WIL
#include <wil/cppwinrt_helpers.h>


// STL
#include <iostream>
#include <iomanip>
#include <fstream>
#include <functional>
#include <filesystem>

// Thirdparty from vcpkg
#include <discord-game-sdk/discord.h>
#include <pugixml.hpp>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// Enum
#include <Enum/ERpcTextLanguage.h>
#include <Enum/ERpcTextType.h>

// Utility
#include <Utils/TSingletonMutex.hpp>
#include <Utils/Path.h>
#include <Utils/DataTypeConvert.h>
#include <Utils/Config.h>
#include <Utils/MacroUtil.h>
#include <Utils/StringUtil.h>
#include <Utils/UString.hpp>
#include <Utils/WinUI3Util.h>

// Manager
#include <Manager/DiscordManager.h>
#include <Manager/ConsoleManager.h>
#include <Manager/FileManager.h>


// WinRTClass
#include <WinRTClass/CspWorkCacheData.h>