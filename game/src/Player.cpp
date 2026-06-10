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

void Player::to(const int x, const int y)
{
    _x = x;
    _y = y;
}

int Player::x() const
{
    return _x;
}

int Player::y() const
{
    return _y;
}

Player Player::operator=(Player player)
{
    _x = player.x();
    _y = player.y();
}
