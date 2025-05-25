#include"Xiao.h"

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
	GameManager(Player* player) :currentPlayer(player), gameDuration(120) {}
	string difficultyToString(Difficulty dif) {
		switch (dif) {
		case Difficulty::EASY: return "EASY";
		case Difficulty::MEDIUM: return "MEDIUM";
		case Difficulty::HARD: return "HARD";
		case Difficulty::EXTREME: return "EXTREME";
		default: return "UNKNOWN";
		}
	}

	void startGame1(Difficulty dif)
	{
		pa = false;
		currentQuestion = new Question(dif);
		currentQuestion->generateQuestion(dif);
		cout << "游戏开始！当前题目难度为：" << difficultyToString(dif) << endl;
		currentQuestion->outPath();
		timer.start();
		currentQuestion->inPath1();
		if (currentQuestion->CheckPath())
		{
			pa = true;
		}
	}

	void endGame1(bool passed)
	{
		timer.stop();
		int time = timer.getElapsedSeconds();
		cout << "游戏结束！你的用时:" << time << endl;//可以检测是否打破记录
		// 获取当前玩家对应的难度记录
		Difficulty currentDifficulty = currentQuestion->getDifficulty(); // 假设Question类有getDifficulty方法
		Record& record = currentPlayer->getRecord(currentDifficulty);
		// 调用Record的recordScore1方法记录成绩
		record.recordScore1(time, passed); // 传入用时和通关状态
		delete currentQuestion;
	}

	void startGame0(Difficulty dif)
	{
		pa = false;
		dif = Difficulty::A;
		currentQuestion = new Question(dif);
		timer.start();
		currentQuestion->inPath1();
		if (currentQuestion->CheckPath())
		{
			pa = true;
		}
	}

	void endGame0(bool passed)
	{
		timer.stop();
		int time = timer.getElapsedSeconds();
		if (passed) { cout << "你过关！" << endl; }
		else { cout << "作答有错误!" << endl; }
		cout << "游戏结束！你的用时:" << time << endl;
		delete currentQuestion;
	}

	void Gaming(Difficulty dif, int diff, int currentScore)
	{
		a = 0;
		dif = Difficulty::A;
		currentQuestion = new Question(dif);
		currentQuestion->generateQuestion(diff);
		cout << "游戏开始！当前题目难度为：" << diff << endl;
		currentQuestion->outPath();
		currentQuestion->inPath();
		if (currentQuestion->CheckPath())
		{
			a = 1;
			addScore(currentScore, diff, currentQuestion->getN());
		}
		delete currentQuestion;
	}

	void startGame2()
	{
		game.setGameDuration(120);
		game.start();
		int diff = 3;
		int currentScore = 0;
	SA:
		Gaming(Difficulty::A, diff, currentScore);
		if (a = 1)
		{
			cout << "您当前的分数为:" << currentScore << endl;
			diff+= (rand() % 2) + 1;
			game.addGameDuration(60);
			game.triggerAutoPause();
			goto SA;
		}
		game.wait();
		cout << "游戏已完全退出" << endl;
		cout << "你的分数为：" << currentScore << endl;
		currentPlayer->recordScore2(currentScore);
	}
	int addScore(int currentScore, int diff, int n)
	{
		return currentScore += diff * (n - 2);
	}

	bool getpa(){ return pa; }
};