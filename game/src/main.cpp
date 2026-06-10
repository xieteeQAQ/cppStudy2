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
    menu.startGame(Level_1);

    return 0;
}