#include <algorithm>
#include "../include/map.hpp"

const std::string F = ". ";

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
            if (r == _player.where()[0] && c == _player.where()[1])
                _map.at(c).at(r) = "@ ";
            else
                _map.at(c).at(r) = ". ";
        }
    }
}

void Map::show()
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
    int x = _player.where()[0] + dx;
    int y = _player.where()[1] + dy;
    if (x < 0 || x > _rows - 1)
        return;
    else
        _player.move(dx, 0);
    if (y < 0 || y > _columns - 1)
        return;
    else
        _player.move(0, dy);
}

Player &Map::player()
{
    return this->_player;
}

int &Map::rows()
{
    return this->_rows;
}
int &Map::cols()
{
    return this->_columns;
}
mv &Map::map()
{
    return this->_map;
}

void Map::inPlayer(Player &player)
{
    _player = player;
}
