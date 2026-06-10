#include <algorithm>
#include "../include/map.hpp"

const std::string P = "@ ";
const std::string F = ". ";
const std::string W = "■ ";
const std::string B = "□ ";

const std::string UP = "UP";
const std::string RIGHT = "RIGHT";
const std::string DOWN = "DOWN";
const std::string LEFT = "LEFT";
const std::string QUIT = "QUIT";

const std::string COM_P = "COM_P";
const std::string COM_B = "COM_B";

using mv = std::vector<std::vector<std::string>>;

Map::Map(const int &rows, const int &cols)
{
    _rows = rows;
    _columns = cols;
    for (int i = 0; i < _columns; ++i)
    {
        std::vector<std::string> c{};
        _map.push_back(c);
    }
    for (auto &c : _map)
    {
        while (c.size() < _rows)
        {
            c.push_back("? ");
        }
    }
}

Map::Map(const std::string &mapName, const int &rows, const int &cols)
{
    _mapName = mapName;
    _rows = rows;
    _columns = cols;
    for (int i = 0; i < _columns; ++i)
    {
        std::vector<std::string> c{};
        _map.push_back(c);
    }
    for (auto &c : _map)
    {
        while (c.size() < _rows)
        {
            c.push_back("? ");
        }
    }
}

Map::Map(const std::string &mapName, const int &rows, const int &cols, const mv &initMap)
{
    _mapName = mapName;
    _rows = rows;
    _columns = cols;
    for (int i = 0; i < _columns; ++i)
    {
        std::vector<std::string> c{};
        _map.push_back(c);
    }
    for (auto &c : _map)
    {
        while (c.size() < _rows)
        {
            c.push_back("? ");
        }
    }
    this->init(initMap);
}
Map::Map(const std::string &mapName, const mv &initMap)
{
    if (initMap.empty())
        return;
    _mapName = mapName;
    _columns = initMap.size();
    std::vector<int> allRows{};
    for (auto &c : initMap)
    {
        allRows.push_back(c.size());
    }
    _rows = *std::max_element(allRows.begin(), allRows.end());
    _map = initMap;
}

void Map::setMapSize(const int &rows, const int &cols)
{
    if (_map.empty())
    {
        _rows = rows;
        _columns = cols;
        for (int i = 0; i < _columns; ++i)
        {
            std::vector<std::string> c{};
            _map.push_back(c);
        }
        for (auto &c : _map)
        {
            while (c.size() < _rows)
            {
                c.push_back("? ");
            }
        }
    }
    else
    {
        while (_map.size() > cols)
        {
            _map.pop_back();
        }
        _columns = cols;

        for (auto &c : _map)
        {
            while (c.size() > rows)
            {
                c.pop_back();
            }
        }
        _rows = rows;
    }
}

void Map::init(const mv &initMap)
{
    if (initMap.empty())
        return;
    size_t initc = 0;
    for (auto &c : _map)
    {
        if (initc < initMap.size())
        {
            size_t initr = 0;
            for (auto &r : c)
            {
                if (initr < initMap.at(initc).size())
                    r = initMap.at(initc).at(initr);
                ++initr;
            }
        }
        ++initc;
    }
}

void Map::refresh()
{
    for (size_t c = 0; c < _map.size(); ++c)
    {
        for (size_t r = 0; r < _map.at(c).size(); ++r)
        {
            std::string &str = _map.at(c).at(r);
            if (r == _player.x() && c == _player.y())
                str = "@ ";
            else if (str != W && str != B)
                str = F;
        }
    }
}

void Map::show() const
{
    if (_map.empty())
    {
        std::cout << "WARN | Map <" << _mapName << "> empty\n";
    }
    else
    {
        for (const auto &c : _map)
        {
            for (const auto &r : c)
            {
                if (r.empty())
                    std::cout << "? ";
                else
                    std::cout << r;
            }
            std::cout << "\n";
        }
    }
}

void Map::movePlayer(const int dx, const int dy)
{
    int x = _player.x() + dx;
    int y = _player.y() + dy;
    if (x < 0 || x > _rows - 1)
        return;
    else
        _player.move(dx, 0);
    if (y < 0 || y > _columns - 1)
        return;
    else
        _player.move(0, dy);
}

Player Map::player() const
{
    return _player;
}

