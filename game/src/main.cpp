#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "../include/menu.hpp"
#include "../include/map.hpp"
#include "../include/maps.hpp"
#include "../include/Player.hpp"


int main()
{
    Menu menu{};
    for (auto &m : Levels)
    {
        menu.startGame(m);
        std::cout << "按任意键继续...\n";
        char c{};
        std::cin >> c;
    }

    return 0;
}