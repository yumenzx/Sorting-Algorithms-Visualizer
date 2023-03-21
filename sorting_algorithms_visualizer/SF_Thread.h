#pragma once

#include <SFML/Graphics.hpp>

class SF_Thread : protected sf::Thread
{
private:
	bool running;
public:
	template <typename F, typename A>
	SF_Thread(F function, A argument);

	bool isRunning();
	bool* getRunningInstance();
	
	void start();
	void terminate();
};

template<typename F, typename A>
inline SF_Thread::SF_Thread(F function, A argument) :Thread(function, argument)
{
	running = false;
};
