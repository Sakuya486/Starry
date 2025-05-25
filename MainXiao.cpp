#include"Xiao.h"

int main()
{
	std::srand(std::time(nullptr));
	Player player(1,"TestPlayer");
	GameManager GM(&player);
	Ff:
	MainMenu();

	int a;
	cin >> a;
	switch (a)
	{
	case 1:
	{
		DataForLevel level;
		LevelMenu();
		bool pa = false;
		int LeCh;
		cin >> LeCh;
		switch (LeCh)
		{
		case1:
			{
				if (!level.loadFromFile("level1.txt"))
				{
					return 1;
				}
				cout << "地图8*8，轨迹长度为6" << endl;
				std::this_thread::sleep_for(std::chrono::seconds(2));
				level.printInfo(8);
				GM.startGame0(Difficulty::A);
				pa = GM.getpa();
				GM.endGame0(pa);
				break;
			}
		case2:
			{
				if (!level.loadFromFile("level2.txt"))
				{
					return 1;
				}
				cout << "地图15*15，轨迹长度为8" << endl;
				std::this_thread::sleep_for(std::chrono::seconds(2));
				level.printInfo(15);
				GM.startGame0(Difficulty::A);
				pa = GM.getpa();
				GM.endGame0(pa);
				break;
			}
		case3:
			{
				if (!level.loadFromFile("level3.txt"))
				{
					return 1;
				}
				cout << "地图28*28，轨迹长度为6" << endl;
				std::this_thread::sleep_for(std::chrono::seconds(2));
				level.printInfo(28);
				GM.startGame0(Difficulty::A);
				pa = GM.getpa();
				GM.endGame0(pa);
				break;
			}
		case10:
			{
				goto Ff;
				break;
			}
		}

	}
	case 7:
	{
		ruleMenu();
		int back;
		switch (back)
		{
		case10:
			{
				goto Ff;
				break;
			}
		}
		break;
	}
	}




	return 0;
}