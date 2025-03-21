#pragma once

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

class DiscordManager : public TSingletonMutex<DiscordManager>
{
private:

	enum class ResultGetter
	{
		Core = 0,
		User = 1,
		Activity = 2
	};

public:

	void CreateCore();
	void UpdateActivity(const std::string& state, const std::string& details, const std::string& largeImageText, const std::string& smallImageSource, const std::string& smallImageText, discord::ActivityType activityType = discord::ActivityType::Playing);
	void StopActivity();
	bool IsCoreExist();

public:

	const discord::ClientId CLIENT_ID{ 1351785436850163733 };

private:
	void ClearActivity();
	void CheckResult(ResultGetter const& resultGetter, discord::Result const& result) const;
private:
	discord::Timestamp m_startTime;
	std::unique_ptr<discord::Core> m_core;
	discord::User m_currentUser;
	std::atomic<bool> m_callbackStopped{ true };
	StopActivityEvent m_stopActivityEvent;
};

