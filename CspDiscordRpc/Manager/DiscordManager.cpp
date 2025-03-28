#include "pch.h"

#ifdef _DISCORD_GAME_SDK_H_ // If Discord Game SDK is included

#include "DiscordManager.h"

void DiscordManager::CreateCore(const discord::ClientId& clientId)
{
	if (this->HasCore()) return;

	discord::Core* core{};
	discord::Result createResult = discord::Core::Create(clientId, DiscordCreateFlags_NoRequireDiscord, &core);
	m_core.reset(core); // Assign the created discord::Core* to m_core

	if (!m_core)
	{
		std::cout << "Failed to instantiate discord core!" << static_cast<int>(createResult) << std::endl;
		return;
	}

	std::cout << "DiscordResult: " << this->ResultToString(createResult) << std::endl;

	core->UserManager().OnCurrentUserUpdate.Connect([this]()
	{
		m_core->UserManager().GetCurrentUser(&m_currentUser);

		std::cout << "Current user updated: " << m_currentUser.GetUsername() << std::endl;

		m_core->UserManager().GetUser(m_currentUser.GetId(), [this](discord::Result result, discord::User const& user)
		{
			std::cout << "DiscordResult: " << this->ResultToString(result) << std::endl;
		});
	});

	m_stopActivityEvent.SetHandler([this]()
	{
		this->DestroyCore();
	});

	// Set start time
	m_startTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	m_callbackStopped = false;
	std::thread([this]()
	{
		do
		{
			m_core->RunCallbacks();
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		} while (!m_callbackStopped);
		m_stopActivityEvent.Notify();

	}).detach();
}

void DiscordManager::UpdateActivity(const std::string& state, const std::string& details,
									const std::string& largeImageSource, const std::string& largeImageText,
									const std::string& smallImageSource, const std::string& smallImageText, discord::ActivityType activityType/* = discord::ActivityType::Playing*/)
{
	if (!this->HasCore()) return;

	discord::Activity activity{};

	activity.SetState(state.c_str());

	// Details
	activity.SetDetails(details.c_str());

	// LargeImage
	activity.GetAssets().SetLargeImage(largeImageSource.c_str());
	activity.GetAssets().SetLargeText(largeImageText.c_str());

	// SmallImage
	activity.GetAssets().SetSmallImage(smallImageSource.c_str());
	activity.GetAssets().SetSmallText(smallImageText.c_str());

	// Timestamp
	// milisecond unix timestamp -> second unix timestamp
	
	activity.GetTimestamps().SetStart(m_startTime);

	// ActivityType
	activity.SetType(discord::ActivityType::Playing);

	m_core->ActivityManager().UpdateActivity(activity, [this](discord::Result result)
	{
		std::cout << "DiscordResult: " << this->ResultToString(result) << std::endl;
	});

}

void DiscordManager::StopActivity()
{
	m_core->ActivityManager().ClearActivity([this](discord::Result result)
	{
		std::cout << "DiscordResult: " << this->ResultToString(result) << std::endl;
		m_callbackStopped = true;
	});
}

bool DiscordManager::HasCore()
{
	return m_core.get() != nullptr ? true : false;
}

void DiscordManager::DestroyCore()
{
	if (!this->HasCore()) return;

	m_core->~Core();
	m_core.reset(nullptr); // Release and delete the owned discord::Core*
}

std::string DiscordManager::ResultToString(const discord::Result& result)
{
	switch (result) 
	{
		case discord::Result::Ok: return "Ok";
		case discord::Result::ServiceUnavailable: return "ServiceUnavailable";
		case discord::Result::InvalidVersion: return "InvalidVersion";
		case discord::Result::LockFailed: return "LockFailed";
		case discord::Result::InternalError: return "InternalError";
		case discord::Result::InvalidPayload: return "InvalidPayload";
		case discord::Result::InvalidCommand: return "InvalidCommand";
		case discord::Result::InvalidPermissions: return "InvalidPermissions";
		case discord::Result::NotFetched: return "NotFetched";
		case discord::Result::NotFound: return "NotFound";
		case discord::Result::Conflict: return "Conflict";
		case discord::Result::InvalidSecret: return "InvalidSecret";
		case discord::Result::InvalidJoinSecret: return "InvalidJoinSecret";
		case discord::Result::NoEligibleActivity: return "NoEligibleActivity";
		case discord::Result::InvalidInvite: return "InvalidInvite";
		case discord::Result::NotAuthenticated: return "NotAuthenticated";
		case discord::Result::InvalidAccessToken: return "InvalidAccessToken";
		case discord::Result::ApplicationMismatch: return "ApplicationMismatch";
		case discord::Result::InvalidDataUrl: return "InvalidDataUrl";
		case discord::Result::InvalidBase64: return "InvalidBase64";
		case discord::Result::NotFiltered: return "NotFiltered";
		case discord::Result::LobbyFull: return "LobbyFull";
		case discord::Result::InvalidLobbySecret: return "InvalidLobbySecret";
		case discord::Result::InvalidFilename: return "InvalidFilename";
		case discord::Result::InvalidFileSize: return "InvalidFileSize";
		case discord::Result::InvalidEntitlement: return "InvalidEntitlement";
		case discord::Result::NotInstalled: return "NotInstalled";
		case discord::Result::NotRunning: return "NotRunning";
		case discord::Result::InsufficientBuffer: return "InsufficientBuffer";
		case discord::Result::PurchaseCanceled: return "PurchaseCanceled";
		case discord::Result::InvalidGuild: return "InvalidGuild";
		case discord::Result::InvalidEvent: return "InvalidEvent";
		case discord::Result::InvalidChannel: return "InvalidChannel";
		case discord::Result::InvalidOrigin: return "InvalidOrigin";
		case discord::Result::RateLimited: return "RateLimited";
		case discord::Result::OAuth2Error: return "OAuth2Error";
		case discord::Result::SelectChannelTimeout: return "SelectChannelTimeout";
		case discord::Result::GetGuildTimeout: return "GetGuildTimeout";
		case discord::Result::SelectVoiceForceRequired: return "SelectVoiceForceRequired";
		case discord::Result::CaptureShortcutAlreadyListening: return "CaptureShortcutAlreadyListening";
		case discord::Result::UnauthorizedForAchievement: return "UnauthorizedForAchievement";
		case discord::Result::InvalidGiftCode: return "InvalidGiftCode";
		case discord::Result::PurchaseError: return "PurchaseError";
		case discord::Result::TransactionAborted: return "TransactionAborted";
		default: return "UnknownResult";
	}
}

#endif _DISCORD_GAME_SDK_H_ // If Discord Game SDK is included