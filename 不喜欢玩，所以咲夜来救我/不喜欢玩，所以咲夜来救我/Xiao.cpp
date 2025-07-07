#include"Xiao.h"

enum class Difficulty 
{
	EASY,
	MEDIUM,
	HARD,
	EXTREME,
	A
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
	cout << "2.难度模式" << endl;
	cout << "3.无限模式" << endl;
	cout << "4.我的" << endl;
	cout << "5.排行榜" << endl;
	cout << "6.游戏规则" << endl;
	cout << "7.退出游戏" << endl;
	cout << "(输入模式前的数字以进入相应的程序）" << endl;
}

void LevelMenu()
{
	cout << "================" << endl;
	cout << "    关卡模式    " << endl;
	cout << "================" << endl;
	cout << "1.关卡一" << endl;
	cout << "2.关卡二" << endl;
	cout << "3.关卡三" << endl;
	cout << "4.关卡四" << endl;
	cout << "5.关卡五" << endl;
	cout << "6.关卡六" << endl;
}

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

	bool CheckPath()
	{
		for (int i = 1; i < a1; i++)
		{
			if (arr3[i] != arr4[i])
			{
				return false;
			}
		}
		return true;
	}

	bool CheckPath(vector<int> arr3, vector<int> arr4)
	{
		for (int i = 1; i < a1; i++)
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
		const int nm = diff ;
		a1 = n;
		a2 = m;
		createArr3(n, m);
		createArr2(n, m, nm);
		createArr1(n);
	}

	void generateQuestion(int diff)
	{
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
		cout << "题目图案：" << endl;
		cout << "A轨迹:   " << "B轨迹：" << endl;
		for (int i = 0; i < a1; i++)
		{
			cout << "A" << i+1 << ".(" << arr1[i] % a2 << "," << arr1[i] / a2 << ")" << "      " << "B" << i+1 << ".(" << arr2[i] % a2 << "," << arr2[i] / a2 << ")" << endl;
		}
		cout << "相对轨迹可见点：" << "C1:" << arr3[0] << "    " << "C" << a1 << ":" << arr3[a1-1] << endl;
	}

	void inPath()
	{
	FLAG:
		for (int i = 1; i < a1-1; i++)
		{
			int x, y;
			cout << "C" << i + 1 << "x坐标:";
			cin >> x;
			cout << "C" << i + 1 << "y坐标:";
			cin >> y;
			arr4[i] = x + y * a2;
			if (x == 0 && y == 0)//输入x，y为零以重新输入数据
			{
				i--;
			}
		}
		if (!CheckPath())
		{
			cout << "输入错误，已重置相对路径！" << endl;
			goto FLAG;
		}
		else
		{
			cout << "你过关！" << endl;
		}
	}

	int getN() { return a1; }
	Difficulty getDifficulty() const { return difficulty; }
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
		:totalChallan(0), shortestTime(1000),averageTime(0), passes(0), passRate(0), difficu(dif), owner(owner) {}

	void recordScore1(int time, bool passed)//考虑删除mistakes
	{
		totalChallan++;
		if (time < shortestTime)
		{
			shortestTime = time;
		}
		if (passed)passes++;
		averageTime = (time + averageTime * (totalChallan - 1)) / totalChallan;
		passRate = passes / totalChallan * 100;
		// 数据更新后自动保存
		save();
	}

	void save() const {
		if (owner && owner->getStorage()) {
			owner->getStorage()->updateSinglePlayer(*owner);
		}
	}

	//getter
	Difficulty getDifficultyName(){return difficu;}
	int getTotalChallan() const { return totalChallan; }
	int getShortestTime() const { return shortestTime; }
	double getAverageTime() const { return averageTime; }
	int getPasses() const { return passes; }
	double getPassRate() const { return passRate; }

	// 添加序列化和反序列化方法
	friend std::ostream& operator<<(std::ostream& os, const Record& record) {
		os << static_cast<int>(record.difficu) << " "
			<< record.totalChallan << " "
			<< record.shortestTime << " "
			<< record.averageTime << " "
			<< record.passes << " "
			<< record.passRate;
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Record& record) {
		int difficulty;
		is >> difficulty;
		record.difficu = static_cast<Difficulty>(difficulty);
		is >> record.totalChallan
			>> record.shortestTime
			>> record.averageTime
			>> record.passes
			>> record.passRate;
		return is;
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
	array<unique_ptr<Record>, 4> records;
	DataStorage* storage; //存储类指针
public:
	Player(int ID, const string& name,DataStorage* storage = nullptr)
		:userID(ID), userName(name), totalChallenges(0), highestScore(0), lastChallengeScore(0), storage(storage)
	{
		records[static_cast<int>(Difficulty::EASY)] = std::make_unique<Record>(Difficulty::EASY, this);
		records[static_cast<int>(Difficulty::MEDIUM)] = std::make_unique<Record>(Difficulty::MEDIUM, this);
		records[static_cast<int>(Difficulty::HARD)] = std::make_unique<Record>(Difficulty::HARD, this);
		records[static_cast<int>(Difficulty::EXTREME)] = std::make_unique<Record>(Difficulty::EXTREME, this);
	}

	void recordScore2(int Score)
	{
		totalChallenges++;
		if (Score > highestScore)
		{
			highestScore = Score;
		}
		lastChallengeScore = Score;
		if (storage) {
			storage->updateSinglePlayer(*this);
		}//使数据自动储存
	}

	string getTrainningAdice()
	{
		return "建议多练习，提升解题速度和准确性。";//有待改进
	}

	// 添加序列化和反序列化方法
	friend std::ostream& operator<<(std::ostream& os, const Player& player) 
	{
		os << player.userID << " "
			<< player.userName << " "
			<< player.totalChallenges << " "
			<< player.highestScore << " "
			<< player.lastChallengeScore << "\n";

		for (const auto& record : player.records) {
			os << *record << "\n";
		}

		return os;
	}

	friend std::istream& operator>>(std::istream& is, Player& player) 
	{
		is >> player.userID
			>> player.userName
			>> player.totalChallenges
			>> player.highestScore
			>> player.lastChallengeScore;

		for (int i = 0; i < 4; ++i) {
			Record temp(static_cast<Difficulty>(i));
			is >> temp;
			player.records[i] = std::make_unique<Record>(temp);
		}

		return is;
	}

	//getter
	const Record& getRecord(Difficulty diff)const {return *records[static_cast<int>(diff)];}
	int getID() const { return userID; }
	const std::string& getUserName() const { return userName; }
	int getTotalChallenges() const { return totalChallenges; }
	int getHighestScore() const { return highestScore; }
	int getLastChallengeScore() const { return lastChallengeScore; }
	DataStorage* getStorage() const { return storage; }
	Record& getRecord(Difficulty diff) {
		return const_cast<Record&>(
			const_cast<const Player*>(this)->getRecord(diff)
			);
	}

	void copyDataFrom(const Player& other) {
		totalChallenges = other.totalChallenges;
		highestScore = other.highestScore;
		lastChallengeScore = other.lastChallengeScore;

		// 复制 Record 数据
		for (int i = 0; i < 4; ++i) {
			records[i] = std::make_unique<Record>(*(other.records[i]));
		}
	}
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

class GameManager
{
private:
	Question* currentQuestion;
	Player* currentPlayer;
	GameTimer timer;
	int gameDuration;
	Game game;
	int a = 0;                //记录游戏是否通关
public:
	GameManager(Player* player) :currentPlayer(player),gameDuration(120) {}
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
		currentQuestion->outPath();
		timer.start();
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

	void startGame0()
	{
		timer.start();
	}

	void endGame0(bool passed)
	{
		timer.stop();
		int time = timer.getElapsedSeconds();
		if (passed) { cout << "你过关！" << endl; }
		else { cout << "作答有错误!" << endl; }
		cout << "游戏结束！你的用时:" << time << endl;
	}

	void Gaming(Difficulty dif, int diff,int currentScore)
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
			diff++;
			game.addGameDuration(60);
			game.triggerAutoPause();
			goto SA;
		}
		game.wait();
		cout << "游戏已完全退出" << endl;
		cout << "你的分数为：" << currentScore<<endl;
		currentPlayer->recordScore2(currentScore);
	}
	int addScore(int currentScore, int diff,int n)
	{
		return currentScore += diff * (n - 2);
	}
};

