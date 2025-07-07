#include"Xiao.h"

int getValidInteger() {
    int value;
    while (true) {
        if (std::cin >> value) {
            // 成功读取整数后，清除缓冲区剩余内容
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        else {
            // 输入无效时，重置流状态并清除缓冲区
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入无效，请重新输入一个整数: " << endl;
        }
    }
}