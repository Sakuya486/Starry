#include"Xiao.h"

class GameTimer
{
private:
	chrono::time_point<chrono::high_resolution_clock> startTime;
	chrono::time_point<chrono::high_resolution_clock> endTime;
	bool isRunning = false;
public:
	void start()
	{
		startTime = chrono::high_resolution_clock::now();
		isRunning = true;
	}

	void stop()
	{
		endTime = chrono::high_resolution_clock::now();
		isRunning = false;
	}

	double getElapsedSeconds() const
	{
		auto end = isRunning ? chrono::high_resolution_clock::now() : endTime;
		auto duration = chrono::duration_cast<chrono::milliseconds>(end - startTime);
		return duration.count() / 1000.0; // ×ª»»ÎªÃë
	}
};