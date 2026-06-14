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

    Menu::initLevels();
    Menu menu(Levels);

    std::cout << "这里的输入用于暂停程序保留编译信息,请按输入任意内容继续\n";
    std::cin >> input;

    system("clear");
    menu.startMenu();

    return 0;
}