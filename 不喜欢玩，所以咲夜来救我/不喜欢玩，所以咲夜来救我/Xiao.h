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

class Player;
class DataStorage;

//状态机，便于切换主菜单及各个模式
enum GameState {
	MAIN_MENU,
	LEVEL,
	DD,          //难度模式
	INFINITE,    //无限 
	MINE,
	PRACTICE,
	RULE,
    EXIT
};

//状态机，用于子菜单
enum LevelState {
	LEVEL_MENU,
	L1,
	L2,
	L3,
	L4,
	L5,
	L6,
	OUT,
	EASY,
	MEDIUM,
	HARD,
	EXTREME,
	GT
};

//各难度，A是为除难度模式外的其他模式设置，便于Question类的初始化
enum class Difficulty {
	EASY,
	MEDIUM,
	HARD,
	EXTREME,
	A
};

//对各个菜单的声明
void MainMenu();
void LevelMenu();
void ruleMenu();
void DDMenu();
void PracticeMenu();

//检测<int>的有效输入
int getValidInteger();
//清屏
void clearScreen();

//计时器
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
//题目的生成及答案的输入和检测
class Question
{
private:
	Difficulty difficulty;     //对标难度
	vector<int> arr1;          //A轨迹
	vector<int> arr2;          //B轨迹
	vector<int> arr3;          //C轨迹
	vector<int> arr4;          //玩家输入的轨迹
	int a1, a2;
public:
	Question(Difficulty dif) : difficulty(dif) {}
	void createArr3(const int n, const int m);
	//n数组大小，m地图长度，nm数组元素跳跃的最大值
	void createArr2(const int n, const int m, const int nm);
	void createArr1(const int n, const int m);
	//用于其他模式答案检测
	bool CheckPath();            
	//用于关卡模式答案检测
	bool CheckPath(vector<int> arr3, vector<int> arr4, int N);
	//用于难度模式和练习模式的题目生成
	void generateQuestion(Difficulty dif);
	//用于无限模式的题目生成
	void generateQuestion(int diff);
	//其他模式（除关卡和练习）
	void outPath1();
	//练习模式题面输出
	void outPath2();
	//其他
	void inPath();
	//关卡
	void inPath1(int aa,int bb);
	//获取轨迹长度
	int getN();
	//地图大小
	int getM();
	//获取难度
	Difficulty getDifficulty() const;
	//获取玩家作答轨迹
	const std::vector<int>& getArr4() const;
};
//记录难度模式下玩家成绩
class Record
{
private:
	int totalChallan;
	double shortestTime;
	double averageTime;
	int passes;
	double passRate;
	Difficulty difficu;
	Player* owner;  // 指向所属 Player 的指针
public:
	Record(Difficulty dif, Player* owner = nullptr) 
		:totalChallan(0), shortestTime(1000), averageTime(0), passes(0), passRate(0), difficu(dif), owner(owner) {}
	//自动录入难度模式成绩
	void recordScore1(double time,bool passed);
	//为自动录入服务
	void save() const;
	//getters
	Difficulty getDifficultyName();
	int getTotalChallan() const;
	double getShortestTime() const;
	double getAverageTime() const;
	int getPasses() const;
	double getPassRate() const;
	//序列化和反序列化，便于文件操作
	friend std::ostream& operator<<(std::ostream& os, const Record& record);
	friend std::istream& operator>>(std::istream& is, Record& record);
};
//记录玩家信息和闯关记录
class Player
{
private:
	int userID;
	string userName;
	int totalChallenges;
	int highestScore;
	int lastChallengeScore;
	array<shared_ptr<Record>, 4> records;
	DataStorage* storage; //存储类指针
	std::shared_ptr<int> resource;
public:
	Player(int ID, const string& name, DataStorage* storage = nullptr) :userID(ID), userName(name), totalChallenges(0), highestScore(0), lastChallengeScore(0),resource(std::shared_ptr<int>(0))
	{
		records[static_cast<int>(Difficulty::EASY)] = std::make_unique<Record>(Difficulty::EASY, this);
		records[static_cast<int>(Difficulty::MEDIUM)] = std::make_unique<Record>(Difficulty::MEDIUM, this);
		records[static_cast<int>(Difficulty::HARD)] = std::make_unique<Record>(Difficulty::HARD, this);
		records[static_cast<int>(Difficulty::EXTREME)] = std::make_unique<Record>(Difficulty::EXTREME, this);
	}
	//获取记录
	const Record& getRecord(Difficulty diff)const;
	//对无限模式的成绩记录
	void recordScore2(int Score);
	string getTrainningAdice();
	//序列化和反序列化
	friend std::ostream& operator<<(std::ostream& os, const Player& player);
	friend std::istream& operator>>(std::istream& is, Player& player);
	//getters
	int getID() const;
	const std::string& getUserName() const;
	int getTotalChallenges() const;
	int getHighestScore() const;
	int getLastChallengeScore() const;
	DataStorage* getStorage() const;
	//用于玩家数据信息的更新
	void copyDataFrom(const Player& other);
	//获取记录，与上面同等作用的成员函数格式不同，方便不同情况下的调用
	Record& getRecord(Difficulty diff);
};
//倒计时，多线程，使之能在运行时仍能进行数据输入
class Game {
private:
	int b = 0;//记录游戏时间是否为零
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
	int getB();
};
//调动游戏运行
class GameManager
{
private:
	Question* currentQuestion;
	Player* currentPlayer;
	GameTimer timer;
	int gameDuration;
	Game game;
	int a = 0;                //记录游戏是否通关
	bool pa;                  //记录游戏是否通关
	int b = 0;                //记录倒计时是否结束
public:
	GameManager(Player* player):currentPlayer(player), gameDuration(120) {}
	string difficultyToString(Difficulty dif);
	//对于难度模式
	void startGame1(Difficulty dif);
	//对于练习模式
	void startGame1P(Difficulty dif);
	//对于难度模式和练习模式
	void endGame1(bool passed);
	//对于关卡模式，dif固定为A，aa为轨迹长度，bb为地图大小
	void startGame0(Difficulty dif, vector<int> arr,int aa,int bb);
	//对于关卡模式
	void endGame0(bool passed);
	//专为startGame2建立，用于处理题面相关及作答，dif为A，diff影响难度，与题面复杂度直接挂钩
	void Gaming(Difficulty dif, int diff, int currentScore);
	//对于无限模式
	void startGame2();
	//对于无限模式
	int addScore(int currentScore, int diff, int n);
	bool getpa();
};
//文件操作
class DataStorage
{
public:
	static void saveToFile(const vector<Player>& players);
	static std::vector<Player> loadFromFile();
	// 查找并返回特定ID的玩家引用
	static Player* findPlayerById(std::vector<Player>& players, int id);
	// 更新特定玩家的数据
	static bool updatePlayerData(int playerId, const std::function<void(Player&)>& modifier);
	// 删除指定ID的玩家
	static bool deletePlayer(int playerId);
	//更新单个玩家数据
	static void updateSinglePlayer(const Player& player);
	// 输出玩家数据到控制台
	static void printPlayerInfo(const Player& player);
	// 输出玩家的所有难度记录
	static void printPlayerRecords(const Player& player);
};
//针对于关卡模式的文件操作
class DataForLevel
{
private:
	vector<int> arr1;
	vector<int> arr2;
	vector<int> arr3;
	friend class Question;
public:
	bool loadFromFile(const std::string& filename);
	//按行读取文件
	std::vector<int> parseLine(const std::string& line);
	//输出题面
	void printInfo(int m) const;
	const std::vector<int>& getArr1() const;
	const std::vector<int>& getArr2() const;
	const std::vector<int>& getArr3() const;
};
