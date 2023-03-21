#include "SF_Thread.h"

bool SF_Thread::isRunning()
{
	return running;
}

bool* SF_Thread::getRunningInstance()
{
	return &running;
}

void SF_Thread::start()
{
	running = true;
	Thread::launch();
}

void SF_Thread::terminate()
{
	Thread::terminate();
	running = false;
}
