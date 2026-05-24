#include "../include/Player.hpp"
#include "../include/map.hpp"

Player::Player(const int x, const int y)
{
    _x = x;
    _y = y;
}

void Player::move(const int dx, const int dy)
{
    _x = _x < 0 ? 0 : _x + dx;
    _y = _y < 0 ? 0 : _y + dy;
}

std::vector<int> Player::where() const
{
    int x = _x;
    int y = _y;
    std::vector<int> _x_y = {x, y};
    return _x_y;
}
