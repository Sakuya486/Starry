#pragma once

//C++ 标准库核心功能
#include <iostream>    // 输入输出流
#include <string>      // 字符串处理
#include <vector>      // 动态数组容器
#include <map>         // 关联容器（键值对）
//系统与时间相关
#include <cstdlib>     // 通用工具库（含随机数生成等）
#include <ctime>       // C风格时间函数
#include <chrono>      // C++时间库（高精度计时）
#include <thread>      // 线程支持库
//内存与智能指针
#include <memory>      // 智能指针（如unique_ptr、shared_ptr）
//容器与数据结构
#include <array>       // 固定大小数组容器
//并发与原子操作
#include <atomic>      // 原子类型支持（多线程同步）
//平台特定（非标准跨平台）
#include <conio.h>     // 控制台输入输出（Windows特定）
//文件操作
#include <fstream>     // 文件流操作（读写文件）
//函数式编程支持
#include <functional>  // 函数对象与回调支持
//字符串流处理
#include <sstream>     // 字符串流（如stringstream）

using namespace std;

enum class Difficulty {
	EASY,
	MEDIUM,
	HARD,
	EXTREME,
	A
};

class GameTimer {
private:
	chrono::time_point<chrono::high_resolution_clock> startTime;
	chrono::time_point<chrono::high_resolution_clock> endTime;
	bool isRunning = false;
public:
	void start();
	void stop();
	double getElapsedSeconds()const;
};
void MainMenu();
void LevelMenu();
void ruleMenu();
class Question
{
private:
	Difficulty difficulty;
	vector<int> arr1;
	vector<int> arr2;
	vector<int> arr3;
	vector<int> arr4;
	int a1, a2;
public:
	Question(Difficulty dif) : difficulty(dif) {}
	void createArr3(const int n, const int m);
	void createArr2(const int n, const int m, const int nm);//n数组大小，m地图长度，nm数组元素跳跃的最大值
	void createArr1(const int n);
	bool CheckPath();
	bool CheckPath(vector<int> arr3, vector<int> arr4);
	void generateQuestion(Difficulty dif);
	void generateQuestion(int diff);
	void outPath();
	void inPath();
	void inPath1();
	int getN();
	Difficulty getDifficulty() const;
};
class Record
{
private:
	int totalChallan;
	int shortestTime;
	double averageTime;
	int passes;
	double passRate;
	Difficulty difficu;
	Player* owner;  // 指向所属 Player 的指针
public:
	Record(Difficulty dif, Player* owner = nullptr) 
		:totalChallan(0), shortestTime(1000), averageTime(0), passes(0), passRate(0), difficu(dif), owner(owner) {}
	void recordScore1(int time,bool passed);
	void save() const;
	string getDifficultyName();
	int getTotalChallan() const;
	int getShortestTime() const;
	double getAverageTime() const;
	int getPasses() const;
	double getPassRate() const;
	friend std::ostream& operator<<(std::ostream& os, const Record& record);
	friend std::istream& operator>>(std::istream& is, Record& record);
};
class Player
{
private:
	int userID;
	string userName;
	int totalChallenges;
	int highestScore;
	int lastChallengeScore;
	array<unique_ptr<Record>, 4> records;
	DataStorage* storage; //存储类指针
public:
	Player(int ID,const string& name, DataStorage* storage = nullptr):userID(ID),userName(name),totalChallenges(0),highestScore(0),lastChallengeScore(0)
	{
		records[static_cast<int>(Difficulty::EASY)] = std::make_unique<Record>(Difficulty::EASY, this);
		records[static_cast<int>(Difficulty::MEDIUM)] = std::make_unique<Record>(Difficulty::MEDIUM, this);
		records[static_cast<int>(Difficulty::HARD)] = std::make_unique<Record>(Difficulty::HARD, this);
		records[static_cast<int>(Difficulty::EXTREME)] = std::make_unique<Record>(Difficulty::EXTREME, this);
	}
	const Record& getRecord(Difficulty diff)const;
	void recordScore2(int Score);
	string getTrainningAdice();
	friend std::ostream& operator<<(std::ostream& os, const Player& player);
	friend std::istream& operator>>(std::istream& is, Player& player);
	int getID() const;
	const std::string& getUserName() const;
	int getTotalChallenges() const;
	int getHighestScore() const;
	int getLastChallengeScore() const;
	DataStorage* getStorage() const;
	void copyDataFrom(const Player& other);
	Record& getRecord(Difficulty diff);
};
class Game {
private:
	std::atomic<bool> gameRunning{ true };  // 原子标志，控制游戏运行状态
	std::atomic<bool> isPaused{ false };  // 暂停标志
	std::atomic<bool> shouldAutoPause{ false };  // 自动暂停标志
	int gameDuration = 120;                // 无限模式初始时长（秒）
	std::thread countdownThread;          // 倒计时线程
	std::thread inputThread;              // 输入处理线程
	// 倒计时线程函数（私有成员）
	void countdown();
	// 输入处理线程函数（私有成员）
	void handleInput();
public:
	void setGameDuration(int newDuration);
	void addGameDuration(int add);
	// 启动游戏（公有接口）
	void start();
	// 等待游戏结束（公有接口）
	void wait();
	// 析构函数：确保线程正确结束
	~Game() {
		wait();
	}
	void triggerAutoPause();
};
class GameManager
{
private:
	Question* currentQuestion;
	Player* currentPlayer;
	GameTimer timer;
	int gameDuration;
	Game game;
	int a = 0;                //记录游戏是否通关
	bool pa;
public:
	GameManager(Player* player):currentPlayer(player), gameDuration(120) {}
	void startGame1(Difficulty dif);//对于难度模式
	string difficultyToString(Difficulty dif);
	void endGame1(bool passed);
	void startGame0(Difficulty dif);//对于关卡模式
	void endGame0(bool passed);
	void Gaming(Difficulty dif, int diff, int currentScore);//专为startGame2建立
	void startGame2();//对于无限模式
	int addScore(int currentScore, int diff, int n);
	bool getpa();
};
class DataStorage
{
public:
	static void saveToFile(const vector<Player>& players);
	static std::vector<Player> loadFromFile();
	static Player* findPlayerById(std::vector<Player>& players, int id);
	static bool updatePlayerData(int playerId, const std::function<void(Player&)>& modifier);
	static bool deletePlayer(int playerId);
	static void updateSinglePlayer(const Player& player);
	static void printPlayerInfo(const Player& player);
	static void printPlayerRecords(const Player& player);
};
class DataForLevel
{
private:
	vector<int> arr1;
	vector<int> arr2;
	vector<int> arr3;
	friend class Question;
public:
	bool loadFromFile(const std::string& filename);
	std::vector<int> parseLine(const std::string& line);
	void printInfo(int m) const;
	const std::vector<int>& getArr1() const;
	const std::vector<int>& getArr2() const;
	const std::vector<int>& getArr3() const;
};
