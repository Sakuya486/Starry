#include"Xiao.h"

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