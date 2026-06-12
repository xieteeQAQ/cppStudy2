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
    void to(const int x, const int y);
    int x() const;
    int y() const;

    void operator=(Player player);

private:
    int _x = 0;
    int _y = 0;
};