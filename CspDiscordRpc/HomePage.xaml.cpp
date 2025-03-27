#include "pch.h"
#include "HomePage.xaml.h"
#if __has_include("HomePage.g.cpp")
#include "HomePage.g.cpp"
#endif

namespace winrt
{
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel::Resources;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Navigation;
}

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CspDiscordRpc::implementation
{

HomePage::HomePage()
{
	// Xaml objects should not call InitializeComponent during construction.
	// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
	this->NavigationCacheMode(winrt::NavigationCacheMode::Required); // 快取這個 Page，防止重新載入（必須在建構函式中設定）。
}

void HomePage::InitializeComponent()
{
    // Call base InitializeComponent() to register with the Xaml runtime
    HomePageT::InitializeComponent();
    // Can now access Xaml properties

    Config* config = Config::GetInstance();

    // RpcTextLanguage
    ComboBox_RpcTextLanguage().SelectedIndex(config->RpcTextLanguage);

    // 初始化 SmallImageSource
	m_smallImageSource = winrt::to_hstring(config->SmallImageSource);
	TextBox_SmallImageSource().Text(m_smallImageSource);

    // 初始化 SmallImageText
	m_smallImageText = winrt::to_hstring(config->SmallImageText);
	TextBox_SmallImageText().Text(m_smallImageText);

    // 初始化 DiscordRPC
	DiscordRpcToggleSwitch().IsOn(config->DiscordRPC);

    // 初始化 ChooseCspWork
	winrt::CspDiscordRpc::CspWorkCacheData cspWorkCacheData = GetCspWorkCacheData(std::filesystem::path{ config->CacheDataPath });
    m_chooseCspWorkDialogPage.SelectedCspWorkCacheData(cspWorkCacheData);

    this->SetRpcProperties(cspWorkCacheData);
    TextBlock_ChoosedCspWork().Text(cspWorkCacheData.Name());
}

winrt::hstring HomePage::State()
{
    return m_state;
}

void HomePage::State(winrt::hstring const& value)
{
    m_state = (value.empty()) ? L"" : std::vformat(GetRpcFormatText(static_cast<ERpcTextLanguage>(Config::GetInstance()->RpcTextLanguage), ERpcTextType::State).c_str(), std::make_wformat_args(value));
}

winrt::hstring HomePage::Details()
{
    return m_details;
}

void HomePage::Details(winrt::hstring const& value)
{
    m_details = (value.empty()) ? L"" : std::vformat(GetRpcFormatText(static_cast<ERpcTextLanguage>(Config::GetInstance()->RpcTextLanguage), ERpcTextType::Details).c_str(), std::make_wformat_args(value));
}

winrt::hstring HomePage::LargeImageText()
{
	return m_largeImageText;
}

void HomePage::LargeImageText(winrt::hstring const& value)
{
    m_largeImageText = (value.empty()) ? L"" : std::vformat(GetRpcFormatText(static_cast<ERpcTextLanguage>(Config::GetInstance()->RpcTextLanguage), ERpcTextType::LargeImageText).c_str(), std::make_wformat_args(value));
}

winrt::hstring HomePage::SmallImageSource()
{
	return m_smallImageSource;
}

winrt::hstring HomePage::SmallImageText()
{
    return m_smallImageText;
}

void HomePage::DiscordRpcToggleSwitch_Toggled(winrt::IInspectable const& sender, winrt::RoutedEventArgs const& e)
{
    DiscordManager* discordManager = DiscordManager::GetInstance();

    auto toggleSwitch = sender.as<winrt::ToggleSwitch>();

    if (toggleSwitch.IsOn())
    {
        discordManager->CreateCore();
        discordManager->UpdateActivity(
            winrt::to_string(this->State()),
            winrt::to_string(this->Details()),
            winrt::to_string(this->LargeImageText()),
            winrt::to_string(this->SmallImageSource()),
            winrt::to_string(this->SmallImageText())
        );
    }
    else
    {
        discordManager->StopActivity();
    }
}

std::vector<std::filesystem::path> HomePage::GetCspWorkCachePaths()
{
    std::vector<std::filesystem::path> cspWorkCachePaths;

    for (const auto& entry : std::filesystem::directory_iterator(CSP_WORKS_CACHE_ROOT_PATH))
    {
        // 忽略 檔案
        if (!entry.is_directory()) continue;

        // 忽略 Update 資料夾
        if (entry.path().filename() == "Update") continue;

        //std::cout << util::FindFirstFolderWithFile(entry).relative_path().string() << std::endl;
        cspWorkCachePaths.push_back(util::FindFirstFolderWithFile(entry));
    }

    return cspWorkCachePaths;
}

winrt::CspDiscordRpc::CspWorkCacheData HomePage::GetCspWorkCacheData(const std::filesystem::path& cspWorkCachePath)
{
    if (cspWorkCachePath.empty())
    {
        std::cout << "HomePage::GetCspWorkCacheData: cspWorkCachePath.empty()" << std::endl;
        return {};
    }

    FileManager* fileManager = FileManager::GetInstance();

    std::string catalogXmlContent = fileManager->ReadFile(cspWorkCachePath / "catalog.xml");

    // 使用 pugixml 解析 XML
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(catalogXmlContent.c_str());

    if (result)
    {
        pugi::xpath_node workNameNode = doc.select_node("/archive/catalog/name");
        pugi::xpath_node cspVersionNode = doc.select_node("/archive/catalog/groups/group/tool");
        pugi::xpath_node thumbnailPathNode = doc.select_node("/archive/files/file[contains(@mime, \"image/png\")]/path");


		int64_t totalWorkingTime = fileManager->ReadJson(cspWorkCachePath / "workingTime.json")["totalworkingtime"].get<int64_t>();
 
		std::string DHMSTotalWorkingTime = util::ConvertMillisecondsToDHMS(totalWorkingTime);

        return {
            winrt::to_hstring(workNameNode.node().text().as_string()),
            std::filesystem::path{cspWorkCachePath / thumbnailPathNode.node().text().as_string()}.wstring(),
            winrt::to_hstring(cspVersionNode.node().attribute("version").as_string()),
            cspWorkCachePath.wstring(),
            winrt::to_hstring(DHMSTotalWorkingTime)
		};
    }
    else
    {
        std::cout << "XML parsed with errors, attr value: [" << doc.child("catalog").attribute("attr").value() << "]" << std::endl;
        std::cout << "Error description: " << result.description() << std::endl;
        std::cout << "Error offset: " << result.offset << " (error at [..." << (catalogXmlContent.c_str() + result.offset) << "]" << std::endl;
    }

    return {};
}

winrt::hstring HomePage::GetRpcFormatText(const ERpcTextLanguage& rpcTextLanguage, const ERpcTextType& rpcTextType)
{
    switch (rpcTextType)
    {
        case ERpcTextType::State:
        {
            switch (rpcTextLanguage)
            {
                case ERpcTextLanguage::Japanese: return L"\"{}\" で作業している";
                case ERpcTextLanguage::TraditionalChinese: return L"於 \"{}\" 中作業";
                case ERpcTextLanguage::SimplifiedChinese: return L"于 \"{}\" 中作业";
                default: return L"Working on \"{}\"";
            }
        }
        case ERpcTextType::Details:
        {
            switch (rpcTextLanguage)
            {
                case ERpcTextLanguage::Japanese: return L"総作業時間: {}";
                case ERpcTextLanguage::TraditionalChinese: return L"總作業時長: {}";
                case ERpcTextLanguage::SimplifiedChinese: return L"总作业时长: {}";
                default: return L"Total working time: {}";
            }
        }
        case ERpcTextType::LargeImageText:
        {
            switch (rpcTextLanguage)
            {
                case ERpcTextLanguage::Japanese: return L"CLIP STUDIO PAINT Ver.{}";
                case ERpcTextLanguage::TraditionalChinese: return L"CLIP STUDIO PAINT Ver.{}";
                case ERpcTextLanguage::SimplifiedChinese: return L"CLIP STUDIO PAINT Ver.{}";
                default: return L"CLIP STUDIO PAINT Ver.{}";
            }
        }
        default: return L"";
    }

}

void HomePage::SetRpcProperties(const winrt::CspDiscordRpc::CspWorkCacheData& cspWorkCacheData/* = winrt::CspDiscordRpc::CspWorkCacheData{}*/)
{
	this->State(cspWorkCacheData.Name());
	this->Details(cspWorkCacheData.TotalWorkingTime());
	this->LargeImageText(cspWorkCacheData.CspVersion());
}

winrt::IAsyncAction HomePage::Button_ChooseCspWork_Click(winrt::IInspectable const& sender, winrt::RoutedEventArgs const& e)
{
    winrt::ResourceLoader resourceLoader = winrt::ResourceLoader::GetForViewIndependentUse();
	Config* config = Config::GetInstance();

    m_chooseCspWorkDialogPage.CspWorkCacheData().Clear();

	for (const auto& path : this->GetCspWorkCachePaths())
	{
		winrt::CspDiscordRpc::CspWorkCacheData cspWorkCacheData = GetCspWorkCacheData(path);

		if (cspWorkCacheData.IsEmpty()) continue;

		m_chooseCspWorkDialogPage.CspWorkCacheData().Append(cspWorkCacheData);
	}

    m_chooseCspWorkContentDialog.XamlRoot(this->XamlRoot());
    m_chooseCspWorkContentDialog.Title(winrt::box_value(resourceLoader.GetString(L"ChooseWork")));
    m_chooseCspWorkContentDialog.PrimaryButtonText(resourceLoader.GetString(L"Choose"));
    m_chooseCspWorkContentDialog.PrimaryButtonClick([this, config](winrt::ContentDialog const& sender, winrt::ContentDialogButtonClickEventArgs const& args)
    {
		// Get selected CspWorkCacheData
        winrt::CspDiscordRpc::CspWorkCacheData selectedCspWorkCacheData = m_chooseCspWorkDialogPage.SelectedCspWorkCacheData();

		// Set member variables
        this->SetRpcProperties(selectedCspWorkCacheData);
  //      m_state = winrt::format(GetRpcFormatText(static_cast<ERpcTextLanguage>(config->RpcTextLanguage), ERpcTextType::State), selectedCspWorkCacheData.Name());
		//m_details = winrt::format(GetRpcFormatText(static_cast<ERpcTextLanguage>(config->RpcTextLanguage), ERpcTextType::Details), selectedCspWorkCacheData.TotalWorkingTime());
		//m_largeImageText = winrt::format(L"CLIP STUDIO PAINT Ver.{}", selectedCspWorkCacheData.CspVersion());

        // Config
		config->CacheDataPath = winrt::to_string(selectedCspWorkCacheData.CacheDataPath());
		config->WriteToJson();

        // Update UI
        TextBlock_ChoosedCspWork().Text(selectedCspWorkCacheData.Name());

        // Debug
        std::cout << "Name: " << winrt::to_string(selectedCspWorkCacheData.Name()) << '\n';
        std::cout << "ThumbnailPath: " << winrt::to_string(selectedCspWorkCacheData.ThumbnailPath()) << '\n';
        std::cout << "CspVersion: " << winrt::to_string(selectedCspWorkCacheData.CspVersion()) << '\n';
        std::cout << "CacheDataPath: " << winrt::to_string(selectedCspWorkCacheData.CacheDataPath()) << '\n';
	});
    
    m_chooseCspWorkContentDialog.CloseButtonText(resourceLoader.GetString(L"Close"));

    m_chooseCspWorkContentDialog.Content(m_chooseCspWorkDialogPage);

    co_await m_chooseCspWorkContentDialog.ShowAsync();
}

void HomePage::TextBox_SmallImageSource_TextChanged(winrt::IInspectable const& sender, winrt::TextChangedEventArgs const& e)
{
    winrt::hstring Text = sender.as<winrt::TextBox>().Text();
    m_smallImageSource = Text;

	Config* config = Config::GetInstance();
	config->SmallImageSource = winrt::to_string(Text);
	config->WriteToJson();
}

void HomePage::TextBox_SmallImageText_TextChanged(winrt::IInspectable const& sender, winrt::TextChangedEventArgs const& e)
{
    winrt::hstring Text = sender.as<winrt::TextBox>().Text();
    m_smallImageText = Text;

    Config* config = Config::GetInstance();
	config->SmallImageText = winrt::to_string(Text);
    config->WriteToJson();
}

void HomePage::ComboBox_RpcTextLanguage_SelectionChanged(winrt::IInspectable const& sender, winrt::SelectionChangedEventArgs const& e)
{
    Config* config = Config::GetInstance();

    int selectedItemIndex = sender.as<winrt::ComboBox>().SelectedIndex();

    config->RpcTextLanguage = selectedItemIndex;
    config->WriteToJson();

    // Update Properties
    winrt::CspDiscordRpc::CspWorkCacheData selectedCspWorkCacheData = m_chooseCspWorkDialogPage.SelectedCspWorkCacheData();
    this->SetRpcProperties(selectedCspWorkCacheData);
}


winrt::IAsyncAction HomePage::Button_UpdateRpc_Click(winrt::IInspectable const& sender, winrt::RoutedEventArgs const& e)
{
    if (!DiscordRpcToggleSwitch().IsOn())
    {
        winrt::ContentDialog contentDialog{};
        contentDialog.XamlRoot(this->XamlRoot());
        contentDialog.Title(winrt::box_value(L""));
        contentDialog.PrimaryButtonText(L"OK");

        winrt::CspDiscordRpc::TurnOnDiscordRpcDialogPage dialogContent{};
        contentDialog.Content(dialogContent);

        co_await contentDialog.ShowAsync();
        co_return;
    }

    DiscordManager* discordManager = DiscordManager::GetInstance();
    if (!discordManager->IsCoreExist())
    {
		std::cout << "Discord Core not exist!" << std::endl;
        co_return;
    }

    discordManager->UpdateActivity(
        winrt::to_string(this->State()),
        winrt::to_string(this->Details()),
        winrt::to_string(this->LargeImageText()),
        winrt::to_string(this->SmallImageSource()),
        winrt::to_string(this->SmallImageText())
    );

}


} // namespace winrt::CspDiscordRpc::implementation


