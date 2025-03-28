#pragma once

class ConsoleManager : public TSingletonMutex<ConsoleManager>
{
public:

	/*
	* Create a console
	* @param consoleName - Console Name
	*/
	void Create(const std::wstring& consoleName = L"Console");

	/** Destroy the console */
	void Destroy();

	/** Did Console exist? */
	bool HasConsole();

	/*
	* Set IO state
	* @param state IO state
	*/
	void SetIoState(std::ios_base::iostate state = 0);

	/** Clear IO state  */
	void ClearIoState();

	/** Redirect IO to console  */
	void RedirectIoToConsole();

private:

	bool m_hasConsole = false;
};

