#include"Xiao.h"

class Game {
private:
	std::atomic<bool> gameRunning{ true };  // 原子标志，控制游戏运行状态
	std::atomic<bool> isPaused{ false };  // 暂停标志
	std::atomic<bool> shouldAutoPause{ false };  // 自动暂停标志
	int gameDuration = 120;                // 无限模式初始时长（秒）
	std::thread countdownThread;          // 倒计时线程
	std::thread inputThread;              // 输入处理线程

	// 倒计时线程函数（私有成员）
	void countdown() {
		auto startTime = std::chrono::high_resolution_clock::now();
		auto pauseTime = startTime;  // 记录暂停开始时间
		auto pausedDuration = std::chrono::seconds(0);  // 累计暂停时长
		bool autoPausing = false;    // 自动暂停中标志
		while (gameRunning) {
			if (shouldAutoPause && !autoPausing) {
				isPaused = true;
				autoPausing = true;
				std::cout << "\n触发中场休息5秒..." << std::endl;
				pauseTime = std::chrono::high_resolution_clock::now();
				// 自动暂停5秒
				std::this_thread::sleep_for(std::chrono::seconds(5));
				// 恢复计时
				pausedDuration += std::chrono::duration_cast<std::chrono::seconds>(
					std::chrono::high_resolution_clock::now() - pauseTime
				);
				isPaused = false;
				shouldAutoPause = false;
				autoPausing = false;
				std::cout << "\n中场休息结束，继续游戏..." << std::endl;
				continue;
			}
			if (isPaused) {
				pauseTime = std::chrono::high_resolution_clock::now();
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				continue;
			}
			if (pauseTime > startTime) {
				// 恢复时计算暂停时长并累加
				pausedDuration += std::chrono::duration_cast<std::chrono::seconds>(
					std::chrono::high_resolution_clock::now() - pauseTime
				);
				pauseTime = startTime;  // 重置暂停时间
			}
			auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(
				std::chrono::high_resolution_clock::now() - startTime
			).count();
			if (elapsedSeconds >= gameDuration) {
				gameRunning = false;
				break;
			}
			std::cout << "\r剩余时间：" << gameDuration - elapsedSeconds << " 秒" << std::flush;
			std::this_thread::sleep_for(std::chrono::seconds(10));
		}
		std::cout << "\n游戏结束！" << std::endl;
	}

	// 输入处理线程函数（私有成员）
	void handleInput() {
		while (gameRunning) {
			if (_kbhit()) {
				char c = _getch();
				if (c == 'q') {
					gameRunning = false;
					std::cout << "\n用户退出游戏！" << std::endl;
				}
				else if (c == 'p') {
					isPaused = !isPaused;
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
public:
	void setGameDuration(int newDuration)
	{
		if (newDuration > 0)
		{
			gameDuration = newDuration;
		}
	}

	void addGameDuration(int add)
	{
		if (add > 0)
		{
			gameDuration += add;
		}
	}

	// 启动游戏（公有接口）
	void start() {
		// 创建并启动线程
		countdownThread = std::thread(&Game::countdown, this);
		inputThread = std::thread(&Game::handleInput, this);
	}

	// 等待游戏结束（公有接口）
	void wait() {
		if (countdownThread.joinable()) countdownThread.join();
		if (inputThread.joinable()) inputThread.join();
	}
	// 析构函数：确保线程正确结束
	~Game() {
		wait();
	}

	void triggerAutoPause() {
		shouldAutoPause = true;
	}
};