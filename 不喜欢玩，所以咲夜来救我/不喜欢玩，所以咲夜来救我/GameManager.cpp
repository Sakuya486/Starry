#include"Xiao.h"

	string GameManager::difficultyToString(Difficulty dif) {
		switch (dif) {
		case Difficulty::EASY: return "EASY";
		case Difficulty::MEDIUM: return "MEDIUM";
		case Difficulty::HARD: return "HARD";
		case Difficulty::EXTREME: return "EXTREME";
		default: return "UNKNOWN";
		}
	}

	void GameManager::startGame1(Difficulty dif)
	{
		pa = false;
		currentQuestion = new Question(dif);
		currentQuestion->generateQuestion(dif);
		int N = currentQuestion->getN();
		int M= currentQuestion->getM();
		cout << "游戏开始！当前题目难度为：" << difficultyToString(dif) << endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		currentQuestion->outPath1();
		timer.start();
		currentQuestion->inPath1(N,M);
		if (currentQuestion->CheckPath())
		{
			pa = true;
		}
	}

	void GameManager::startGame1P(Difficulty dif)
	{
		pa = false;
		currentQuestion = new Question(dif);
		currentQuestion->generateQuestion(dif);
		int N = currentQuestion->getN();
		int M = currentQuestion->getM();
		cout << "游戏开始！当前题目难度为：" << difficultyToString(dif) << endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		currentQuestion->outPath2();
		timer.start();
		currentQuestion->inPath1(N, M);
		if (currentQuestion->CheckPath())
		{
			pa = true;
		}
	}

	void GameManager::endGame1(bool passed)
	{
		timer.stop();
		double time = timer.getElapsedSeconds();
		if (passed) { cout << endl << "你过关！" << endl; }
		else { cout << endl << "作答有错误!" << endl; }
		cout << "游戏结束！你的用时:" << time <<"秒" << endl << endl;//可以检测是否打破记录
		// 获取当前玩家对应的难度记录
		Difficulty currentDifficulty = currentQuestion->getDifficulty(); // 假设Question类有getDifficulty方法
		Record& record = currentPlayer->getRecord(currentDifficulty);
		// 调用Record的recordScore1方法记录成绩
		record.recordScore1(time, passed); // 传入用时和通关状态
		delete currentQuestion;
	}

	void GameManager::startGame0(Difficulty dif, vector<int> arr,int aa,int bb)
	{
		vector<int> arr4;
		pa = false;
		currentQuestion = new Question(dif);
		timer.start();
		currentQuestion->inPath1(aa,bb);
		arr4 = currentQuestion->getArr4();
		if (currentQuestion->CheckPath(arr4,arr,aa))
		{
			pa = true;
		}
	}

	void GameManager::endGame0(bool passed)
	{
		timer.stop();
		double time = timer.getElapsedSeconds();
		if (passed) { cout << endl << "你过关！" << endl; }
		else { cout << endl << "作答有错误!" << endl; }
		cout << "游戏结束！你的用时:" << time << "秒" << endl << endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		delete currentQuestion;
	}

	void GameManager::Gaming(Difficulty dif, int diff, int currentScore)
	{
		a = 0;
		dif = Difficulty::A;
		currentQuestion = new Question(dif);
		currentQuestion->generateQuestion(diff);
		cout << "\n游戏开始！当前题目难度为：" << diff << endl;
		currentQuestion->outPath1();
		Rein:
		currentQuestion->inPath();
		b = game.getB();
		if (b == 1) {
			if (currentQuestion->CheckPath())
			{
				a = 1;
				addScore(currentScore, diff, currentQuestion->getN());
			}
			else
			{
				cout << "输入错误，已重置相对路径！" << endl << "请重新输入C路径" << endl;
				goto Rein;
			}
		}
		delete currentQuestion;
	}

	void GameManager::startGame2()
	{
		game.setGameDuration(20);
		game.start();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		int diff = 3;
		int currentScore = 0;
		b = 1;
	SA:
		b = game.getB();
		Gaming(Difficulty::A, diff, currentScore);
		if (b != 0) {
			if (a = 1)
			{
				cout << "您当前的分数为:" << currentScore << endl;
				diff += (rand() % 2) + 1;
				game.addGameDuration(60);
				game.triggerAutoPause();
				goto SA;
			}
		}
		game.wait();
		cout << "\n游戏已完全退出" << endl;
		cout << "你的分数为：" << currentScore << endl;
		currentPlayer->recordScore2(currentScore);
	}
	int GameManager::addScore(int currentScore, int diff, int n)
	{
		return currentScore += diff * (n - 2);
	}

	bool GameManager::getpa(){ return pa; }
