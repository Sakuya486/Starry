#include"Xiao.h"

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

	void createArr2(const int n, const int m, const int nm)
	{
		arr2.resize(n);
	FLAG2:
		int x = (std::rand() % m - 2) + m / 2;
		int y = (std::rand() % m - 2) + m / 2;
		arr2[0] = x * m + y;
		int num = 0;
		for (int i = 1; i < n; i++)
		{
			int t1 = (std::rand() % 3) + 0;
			int t2 = (std::rand() % nm) + 1;
			switch (t1) {
			case 0: arr2[i] += t2 * m; break;
			case 1: arr2[i] -= t2 * m; break;
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
		const int nm = diff / 3;
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
		const int nm = diff ;
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
			cout << "A" << i + 1 << ".(" << arr1[i] % a2 << "," << arr1[i] / a2 << ")" << "\t" << "B" << i + 1 << ".(" << arr2[i] % a2 << "," << arr2[i] / a2 << ")" << endl;
		}
		cout << "相对轨迹可见点：" << "C1:" << arr3[0] << "    " << "C" << a1 << ":" << arr3[a1 - 1] << endl;
	}

	void inPath()
	{
	FLAG:
		for (int i = 1; i < a1 - 1; i++)
		{
			int x, y;
			cout << "C" << i + 1 << "x坐标:";
			cin >> x;
			cout << "C" << i + 1 << "y坐标:";
			cin >> y;
			arr4[i] = x + y * a2;
			if (i >= 2 && x == 0 && y == 0)//输入x，y为零以重新输入数据
			{
				i--;
				i--;
			}
		}
		if (!CheckPath())
		{
			cout << "输入错误，已重置相对路径！" << endl << "请重新输入C路径" << endl;
			goto FLAG;
		}
	}

	void inPath1()
	{
		for (int i = 1; i < a1 - 1; i++)
		{
			int x, y;
			cout << "C" << i + 1 << "x坐标:";
			cin >> x;
			cout << "C" << i + 1 << "y坐标:";
			cin >> y;
			arr4[i] = x + y * a2;
			if (i >= 2 && x == 0 && y == 0)//输入x，y为零以重新输入数据
			{
				i--;
				i--;
			}
		}
	}

	int getN(){return a1;}
	Difficulty getDifficulty() const { return difficulty; }
};