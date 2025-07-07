#include"Xiao.h"

void MainMenu()
{
	cout << "================" << endl;
	cout << "    脑力航迹    " << endl;
	cout << "================" << endl;
	cout << "1.关卡模式" << endl;
	cout << "2.难度模式" << endl;
	cout << "3.无限模式" << endl;
	cout << "4.我的" << endl;
	cout << "5.练习模式" << endl;
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
	cout << "（此处输入7以返回主菜单）\n" << endl;
}

void DDMenu()
{
	cout << "================" << endl;
	cout << "    难度模式    " << endl;
	cout << "================" << endl;
	cout << "1.简单" << endl;
	cout << "2.中等" << endl;
	cout << "3.困难" << endl;
	cout << "4.极限" << endl;
	cout << "（此处输入7以返回主菜单）\n" << endl;
}

void PracticeMenu()
{
	cout << "================" << endl;
	cout << "    练习模式    " << endl;
	cout << "================" << endl;
	cout << "1.简单" << endl;
	cout << "2.中等" << endl;
	cout << "3.困难" << endl;
	cout << "4.极限" << endl;
	cout << "（此处输入7以返回主菜单）\n" << endl;
}

void ruleMenu()
{
	cout << "1.在所有模式中都是输入模式前的数字以进入相应的程序\n" << endl;
	cout << "2.关卡中A、B为实际轨迹，C为B对A的相对轨迹，题目会给出A、B的轨迹坐标和\nC轨迹的首末轨迹坐标，"
		"目标是求出C其他轨迹坐标\n" << endl;
	cout << "3.在答题过程中输入x，y同时为0以重新输入上一个数据\n" << endl;
	cout << "4.关卡模式和难度模式无时间限制，请放心大胆尝试!\n" << endl;
	cout << "5.无限模式存在倒计时，初始为120s，每过一关增加60s，考虑到刷屏问题，\n倒计时约10s显示一次，"
		"关卡难度增幅随机（在适当范围内），关卡与关卡之间\n存在5s时间进行休息，最终得分与通关数和关卡难度挂钩\n" << endl;
	cout << "6.难度模式未通过将不会录入时间成绩\n" << endl;
	cout << "7.每个模式在输出题面前一般都有2s时间供玩家获取题目基本信息或者做好调整\n" << endl;
	cout << "8.无限模式在倒计时结束后仍可进行输入，但这不会计入成绩，可快速输完以结束模式\n" << endl;
	cout << "（此处输入7以返回主菜单）\n" << endl;
	//未完待续
}