class DataStorage
{
public:
	static void saveToFile(const vector<Player>& players)
	{
		ofstream outFile("players.txt", ios::app);
		if (outFile.is_open())
		{
			for (const auto& player : players)
			{
				outFile << player << "\n";
			}
			outFile.close();
		}
	}

	static std::vector<Player> loadFromFile()
	{
		std::vector<Player> players;
		std::ifstream inFile("players.txt");
		if (inFile.is_open())
		{
			while (inFile.peek() != EOF)
			{
				int id;
				std::string name;
				inFile >> id;
				inFile >> name;
				// 处理可能包含空格的用户名
				std::string line;
				std::getline(inFile, line);
				name += line;

				Player player(id, name);
				inFile >> player;
				players.push_back(std::move(player));
				// 跳过空行
				while (inFile.peek() == '\n')
					inFile.ignore();
			}
			inFile.close();
		}
		return players;
	}

	// 查找并返回特定ID的玩家引用
	static Player* findPlayerById(std::vector<Player>& players, int id) {
		for (auto& player : players) {
			if (player.getID() == id) {
				return &player;
			}
		}
		return nullptr;
	}

	// 更新特定玩家的数据
	static bool updatePlayerData(int playerId, const std::function<void(Player&)>& modifier) {
		// 从文件加载所有玩家数据
		std::vector<Player> players = loadFromFile();

		// 查找指定ID的玩家
		Player* player = findPlayerById(players, playerId);
		if (!player) {
			return false; // 未找到该玩家
		}
		// 应用修改
		modifier(*player);
		// 保存修改后的数据
		saveToFile(players);
		return true;
	}

