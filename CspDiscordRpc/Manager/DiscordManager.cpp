#include "pch.h"
#include "DiscordManager.h"

void DiscordManager::CreateCore()
{
	if (this->IsCoreExist()) return;

	discord::Core* core{};
	discord::ClientId clientId{ 0 };

	clientId = CLIENT_ID;

	discord::Result createResult = discord::Core::Create(clientId, DiscordCreateFlags_NoRequireDiscord, &core);
	m_core.reset(core);
	if (!m_core)
	{
		std::cout << "Failed to instantiate discord core! (err " << static_cast<int>(createResult) << ")\n";
		return;
	}

	this->CheckResult(ResultGetter::Core, createResult);

	core->UserManager().OnCurrentUserUpdate.Connect([this]()
	{
		m_core->UserManager().GetCurrentUser(&m_currentUser);

		std::cout << std::format("Current user updated: {}\n", m_currentUser.GetUsername());

		m_core->UserManager().GetUser(m_currentUser.GetId(), [this](discord::Result result, discord::User const& user)
		{
			this->CheckResult(ResultGetter::User, result);
		});
	});

	m_stopActivityEvent.SetHandler([this]()
	{
		this->ClearActivity();
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



void DiscordManager::UpdateActivity(const std::string& state, const std::string& details, const std::string& largeImageText, const std::string& smallImageSource, const std::string& smallImageText, discord::ActivityType activityType/* = discord::ActivityType::Playing*/)
{
	if (!this->IsCoreExist()) return;

	discord::Activity activity{};

	activity.SetState(state.c_str());

	// Details
	activity.SetDetails(details.c_str());

	// LargeImage
	activity.GetAssets().SetLargeImage("https://cdn.discordapp.com/app-icons/1351785436850163733/be7cdabb8b164c564f9e844ba209a2b6.png?size=256");
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
		this->CheckResult(ResultGetter::Activity, result);
	});

}

void DiscordManager::StopActivity()
{
	m_core->ActivityManager().ClearActivity([this](discord::Result result)
	{
		this->CheckResult(ResultGetter::Activity, result);
		m_callbackStopped = true;
	});
}


void DiscordManager::ClearActivity()
{
	if (!this->IsCoreExist()) return;

	m_core->~Core();
	m_core.reset(nullptr); // Release and delete the owned discord::Core*
}

void DiscordManager::CheckResult(ResultGetter const& resultGetter, discord::Result const& result) const
{
	std::string getter;
	std::string discordResult;

	switch (resultGetter)
	{
		case ResultGetter::Core:
		{
			getter = "Core";
			break;
		}
		case ResultGetter::User:
		{
			getter = "User";
			break;
		}
		case ResultGetter::Activity:
		{
			getter = "Activity";
			break;
		}
	}

	switch (result)
	{
		case discord::Result::Ok:
		{
			discordResult = "Ok";
			break;
		}
		case discord::Result::TransactionAborted:
		{
			discordResult = "TransactionAborted";
			break;
		}
		default:
		{
			discordResult = std::to_string(static_cast<int>(result));
		}
	}

	std::cout << std::format("ResultGetter: {}, DiscordResult: {}\n", getter, discordResult);
}

bool DiscordManager::IsCoreExist()
{
	return m_core.get() != nullptr ? true : false;
}