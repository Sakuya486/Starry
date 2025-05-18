#pragma once

#include<iostream>
#include<string>
#include<map>
#include<vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

enum class Difficulty {
	EASY,
	MEDIUM,
	HARD,
	EXTREME
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
class Question
{
private:
	Difficulty difficulty;
	vector<int> arr1;
	vector<int> arr2;
	vector<int> arr3;
	int a1, a2;
public:
	Question(Difficulty dif) : difficulty(dif) {}
	void createArr3(const int n, const int m);
	void createArr2(const int n, const int m, const int nm);
	void createArr1(const int n);
	bool CheckPath(const vector<int>& arr4, const int n);
	void generateQuestion(Difficulty dif);
	void outPath();
};

void MainMenu();

class Record
{
private:
	int difficulity;
	int totalChallan;
	double averageTime;
	int totalMistakes;
	int passes;
	double passRate;
	Difficulty difficu;
public:
	Record(int diff, Difficulty dif):difficulity(diff),totalChallan(0),averageTime(0),totalMistakes(0),passes(0),passRate(0),difficu(dif){}
	virtual~Record() = default;
	void recordScore1(int time,int mistakes,bool passed);
	string getDifficultyName();
};
class Player
{
private:
	int userID;
	string userName;
	int totalChallenges;
	int highestScore;
	int lastChallengeScore;
public:
	Player(int ID,const string& name):userID(ID),userName(name),totalChallenges(0),highestScore(0),lastChallengeScore(0){}
	void recordScore2(int mistakes, int Score);
	string getTrainningAdice();
};
class GameManager
{
private:
	Question* currentQuestion;
	Player* currentPlayer;
	GameTimer timer;
public:
	GameManager(Player* player):currentPlayer(player){}
	void startGame1(Difficulty dif);//对于关卡和计时模式
	void endGame1(int mistakes);
	void startGame2();//对于无限模式
	void endGame2();
	int calculateScore(int currentScore,int diff);
};