	// 删除指定ID的玩家
	static bool deletePlayer(int playerId) {
		std::vector<Player> players = loadFromFile();
		// 查找并删除玩家
		auto it = std::remove_if(players.begin(), players.end(),
			[playerId](const Player& p) { return p.getID() == playerId; });
		if (it == players.end()) {
			return false; // 未找到该玩家
		}
		players.erase(it, players.end());
		// 保存修改后的数据
		saveToFile(players);
		return true;
	}

	//更新单个玩家数据
	static void updateSinglePlayer(const Player& player)
	{
		std::vector<Player> players = loadFromFile();
		// 查找并替换玩家数据
		bool found = false;
		for (auto& p : players)
		{
			if (p.getID() == player.getID())
			{
				// 创建一个临时可移动的 Player 对象
				Player temp(player.getID(), player.getUserName());
				temp.copyDataFrom(player);
				p = std::move(temp); // 使用移动赋值
				found = true;
				break;
			}
		}
		// 如果是新玩家，添加到列表
		if (!found) {
			players.push_back(player);
		}
		saveToFile(players);
	}

	// 输出玩家数据到控制台
	static void printPlayerInfo(const Player& player) {
		std::cout << "=== 玩家信息 ===" << std::endl;
		std::cout << "ID: " << player.getID() << std::endl;
		std::cout << "用户名: " << player.getUserName() << std::endl;
		std::cout << "总挑战次数: " << player.getTotalChallenges() << std::endl;
		std::cout << "最高分: " << player.getHighestScore() << std::endl;
		std::cout << "最后挑战分数: " << player.getLastChallengeScore() << std::endl;

		// 输出各难度记录
		printPlayerRecords(player);
	}

	// 输出玩家的所有难度记录
	static void printPlayerRecords(const Player& player) {
		std::cout << "\n=== 各难度记录 ===" << std::endl;
		const std::array<std::string, 4> difficultyNames = {
			"简单", "中等", "困难", "极限"
		};
		for (int i = 0; i < 4; ++i) {
			const Record& record = player.getRecord(static_cast<Difficulty>(i));
			std::cout << "\n" << difficultyNames[i] << "难度:" << std::endl;
			std::cout << "总挑战次数: " << record.getTotalChallan() << std::endl;
			std::cout << "最短用时: " << record.getShortestTime() << "秒" << std::endl;
			std::cout << "平均用时: " << record.getAverageTime() << "秒" << std::endl;
			std::cout << "通过次数: " << record.getPasses() << std::endl;
			std::cout << "通过率: " << record.getPassRate() << "%" << std::endl;
		}
	}
};

//针对于关卡模式的文件处理
class DataForLevel
{
private:
	vector<int> arr1;
	vector<int> arr2;
	vector<int> arr3;
	friend class Question;
public:
	bool loadFromFile(const std::string& filename) {
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cerr << "无法打开关卡文件: " << filename << std::endl;
			return false;
		}
		std::string line;
		// 读取第一行：A轨迹
		if (std::getline(file, line)) {
			arr1 = parseLine(line);
		}
		// 读取第二行：B轨迹
		if (std::getline(file, line)) {
			arr2 = parseLine(line);
		}
		// 读取第三行：C轨迹
		if (std::getline(file, line)) {
			arr3 = parseLine(line);
		}

		file.close();
		return true;
	}

	std::vector<int> parseLine(const std::string& line) {
		std::vector<int> result;
		std::istringstream iss(line);
		int value;
		while (iss >> value) {
			result.push_back(value);
		}
		return result;
	}

	void printInfo(int m) const {
		std::cout << "=== 关卡信息 ===" << std::endl;
		std::cout << "A\tB" << std::endl;
		for (size_t i = 0; i < arr1.size(); ++i) {
			// 输出 A 轨迹
			std::cout << "A" << i << ":(" << arr1[i] / m << "," << arr1[i] % m << ")";
			std::cout << "\t";
			// 输出 B 轨迹
			std::cout << "B" << i << ":(" << arr2[i] / m << "," << arr2[i] % m << ")";
			std::cout << std::endl;
		}
		// 输出 C 轨迹
		std::cout << "C 轨迹首元素: " << "(" << arr3.front() / m << "," << arr3.front() % m << ")" << std::endl;
		std::cout << "C 轨迹尾元素: " << "(" << arr3.back() / m << "," << arr3.back() % m << ")" << std::endl;
	}

	const std::vector<int>& getArr1() const { return arr1; }
	const std::vector<int>& getArr2() const { return arr2; }
	const std::vector<int>& getArr3() const { return arr3; }
};