int Map::rows() const
{
    return this->_rows;
}
int Map::cols() const
{
    return this->_columns;
}
mv Map::map() const
{
    return this->_map;
}

void Map::inPlayer(Player &player)
{
    _player = player;
}

std::vector<std::string> Map::keyAnalyse(std::string &keys) const
{
    std::vector<std::string> result{};
    std::string flag{};
    int x = _player.x();
    int y = _player.y();
    for (const auto &c : keys)
    {
        switch (c)
        {
        case 'w':
            if (y != 0)
            {
                std::string up = _map.at(y - 1).at(x);
                if (up == F)
                {
                    --y;
                    if (flag == B || flag.empty())
                    {
                        flag = P;
                        result.push_back(COM_P);
                    }
                    result.push_back(UP);
                }
                else if (up == B && y != 1 && _map.at(y - 2).at(x) != W)
                {
                    --y;
                    if (flag == P || flag.empty())
                    {
                        flag = B;
                        result.push_back(COM_B);
                    }
                    result.push_back(UP);
                    if (flag == B || flag.empty())
                    {
                        flag = P;
                        result.push_back(COM_P);
                    }
                    result.push_back(UP);
                }
            }
            break;
        case 'a':
            if (x != 0)
            {
                std::string left = _map.at(y).at(x - 1);
                if (left == F)
                {
                    --x;
                    if (flag == B || flag.empty())
                    {
                        flag = P;
                        result.push_back(COM_P);
                    }
                    result.push_back(LEFT);
                }
                else if (left == B && x != 1 && _map.at(y).at(x - 2) != W)
                {
                    --x;
                    if (flag == P || flag.empty())
                    {
                        flag = B;
                        result.push_back(COM_B);
                    }
                    result.push_back(LEFT);
                    if (flag == B || flag.empty())
                    {
                        flag = P;
                        result.push_back(COM_P);
                    }
                    result.push_back(LEFT);
                }
            }
            break;
        case 's':
            if (y != _columns - 1)
            {
                std::string down = _map.at(y + 1).at(x);
                if (down == F)
                {
                    ++y;
                    if (flag == B || flag.empty())
                    {
                        flag = P;
                        result.push_back(COM_P);
                    }
                    result.push_back(DOWN);
                }
                else if (down == B && y != _columns - 2 && _map.at(y + 2).at(x) != W)
                {
                    ++y;
                    if (flag == P || flag.empty())
                    {
                        flag = B;
                        result.push_back(COM_B);
                    }
                    result.push_back(DOWN);
                    if (flag == B || flag.empty())
                    {
                        flag = P;
                        result.push_back(COM_P);
                    }
                    result.push_back(DOWN);
                }
            }
            break;
        case 'd':
            if (x != _rows - 1)
            {
                std::string right = _map.at(y).at(x + 1);
                if (right == F)
                {
                    ++x;
                    if (flag == B || flag.empty())
                    {
                        flag = P;
                        result.push_back(COM_P);
                    }
                    result.push_back(RIGHT);
                }
                else if (right == B && x != _rows - 2 && _map.at(y).at(x + 2) != W)
                {
                    ++x;
                    if (flag == P || flag.empty())
                    {
                        flag = B;
                        result.push_back(COM_B);
                    }
                    result.push_back(RIGHT);
                    if (flag == B || flag.empty())
                    {
                        flag = P;
                        result.push_back(COM_P);
                    }
                    result.push_back(RIGHT);
                }
            }
            break;
        case 'q':
            result.push_back(QUIT);
            break;
        default:
            break;
        }
    }

    return result;
}

void Map::setPlayerPosition(const int x, const int y)
{
    _player.to(x, y);
}

void Map::moveBox(const int dx, const int dy)
{
    int x = _player.x();
    int y = _player.y();
    if (x + dx < 0 || x + dx > _rows - 1 || x + dx + (dx > 0) - (dx < 0) > _rows - 1)
        return;
    else if (y + dy < 0 || y + dy > _columns - 1 || y + dy + (dy > 0) - (dy < 0) > _columns - 1)
        return;
    _map.at(y + dy).at(x + dx) = F;
    _map.at(y + dy + (dy > 0) - (dy < 0)).at(x + dx + (dx > 0) - (dx < 0)) = B;
}
