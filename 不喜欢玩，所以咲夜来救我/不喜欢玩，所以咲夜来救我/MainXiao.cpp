#include"Xiao.h"

int main()
{
	std::srand(std::time(nullptr));
	GameState currentState = MAIN_MENU;
	DataStorage storage;
	Player player(1, "TestPlayer", &storage);
	GameManager GM(&player);

	int a = 0;          //在主菜单中进行选择
	int c = 0;          //在关卡模式菜单中进行选择,在难度模式菜单中进行选择
	int b = 0;          //在关卡结束后对返回主菜单或关卡菜单进行选择
	string ad;          //用于获取玩家建议
	LevelState cState = LEVEL_MENU;
	DataForLevel level;
	bool pa = false;
	while (currentState != EXIT)
	{
		switch (currentState)
		{
		case MAIN_MENU:
			clearScreen();
			MainMenu();
			a = getValidInteger();      //在主菜单中进行选择
			switch (a)
			{
			case 1:
				currentState = LEVEL;
				break;
			case 2:
				currentState = DD;
				break;
			case 3:
				currentState = INFINITE;
				break;
			case 4:
				currentState = MINE;
				break;
			case 5:
				currentState = PRACTICE;
				break;
			case 6:
				currentState = RULE;
				break;
			case 7:
				currentState = EXIT;
				break;
			default:
				std::cout << "无效选择，请重新输入!" << endl;
			}
			break;
		case LEVEL:
			cState = LEVEL_MENU;
			c = 0;
			while (cState != OUT)
			{
				vector<int> arr3;
				switch (cState)
				{
				case LEVEL_MENU:
					clearScreen();
					LevelMenu();
					c = 0;
					b = 0;
					pa = false;
					arr3.clear();
					cin >> c;
					switch (c)
					{
					case 1:
						cState = L1;
						break;
					case 2:
						cState = L2;
						break;
					case 3:
						cState = L3;
						break;
					case 7:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				case L1:
					clearScreen();
					if (!level.loadFromFile("Level1.txt"))
					{
						return 1;
					}
					std::cout << "地图8*8，轨迹长度为6" << endl;
					std::this_thread::sleep_for(std::chrono::seconds(2));
					level.printInfo(8);
					arr3 = level.getArr3();
					GM.startGame0(Difficulty::A, arr3,6,8);
					pa = GM.getpa();
					GM.endGame0(pa);
					std::cout << "返回主菜单请输入1，返回关卡菜单请输入2" << endl;
					b = getValidInteger();
					switch (b)
					{
					case 1:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					case 2:
						cState = LEVEL_MENU;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				case L2:
					clearScreen();
					if (!level.loadFromFile("Level2.txt"))
					{
						return 1;
					}
					std::cout << "地图15*15，轨迹长度为8" << endl;
					std::this_thread::sleep_for(std::chrono::seconds(2));
					level.printInfo(15);
					arr3 = level.getArr3();
					GM.startGame0(Difficulty::A, arr3,8,15);
					pa = GM.getpa();
					GM.endGame0(pa);
					std::cout << "返回主菜单请输入1，返回关卡菜单请输入2" << endl;
					b = getValidInteger();
					switch (b)
					{
					case 1:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					case 2:
						cState = LEVEL_MENU;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				case L3:
					clearScreen();
					if (!level.loadFromFile("Level3.txt"))
					{
						return 1;
					}
					std::cout << "地图28*28，轨迹长度为11" << endl;
					std::this_thread::sleep_for(std::chrono::seconds(2));
					level.printInfo(28);
					arr3 = level.getArr3();
					GM.startGame0(Difficulty::A, arr3,11,28);
					pa = GM.getpa();
					GM.endGame0(pa);
					std::cout << "返回主菜单请输入1，返回关卡菜单请输入2" << endl;
					b = getValidInteger();
					switch (b)
					{
					case 1:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					case 2:
						cState = LEVEL_MENU;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				default:
					std::cout << "无效选择，请重新输入!" << endl;
				}
			}
			break;
		case DD:
			clearScreen();
			cState = LEVEL_MENU;
			while (cState != OUT)
			{
				switch (cState)
				{
				case LEVEL_MENU:
					clearScreen();
					DDMenu();
					pa = false;
					c = 0;
					b = 0;
					c = getValidInteger();
					switch (c)
					{
					case 1:
						cState = EASY;
						break;
					case 2:
						cState = MEDIUM;
						break;
					case 3:
						cState = HARD;
						break;
					case 4:
						cState = EXTREME;
						break;
					case 7:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				case EASY:
					clearScreen();
					GM.startGame1(Difficulty::EASY);
					pa = GM.getpa();
					GM.endGame1(pa);
					std::cout << "返回主菜单请输入1，返回挑选难度界面请输入2" << endl;
					b = getValidInteger();
					switch (b)
					{
					case 1:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					case 2:
						cState = LEVEL_MENU;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				case MEDIUM:
					clearScreen();
					GM.startGame1(Difficulty::MEDIUM);
					pa = GM.getpa();
					GM.endGame1(pa);
					std::cout << "返回主菜单请输入1，返回挑选难度界面请输入2" << endl;
					b = getValidInteger();
					switch (b)
					{
					case 1:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					case 2:
						cState = LEVEL_MENU;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				case HARD:
					clearScreen();
					GM.startGame1(Difficulty::HARD);
					pa = GM.getpa();
					GM.endGame1(pa);
					std::cout << "返回主菜单请输入1，返回挑选难度界面请输入2" << endl;
					b = getValidInteger();
					switch (b)
					{
					case 1:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					case 2:
						cState = LEVEL_MENU;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				case EXTREME:
					clearScreen();
					GM.startGame1(Difficulty::EXTREME);
					pa = GM.getpa();
					GM.endGame1(pa);
					std::cout << "返回主菜单请输入1，返回挑选难度界面请输入2" << endl;
					b = getValidInteger();
					switch (b)
					{
					case 1:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					case 2:
						cState = LEVEL_MENU;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				default:
					std::cout << "无效选择，请重新输入!" << endl;
				}
			}
			break;
		case INFINITE:
			cState = LEVEL_MENU;
			while (cState != OUT)
			{
				clearScreen();
				b = 0;
				cout << "游戏即将开始，请做好准备。" << endl;
				std::this_thread::sleep_for(std::chrono::seconds(2));
				GM.startGame2();
				std::cout << "\n返回主菜单请输入1，重新开始游戏请输入2" << endl;
				b = getValidInteger();
				switch (b)
				{
				case 1:
					cState = OUT;
					currentState = MAIN_MENU;
					break;
				case 2:
					cState = LEVEL_MENU;
					break;
				default:
					std::cout << "无效选择，请重新输入!" << endl;
				}
			}
			break;
		case MINE:
			cState = LEVEL_MENU;
			while (cState != OUT) 
			{
				switch (cState)
				{
				case LEVEL_MENU:
					clearScreen();
					b = 0;
					DataStorage::printPlayerInfo(player);
					std::cout << "\n返回主菜单请输入1，获取玩家建议请输入2" << endl;
					b = getValidInteger();
					switch (b)
					{
					case 1:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					case 2:
						cState = GT;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				case GT:
					ad.clear();
					ad = player.getTrainningAdice();
					cout << endl << ad << endl << endl;
					b = 0;
					std::cout << "\n返回主菜单请输入1，重新输入玩家信息请输入2" << endl;
					b = getValidInteger();
					switch (b)
					{
					case 1:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					case 2:
						cState = LEVEL_MENU;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				}
			}
			break;
		case PRACTICE:
			clearScreen();
			cState = LEVEL_MENU;
			while (cState != OUT)
			{
				switch (cState)
				{
				case LEVEL_MENU:
					clearScreen();
					PracticeMenu();
					pa = false;
					c = 0;
					b = 0;
					c = getValidInteger();
					switch (c)
					{
					case 1:
						cState = EASY;
						break;
					case 2:
						cState = MEDIUM;
						break;
					case 3:
						cState = HARD;
						break;
					case 4:
						cState = EXTREME;
						break;
					case 7:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				case EASY:
					clearScreen();
					GM.startGame1P(Difficulty::EASY);
					pa = GM.getpa();
					GM.endGame1(pa);
					std::cout << "返回主菜单请输入1，返回练习模式菜单请输入2" << endl;
					b = getValidInteger();
					switch (b)
					{
					case 1:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					case 2:
						cState = LEVEL_MENU;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				case MEDIUM:
					clearScreen();
					GM.startGame1P(Difficulty::MEDIUM);
					pa = GM.getpa();
					GM.endGame1(pa);
					std::cout << "返回主菜单请输入1，返回练习模式菜单请输入2" << endl;
					b = getValidInteger();
					switch (b)
					{
					case 1:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					case 2:
						cState = LEVEL_MENU;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				case HARD:
					clearScreen();
					GM.startGame1P(Difficulty::HARD);
					pa = GM.getpa();
					GM.endGame1(pa);
					std::cout << "返回主菜单请输入1，返回练习模式菜单请输入2" << endl;
					b = getValidInteger();
					switch (b)
					{
					case 1:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					case 2:
						cState = LEVEL_MENU;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				case EXTREME:
					clearScreen();
					GM.startGame1P(Difficulty::EXTREME);
					pa = GM.getpa();
					GM.endGame1(pa);
					std::cout << "返回主菜单请输入1，返回练习模式菜单请输入2" << endl;
					b = getValidInteger();
					switch (b)
					{
					case 1:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					case 2:
						cState = LEVEL_MENU;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				default:
					std::cout << "无效选择，请重新输入!" << endl;
				}
			}
			break;
		case RULE:
			clearScreen();
			cState = LEVEL_MENU;
			while (cState != OUT)
			{
				switch (cState)
				{
				case LEVEL_MENU:
					clearScreen();
					ruleMenu();
					pa = false;
					c = 0;
					b = 0;
					c = getValidInteger();
					switch (c)
					{
					case 7:
						cState = OUT;
						currentState = MAIN_MENU;
						break;
					default:
						std::cout << "无效选择，请重新输入!" << endl;
					}
					break;
				default:
					std::cout << "无效选择，请重新输入!" << endl;
				}
			}
			break;
		case EXIT:
			clearScreen();
			currentState = EXIT;
			break;
		default:
			std::cout << "无效选择，请重新输入!" << endl;

		}
	}
	clearScreen();
	std::cout << "游戏已退出！" << endl;
	return 0;
}