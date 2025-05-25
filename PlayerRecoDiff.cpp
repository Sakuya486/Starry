#include"Xiao.h"

enum class Difficulty
{
	EASY,
	MEDIUM,
	HARD,
	EXTREME,
	A
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

	void recordScore1(int time, bool passed)
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
	Difficulty getDifficultyName() { return difficu; }
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
	Player(int ID, const string& name, DataStorage* storage = nullptr)
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
	const Record& getRecord(Difficulty diff)const { return *records[static_cast<int>(diff)]; }
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
