#include"Xiao.h"

enum class Difficulty 
{
	EASY,
	MEDIUM,
	HARD,
	EXTREME
};
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
		return duration.count() / 1000.0; // 转换为秒
	}
};
void MainMenu()
{
	cout << "================" << endl;
	cout << "    脑力航迹    " << endl;
	cout << "================" << endl;
	cout << "1.关卡模式" << endl;
	cout << "2.计时模式" << endl;
	cout << "3.无限模式" << endl;
	cout << "4.我的" << endl;
	cout << "5.排行榜" << endl;
}

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
	void createArr3(const int n, const int m)
	{
		arr3.resize(n);
		FLAG1:
		int x = (std::rand() % m - 2) + 1;
		int y = (std::rand() % m - 2) + 1;
		arr3[0] = x * m + y;
		int num = 0;
		for (int i = 1; i < n; i++)
		{
			int temple = (std::rand() % 3) + 0;
			switch (temple) {
			case 0: arr3[i] += m; break;
			case 1: arr3[i] -= m; break;
			case 2: arr3[i] += 1; break;
			case 3: arr3[i] -= 1; break;
			}
			if (arr3[i] <= 0) { i--; }
			if (arr3[i] > m * m) { i--; }
			for (int j = 0; j < i; j++)
			{
				if (arr3[i] == arr3[j]) { i--; }
			}
			num++;
			if (num > 10 * n) { i = 1; goto FLAG1; }
		}
	}
	void createArr2(const int n, const int m,const int nm)
	{
		arr2.resize(n);
	FLAG2:
		int x = (std::rand() % m - 2) + m/2;
		int y = (std::rand() % m - 2) + m/2;
		arr2[0] = x * m + y;
		int num = 0;
		for (int i = 1; i < n; i++)
		{
			int t1 = (std::rand() % 3) + 0;
			int t2 = (std::rand() % nm) + 1;
			switch (t1) {
			case 0: arr2[i] += t2*m; break;
			case 1: arr2[i] -= t2*m; break;
			case 2: arr2[i] += t2; break;
			case 3: arr2[i] -= t2; break;
			}
			if (arr2[i] <= 0) { i--; }
			if (arr2[i] > m * m) { i--; }
			num++;
			if (num > 10 * n) { i = 1; goto FLAG2; }
		}
	}
	void createArr1(const int n)
	{
		arr1.resize(n);
		for (int i = 1; i < n; i++)
		{
			arr1[i] = (arr3[i] - arr3[i - 1]) - (arr2[i] - arr2[i - 1]) + arr1[i - 1];
		}
	}
	bool CheckPath(const vector<int>& arr4,const int n)
	{
		for (int i = 0; i < n; i++)
		{
			if (arr3[i] != arr4[i])
			{
				return false;
			}
		}
		return true;
	}
	void generateQuestion(Difficulty dif)
	{
		int diff;
		switch (dif)
		{
		case Difficulty::EASY:diff = (rand() % 4) + 2; break;
		case Difficulty::MEDIUM:diff = (rand() % 7) + 5; break;
		case Difficulty::HARD:diff = (rand() % 10) + 8; break;
		case Difficulty::EXTREME:diff = (rand() % 13) + 11; break;
		}
		const int n = 2 * diff + 1;
		const int m = 5 * diff;
		const int nm = diff / 3;
		a1 = n;
		a2 = m;
		createArr3(n, m);
		createArr2(n, m, nm);
		createArr1(n);
	}
	void outPath()
	{
		for (int i = 0; i <= a1; i++)
		{
			cout << "(" << arr3[i] / a2 << "," << arr3[i] % a2 << ")" <<"      " << "(" << arr2[i] / a2 << "," << arr2[i] % a2 << ")" << endl;
		}
	}
};
class Record
{
private:
	int difficulity;
	int totalChallan;
	int shortestTime;
	double averageTime;
	int totalMistakes;
	int passes;
	double passRate;
	Difficulty difficu;
public:
	Record(int diff, Difficulty dif) :difficulity(diff), totalChallan(0), shortestTime(0),averageTime(0),totalMistakes(0), passes(0), passRate(0), difficu(dif) {}
	void recordScore1(int time, int mistakes, bool passed)
	{
		totalChallan++;
		if (time < shortestTime)
		{
			shortestTime = time;
		}
		totalMistakes += mistakes;
		if (passed)passes++;
		averageTime = (time + averageTime * (totalChallan - 1)) / totalChallan;
		passRate = passes / totalChallan * 100;
	}
	Difficulty getDifficultyName()
	{
		return difficu;
	}
};
class Player
{
private:
	int userID;
	string userName;
	int totalChallenges;//无限
	int highestScore;
	int lastChallengeScore;
	//有时间搞记录所有内容(初步判断要包含另一个记录类
public:
	Player(int ID, const string& name) :userID(ID), userName(name), totalChallenges(0), highestScore(0), lastChallengeScore(0) {}
	void recordScore2(int mistakes,int Score)
	{
		totalChallenges++;
		if (Score > highestScore)
		{
			highestScore = Score;
		}
		lastChallengeScore = Score;
	}
	string getTrainningAdice()
	{
		return "建议多练习，提升解题速度和准确性。";//有待改进
	}
};
class GameManager
{
private:
	Question* currentQuestion;
	Player* currentPlayer;
	GameTimer timer;
public:
	GameManager(Player* player) :currentPlayer(player) {}
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
		currentQuestion = new Question(dif);
		currentQuestion->generateQuestion(dif);
		cout << "游戏开始！当前题目难度为：" << difficultyToString(dif) << endl;
		cout << "题目图案：" << endl;
		cout << "A轨迹:   " << "B轨迹：" << endl;
		currentQuestion->outPath();
		timer.start();
	}
	void endGame1(int mistakes)
	{
		timer.stop();
		int time = timer.getElapsedSeconds();
		cout << "游戏结束！你的用时:" << time << endl;//可以检测是否打破记录
		delete currentQuestion;
		//没有记录成绩
	}
	void startGame2();//缺个倒计时
	void endGame2();
	int calculateScore(int currentScore, int diff);
};
