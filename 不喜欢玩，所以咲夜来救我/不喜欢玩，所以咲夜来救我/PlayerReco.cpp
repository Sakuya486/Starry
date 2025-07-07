#include"Xiao.h"

	void Record::recordScore1(double time, bool passed)
	{
		totalChallan++;
		if (passed) {
			if (time < shortestTime)
			{
				shortestTime = time;
			}
			averageTime = (time + averageTime * (totalChallan - 1)) / totalChallan;
		}
		if (passed)passes++;
		passRate = passes / totalChallan * 100;
		// 数据更新后自动保存
		save();
	}

	void Record::save() const {
		if (owner && owner->getStorage()) {
			owner->getStorage()->updateSinglePlayer(*owner);
		}
	}

	//getter
	Difficulty Record::getDifficultyName() { return difficu; }
	int Record::getTotalChallan() const { return totalChallan; }
	double Record::getShortestTime() const { return shortestTime; }
	double Record::getAverageTime() const { return averageTime; }
	int Record::getPasses() const { return passes; }
	double Record::getPassRate() const { return passRate; }

	// 添加序列化和反序列化方法,以便于实现对文件的操作
	std::ostream& operator<<(std::ostream& os, const Record& record) {
		os << static_cast<int>(record.difficu) << " "
			<< record.totalChallan << " "
			<< record.shortestTime << " "
			<< record.averageTime << " "
			<< record.passes << " "
			<< record.passRate;
		return os;
	}

	std::istream& operator>>(std::istream& is, Record& record) {
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

	void Player::recordScore2(int Score)
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

	string Player::getTrainningAdice()
	{
		return "建议多练习，提升解题速度和准确性。";//有待改进
	}

	// 添加序列化和反序列化方法
	std::ostream& operator<<(std::ostream& os, const Player& player)
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

	std::istream& operator>>(std::istream& is, Player& player)
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
	const Record& Player::getRecord(Difficulty diff)const { return *records[static_cast<int>(diff)]; }
	int Player::getID() const { return userID; }
	const std::string& Player::getUserName() const { return userName; }
	int Player::getTotalChallenges() const { return totalChallenges; }
	int Player::getHighestScore() const { return highestScore; }
	int Player::getLastChallengeScore() const { return lastChallengeScore; }
	DataStorage* Player::getStorage() const { return storage; }
	Record& Player::getRecord(Difficulty diff) {
		return const_cast<Record&>(
			const_cast<const Player*>(this)->getRecord(diff)
			);
	}

	void Player::copyDataFrom(const Player& other) {
		totalChallenges = other.totalChallenges;
		highestScore = other.highestScore;
		lastChallengeScore = other.lastChallengeScore;

		// 复制 Record 数据
		for (int i = 0; i < 4; ++i) {
			records[i] = std::make_unique<Record>(*(other.records[i]));
		}
	}
