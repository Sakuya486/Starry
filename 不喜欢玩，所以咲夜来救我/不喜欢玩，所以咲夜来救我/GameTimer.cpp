#include"Xiao.h"

	void GameTimer::start()
	{
		startTime = chrono::high_resolution_clock::now();
		isRunning = true;
	}

	void GameTimer::stop()
	{
		endTime = chrono::high_resolution_clock::now();
		isRunning = false;
	}

	double GameTimer::getElapsedSeconds() const
	{
		auto end = isRunning ? chrono::high_resolution_clock::now() : endTime;
		auto duration = chrono::duration_cast<chrono::milliseconds>(end - startTime);
		return duration.count() / 1000.0; // ×ª»»ÎªÃë
	}
