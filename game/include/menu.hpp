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
private:
    std::vector<Map> _Level = {Level_1};
};