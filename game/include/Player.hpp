#pragma once

#include <iostream>
#include <vector>
#include <string>

class Player
{
public:
    Player() {};
    explicit Player(const int x, const int y);

    void move(const int dx, const int dy);
    std::vector<int> where() const;

private:
    int _x = 0;
    int _y = 0;
};