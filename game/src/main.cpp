#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <unistd.h>
#include "../include/menu.hpp"
#include "../include/map.hpp"
#include "../include/maps.hpp"
#include "../include/Player.hpp"

int main()
{
    std::string input{};
    // 在运行时初始化关卡，避免在文件作用域出现裸函数调用
    Map::generateMaps("Level_1", Level_1_init, Levels);
    Map::generateMaps("Level_2", Level_2_init, Levels);
    Map::generateMaps("Level_3", Level_3_init, Levels);
    Map::generateMaps("Level_4", Level_4_init, Levels);
    Map::generateMaps("Level_5", Level_5_init, Levels);
    Menu menu(Levels);

    std::cout << "这里的输入用于暂停程序保留编译信息,请按输入任意内容继续\n";
    std::cin >> input;

    system("clear");
    menu.startMenu();

    return 0;
}