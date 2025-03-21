#pragma once

namespace util
{

std::filesystem::path GetAppDataPath();

std::filesystem::path GetLocalFolderPath();

std::filesystem::path FindFirstFolderWithFile(const std::filesystem::path& rootPath);
}
