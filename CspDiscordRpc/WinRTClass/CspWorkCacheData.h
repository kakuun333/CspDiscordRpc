#pragma once

#include "CspWorkCacheData.g.h"

namespace winrt::CspDiscordRpc::implementation
{

struct CspWorkCacheData : CspWorkCacheDataT<CspWorkCacheData>
{
    CspWorkCacheData() {}
    CspWorkCacheData(winrt::hstring const& Name, winrt::hstring const& ThumbnailPath, winrt::hstring const& CspVersion, winrt::hstring const& CacheDataPath, winrt::hstring const& TotalWorkingTime)
        : m_name(Name)
        , m_thumbnailPath(ThumbnailPath)
        , m_cspVersion(CspVersion)
		, m_cacheDataPath(CacheDataPath)
		, m_totalWorkingTime(TotalWorkingTime)
        {}

    // Name
    winrt::hstring Name() const { return m_name; }

    // ThumbnailPath
    winrt::hstring ThumbnailPath() const { return m_thumbnailPath; }

    // CspVersion
    winrt::hstring CspVersion() const { return m_cspVersion; }

    // CacheDataPath
    winrt::hstring CacheDataPath() const { return m_cacheDataPath; }

    // TotalWorkingTime
    winrt::hstring TotalWorkingTime() const { return m_totalWorkingTime; }

private:

    winrt::hstring m_name;
    winrt::hstring m_thumbnailPath;
    winrt::hstring m_cspVersion;
	winrt::hstring m_cacheDataPath;
    winrt::hstring m_totalWorkingTime;

};

} // namespace winrt::CspDiscordRpc::implementation

namespace winrt::CspDiscordRpc::factory_implementation
{
struct CspWorkCacheData : CspWorkCacheDataT<CspWorkCacheData, implementation::CspWorkCacheData> {};
} // namespace winrt::CspDiscordRpc::factory_implementation
