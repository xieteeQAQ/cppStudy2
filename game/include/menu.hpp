#pragma once

#include "map.hpp"
#include "maps.hpp"
#include "Player.hpp"

class Menu
{
public:
    Menu() {};
    Menu(std::vector<Map> &Levels);

    void startMenu();
    void startGame(Map &Level) const;
    void startGame(Map &Level, Player &player) const;
    int LevelsCount() const;
    static void gameLoop(Map &Level, std::string &input, std::vector<std::string> &step, std::string &position, bool &flag);
    Map &selectLevel(int number);

private:
    std::vector<Map> _Levels{};
    int _LevelsCount = 0;
};