#pragma once

class Config : public TSingletonMutex<Config>
{
public:
	void Update();
	void WriteToJson();
public:

	// bool
	bool DebugMode;
	bool DiscordRPC;
	bool MinimizeToSystemTray;
	bool DoNotShowAgain_ClickingCloseButton;

	// std::string
	std::string CacheDataPath;
	std::string SmallImageSource;
	std::string SmallImageText;

	// int (Enum)
	int RpcTextLanguage;
private:
	const std::wstring m_relativePath = L"Config.json";
};
