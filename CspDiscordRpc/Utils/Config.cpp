﻿#include "pch.h"
#include "Config.h"

void Config::Update()
{
	json jsonConfig = FileManager::GetInstance()->ReadJson(util::GetLocalFolderPath() / m_relativePath);

	// bool
	DebugMode = jsonConfig[GetVariableName(DebugMode)].empty() ? false : jsonConfig[GetVariableName(DebugMode)].get<bool>();
	DiscordRPC = jsonConfig[GetVariableName(DiscordRPC)].empty() ? false : jsonConfig[GetVariableName(DiscordRPC)].get<bool>();

	// std::string
	CacheDataPath = jsonConfig[GetVariableName(CacheDataPath)].empty() ? "" : jsonConfig[GetVariableName(CacheDataPath)].get<std::string>();
	SmallImageSource = jsonConfig[GetVariableName(SmallImageSource)].empty() ? "" : jsonConfig[GetVariableName(SmallImageSource)].get<std::string>();
	SmallImageText = jsonConfig[GetVariableName(SmallImageText)].empty() ? "" : jsonConfig[GetVariableName(SmallImageText)].get<std::string>();

	// int (Enum)
	RpcTextLanguage = jsonConfig[GetVariableName(RpcTextLanguage)].empty() ? static_cast<int>(ERpcTextLanguage::English) : jsonConfig[GetVariableName(RpcTextLanguage)].get<int>();

	this->WriteToJson();
}

void Config::WriteToJson()
{
	FileManager* fileManager = FileManager::GetInstance();

	json jsonConfig = fileManager->ReadJson(util::GetLocalFolderPath() / m_relativePath);

	// bool
	jsonConfig[GetVariableName(DebugMode)] = DebugMode;
	jsonConfig[GetVariableName(DiscordRPC)] = DiscordRPC;

	// std::string
	jsonConfig[GetVariableName(CacheDataPath)] = CacheDataPath;
	jsonConfig[GetVariableName(SmallImageSource)] = SmallImageSource;
	jsonConfig[GetVariableName(SmallImageText)] = SmallImageText;

	// int (Enum)
	jsonConfig[GetVariableName(RpcTextLanguage)] = RpcTextLanguage;

	std::string jsonString = jsonConfig.dump(2);
	fileManager->WriteFile(std::filesystem::path(util::GetLocalFolderPath() / m_relativePath), jsonString);
}