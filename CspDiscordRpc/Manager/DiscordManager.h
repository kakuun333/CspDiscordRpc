#pragma once

#ifdef _DISCORD_GAME_SDK_H_ // If Discord Game SDK is included

class DiscordManager : public TSingletonMutex<DiscordManager>
{
private:

	class StopActivityEvent
	{
	public:
		// 定義一個事件處理器的型別
		using HandlerType = std::function<void()>;

		// 註冊事件處理器
		void SetHandler(HandlerType handler)
		{
			m_handler = handler;
		}

		// 觸發事件，通知所有的處理器
		void Notify()
		{
			m_handler();
		}

	private:
		HandlerType m_handler;  // 儲存所有註冊的事件處理器
	};

public:
	/**
	* Create Discord Core
	* @param clientId "Client ID" aka "Application ID"
	*/
	void CreateCore(const discord::ClientId& clientId);

	/**
	* Update Discord Activity
	* @param state State
	* @param details Details
	* @param largeImageSource LargeImageSource
	* @param largeImageText LargeImageText
	* @param smallImageSource SmallImageSource
	* @param smallImageText SmallImageText
	* @param activityType Activity Type
	*/
	void UpdateActivity(const std::string& state, const std::string& details, const std::string& largeImageSource, const std::string& largeImageText, const std::string& smallImageSource, const std::string& smallImageText, discord::ActivityType activityType = discord::ActivityType::Playing);

	/** Stop Discord Activity */
	void StopActivity();

	/**
	* Does Discord Core exist?
	* @return true if Discord Core exist
	*/
	bool HasCore();

private:

	/** Destroy Discord Core */
	void DestroyCore();

	/**
	* Discord Result to String
	* @param result Discord Result
	*/
	std::string ResultToString(const discord::Result& result);

private:

	/** Start time */
	discord::Timestamp m_startTime;

	/** Discord Core */
	std::unique_ptr<discord::Core> m_core;

	/** Discord current user */
	discord::User m_currentUser;

	/** Callback stopped? */
	std::atomic<bool> m_callbackStopped{ true };

	/** Stop Discord Activity event */
	StopActivityEvent m_stopActivityEvent;
};

#endif _DISCORD_GAME_SDK_H_ // If Discord Game SDK is included