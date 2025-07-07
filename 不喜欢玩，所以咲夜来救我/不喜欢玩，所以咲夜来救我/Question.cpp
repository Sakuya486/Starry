#include"Xiao.h"

	void Question::createArr3(const int n, const int m)
	{
		arr3.clear();
	FLAG1:
		arr3.clear();
		int x = (std::rand() % m - 2) + 1;
		int y = (std::rand() % m - 2) + 1;
		arr3.emplace_back(x * m + y);
		int num = 0;
		for (int i = 1; i < n; i++)
		{
			int temple = (std::rand() % 3) + 0;
			switch (temple) {
			case 0: arr3.emplace_back(arr3[i - 1] + m); break;
			case 1: arr3.emplace_back(arr3[i - 1] - m); break;
			case 2: arr3.emplace_back(arr3[i - 1] + 1); break;
			case 3: arr3.emplace_back(arr3[i - 1] - 1); break;
			}
			if (arr3[i] <= 0) {
				i--; arr3.pop_back();
			}
			if (arr3[i] > m * m) {
				i--; arr3.pop_back();
			}
			for (int j = 0; j < i; j++)
			{
				if (arr3[i] == arr3[j]) { 
					i--; arr3.pop_back();
				}
			}
			num++;
			if (num > 10 * n) { i = 1; arr3.clear(); goto FLAG1; }
		}
	}

	void Question::createArr2(const int n, const int m, const int nm)
	{
		arr2.clear();
	FLAG2:
		arr2.clear();
		int x = (std::rand() % m - 2) + m / 2;
		int y = (std::rand() % m - 2) + m / 2;
		arr2.emplace_back(x * m + y);
		int num = 0;
		for (int i = 1; i < n; i++)
		{
			int t1 = (std::rand() % 3) + 0;
			int t2 = (std::rand() % nm) + 1;
			switch (t1) {
			case 0: arr2.emplace_back(arr2[i - 1] + t2 * m); break;
			case 1: arr2.emplace_back(arr2[i - 1] - t2 * m); break;
			case 2: arr2.emplace_back(arr2[i - 1] + t2); break;
			case 3: arr2.emplace_back(arr2[i - 1] - t2); break;
			}
			if (arr2[i] <= 0) {
				i--; arr2.pop_back();
			}
			if (arr2[i] > m * m ) {
				i--; arr2.pop_back();
			}
			num++;
			if (num > 10 * n) { i = 1; arr2.clear(); goto FLAG2; }
		}
	}

	void Question::createArr1(const int n,const int m)
	{
		arr1.clear();
		int x = (std::rand() % m - 2) + m / 2;
		int y = (std::rand() % m - 2) + m / 2;
		arr1.emplace_back(x * m + y);
		for (int i = 1; i < n; i++)
		{
			int aa = (arr3[i] - arr3[i - 1]) - (arr2[i] - arr2[i - 1]) + arr1[i - 1];
			arr1.emplace_back(aa);
		}
	}

	bool Question::CheckPath()
	{
		for (int i = 1; i < a1-1; i++)
		{
			if (arr3[i] != arr4[i])
			{
				return false;
			}
		}
		return true;
	}

	bool Question::CheckPath(vector<int> arr3, vector<int> arr4,int N)
	{
		for (int i = 1; i < N - 1; i++)
		{
			if (arr3[i] != arr4[i])
			{
				return false;
			}
		}
		return true;
	}

	void Question::generateQuestion(Difficulty dif)
	{
		int diff = 0;
		switch (dif)
		{
		case Difficulty::EASY:diff = (rand() % 4) + 2; break;
		case Difficulty::MEDIUM:diff = (rand() % 7) + 5; break;
		case Difficulty::HARD:diff = (rand() % 10) + 8; break;
		case Difficulty::EXTREME:diff = (rand() % 13) + 11; break;
		}
		const int n = 2 * diff + 1;
		const int m = 5 * diff;
		const int nm = (rand() % diff) + 2;
		a1 = n;
		a2 = m;
		createArr3(n, m);
		createArr2(n, m, nm);
		createArr1(n, m);
	}

	void Question::generateQuestion(int diff)
	{
		const int n = 2 * diff + 1;
		const int m = 5 * diff;
		const int nm = diff ;
		a1 = n;
		a2 = m;
		createArr3(n, m);
		createArr2(n, m, nm);
		createArr1(n, m);
	}

	void Question::outPath1()
	{
		int h;
		cout << "题目图案：" << endl;
		cout << " A轨迹:\t\t" << " B轨迹：" << "\t||\t A轨迹:\t\t" << " B轨迹：" << endl;
		if (a1 % 2 == 0) {
			h = a1 / 2;
			for (int i = 0; i < a1 / 2; i++)
			{
				if (arr1[i] % a2 == 0) {
					cout << " A" << i + 1 << ".(" << a2 << "," << arr1[i] / a2 << ")" << "\t";
				}
				else {
					cout << " A" << i + 1 << ".(" << arr1[i] % a2 << "," << arr1[i] / a2 << ")" << "\t";
				}
				if (arr2[i] % a2 == 0) {
					cout << " B" << i + 1 << ".(" << a2 << "," << arr2[i] / a2 << ")" << "\t||\t";
				}
				else {
					cout << " B" << i + 1 << ".(" << arr2[i] % a2 << "," << arr2[i] / a2 << ")" << "\t||\t";
				}
				if (arr1[i + h] % a2 == 0) {
					cout << " A" << i + h + 1 << ".(" << a2 << "," << arr1[i + h] / a2 << ")" << "\t";
				}
				else {
					cout << " A" << i + h + 1 << ".(" << arr1[i + h] % a2 << "," << arr1[i + h] / a2 << ")" << "\t";
				}
				if (arr2[i + h] % a2 == 0) {
					cout << " B" << i + h + 1 << ".(" << a2 << "," << arr2[i + h] / a2 << ")" << endl;
				}
				else {
					cout << " B" << i + h + 1 << ".(" << arr2[i + h] % a2 << "," << arr2[i + h] / a2 << ")" << endl;
				}
				if (i % 2 == 0 && i == a1 / 2 - 1) {
					cout << endl;
				}
			}
		}
		else
		{
			h = a1 / 2 + 1;
			for (int i = 0; i < a1 / 2 + 1; i++)
			{
				if (arr1[i] % a2 == 0) {
					cout << " A" << i + 1 << ".(" << a2 << "," << arr1[i] / a2 << ")" << "\t";
				}
				else {
					cout << " A" << i + 1 << ".(" << arr1[i] % a2 << "," << arr1[i] / a2 << ")" << "\t";
				}
				if (arr2[i] % a2 == 0) {
					cout << " B" << i + 1 << ".(" << a2 << "," << arr2[i] / a2 << ")" << "\t||\t";
				}
				else {
					cout << " B" << i + 1 << ".(" << arr2[i] % a2 << "," << arr2[i] / a2 << ")" << "\t||\t";
				}
				if (i != a1 / 2) {
					if (arr1[i + h] % a2 == 0) {
						cout << " A" << i + h + 1 << ".(" << a2 << "," << arr1[i + h] / a2 << ")" << "\t";
					}
					else {
						cout << " A" << i + h + 1 << ".(" << arr1[i + h] % a2 << "," << arr1[i + h] / a2 << ")" << "\t";
					}
					if (arr2[i + h] % a2 == 0) {
						cout << " B" << i + h + 1 << ".(" << a2 << "," << arr2[i + h] / a2 << ")" << endl;
					}
					else {
						cout << " B" << i + h + 1 << ".(" << arr2[i + h] % a2 << "," << arr2[i + h] / a2 << ")" << endl;
					}
				}
				if (i == a1 / 2) {
					cout << endl;
				}
			}
		}
		cout << endl;
		std::cout << "C 轨迹首元素: " << "(" << arr3.front() % a2 << "," << arr3.front() / a2 << ")" << endl;
		std::cout << "C 轨迹尾元素: " << "(" << arr3.back() % a2 << "," << arr3.back() / a2 << ")" << endl;
		cout << "(同时输入x,y为0以重新输入上一个点的坐标)" << endl << endl;
	}

	void Question::outPath2()
	{
		int h;
		cout << "题目图案：" << endl;
		cout << " A轨迹:\t\t" << " B轨迹：" << "\t||\t A轨迹:\t\t" << " B轨迹：" << endl;
		if (a1 % 2 == 0) {
			h = a1 / 2;
			for (int i = 0; i < a1 / 2 ; i++)
			{
				if (arr1[i] % a2 == 0) {
					cout << " A" << i + 1 << ".(" << a2 << "," << arr1[i] / a2 << ")" << "\t";
				}
				else {
					cout << " A" << i + 1 << ".(" << arr1[i] % a2 << "," << arr1[i] / a2 << ")" << "\t";
				}
				if (arr2[i] % a2 == 0) {
					cout << " B" << i + 1 << ".(" << a2 << "," << arr2[i] / a2 << ")" << "\t||\t";
				}
				else {
					cout << " B" << i + 1 << ".(" << arr2[i] % a2 << "," << arr2[i] / a2 << ")" << "\t||\t";
				}
				if (arr1[i + h] % a2 == 0) {
					cout << " A" << i + h + 1 << ".(" << a2 << "," << arr1[i + h] / a2 << ")" << "\t";
				}
				else {
					cout << " A" << i + h + 1 << ".(" << arr1[i + h] % a2 << "," << arr1[i + h] / a2 << ")" << "\t";
				}
				if (arr2[i + h] % a2 == 0) {
					cout << " B" << i + h + 1 << ".(" << a2 << "," << arr2[i + h] / a2 << ")" << endl;
				}
				else {
					cout << " B" << i + h + 1 << ".(" << arr2[i + h] % a2 << "," << arr2[i + h] / a2 << ")" << endl;
				}
				if (i % 2 == 0 && i == a1 / 2 - 1) {
					cout << endl;
				}
			}
		}
		else
		{
			h = a1 / 2 + 1;
			for (int i = 0; i < a1 / 2 + 1; i++)
			{
				if (arr1[i] % a2 == 0) {
					cout << " A" << i + 1 << ".(" << a2 << "," << arr1[i] / a2 << ")" << "\t";
				}
				else {
					cout << " A" << i + 1 << ".(" << arr1[i] % a2 << "," << arr1[i] / a2 << ")" << "\t";
				}
				if (arr2[i] % a2 == 0) {
					cout << " B" << i + 1 << ".(" << a2 << "," << arr2[i] / a2 << ")" << "\t||\t";
				}
				else {
					cout << " B" << i + 1 << ".(" << arr2[i] % a2 << "," << arr2[i] / a2 << ")" << "\t||\t";
				}
				if (i != a1 / 2) {
					if (arr1[i + h] % a2 == 0) {
						cout << " A" << i + h + 1 << ".(" << a2 << "," << arr1[i + h] / a2 << ")" << "\t";
					}
					else {
						cout << " A" << i + h + 1 << ".(" << arr1[i + h] % a2 << "," << arr1[i + h] / a2 << ")" << "\t";
					}
					if (arr2[i + h] % a2 == 0) {
						cout << " B" << i + h + 1 << ".(" << a2 << "," << arr2[i + h] / a2 << ")" << endl;
					}
					else {
						cout << " B" << i + h + 1 << ".(" << arr2[i + h] % a2 << "," << arr2[i + h] / a2 << ")" << endl;
					}
				}
				if (i == a1 / 2) {
					cout << endl;
				}
			}
		}
		cout << endl;
		std::cout << "C 轨迹首元素: " << "(" << arr3.front() % a2 << "," << arr3.front() / a2 << ")" << endl;
		std::cout << "C 轨迹尾元素: " << "(" << arr3.back() % a2 << "," << arr3.back() / a2 << ")" << endl;
		cout << "(同时输入x,y为0以重新输入上一个点的坐标)" << endl << endl;
		for (size_t i = 0; i < arr1.size(); ++i) {
			std::cout << "C" << i + 1 << ":(" << arr3[i] % a2 << "," << arr3[i] / a2 << ")";
			if ((i + 1) % 5 == 0) {
				cout << endl;
			}
			else {
				cout << "\t";
			}
		}
		cout << endl << endl;
	}

	void Question::inPath()
	{
		arr4.clear();
		arr4.emplace_back(0);
		for (int i = 1; i < a1 - 1; i++)
		{
			int x, y;
			// 循环直到获取有效输入
			while (true) {
				std::cout << "C" << i + 1 << "x坐标:";
				if (!(std::cin >> x)) {
					std::cout << "错误：请输入有效的整数！" << std::endl;
					std::cin.clear(); // 清除错误标志
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略缓冲区中的错误输入
					continue;
				}
				std::cout << "C" << i + 1 << "y坐标:";
				if (!(std::cin >> y)) {
					std::cout << "错误：请输入有效的整数！" << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				// 清除输入缓冲区中的多余字符
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				break; // 输入有效，退出循环
			}
			// 检查是否需要撤销前一个点
			if (i >= 2 && x == 0 && y == 0) {
				if (arr4.size() > 1) {
					arr4.pop_back(); // 移除最后一个添加的点
					i -= 2; // 回退两个步骤
					std::cout << "已撤销上一个点，继续输入C" << i + 2 << "坐标..." << std::endl;
				}
				else {
					std::cout << "错误：无法撤销第一个点！" << std::endl;
					i--; // 保持当前步骤
				}
				continue;
			}
			// 存储转换后的坐标
			arr4.emplace_back(x + y * a2);
		}
	}

	void Question::inPath1(int aa,int bb)
	{
		arr4.clear();
		arr4.emplace_back(0);
		for (int i = 1; i < aa - 1; i++)
		{
			int x, y;
			// 输入验证
			while (true) {
				std::cout << "C" << i + 1 << "的x坐标:";
				if (!(std::cin >> x)) {
					std::cout << "错误：请输入有效的整数！" << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				std::cout << "C" << i + 1 << "的y坐标:";
				if (!(std::cin >> y)) {
					std::cout << "错误：请输入有效的整数！" << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				break;
			}
			// 撤销机制
			if (i >= 2 && x == 0 && y == 0) {
				if (arr4.size() > 1) {
					arr4.pop_back();
					i -= 2;
					std::cout << "已撤销上一个点，继续输入C" << i + 2 << "坐标..." << std::endl;
				}
				else {
					std::cout << "错误：无法撤销第一个点！" << std::endl;
					i--;
				}
				continue;
			}
			arr4.emplace_back(x + y * bb);
		}
	}

	int Question::getN(){return a1;}
	int Question::getM() { return a2; }
	Difficulty Question::getDifficulty() const { return difficulty; }
	const std::vector<int>& Question::getArr4() const { return arr4; }