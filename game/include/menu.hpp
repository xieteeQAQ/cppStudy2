#pragma once

#include "map.hpp"
#include "maps.hpp"
#include "Player.hpp"

class Menu
{
public:
    Menu() {};

    void startGame(Map &Level) const;
    void startGame(Map &Level, Player &player) const;
    static void gameLoop(Map &Level, std::string &input, std::vector<std::string> &step, std::string &position, bool &flag);

private:
    std::vector<Map> _Level = {Level_1};
};