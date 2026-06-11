#include <algorithm>
#include "../include/map.hpp"

const std::string P = "@ ";
const std::string F = ". ";
const std::string W = "■ ";
const std::string B = "□ ";
const std::string S = "⭑ ";
const std::string FINISH = "☑ ";

const std::string UP = "UP";
const std::string RIGHT = "RIGHT";
const std::string DOWN = "DOWN";
const std::string LEFT = "LEFT";
const std::string QUIT = "QUIT";

const std::string COM_P = "COM_P";
const std::string COM_B = "COM_B";
const std::string WIN = "WIN";

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

    for (int c = 0; c < _columns; ++c)
    {
        for (int r = 0; r < _rows; ++r)
        {
            if (initMap[c][r] == P)
                _player.to(r, c);
            else if (initMap[c][r] == S)
                _star = {r, c};
        }
    }

    _map = initMap;
}

Map::Map(const mv &initMap)
{
    if (initMap.empty())
        return;
    _columns = initMap.size();
    std::vector<int> allRows{};

    for (auto &c : initMap)
    {
        allRows.push_back(c.size());
    }
    _rows = *std::max_element(allRows.begin(), allRows.end());

    for (int c = 0; c < _columns; ++c)
    {
        for (int r = 0; r < _rows; ++r)
        {
            if (initMap[c][r] == P)
                _player.to(r, c);
            else if (initMap[c][r] == S)
                _star = {r, c};
        }
    }

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

void Map::refresh()
{
    for (size_t c = 0; c < _map.size(); ++c)
    {
        for (size_t r = 0; r < _map.at(c).size(); ++r)
        {
            std::string &str = _map.at(c).at(r);
            if (r == _star[0] && c == _star[1])
            {
                if (_map[c][r] == FINISH)
                    continue;
                else
                    str = S;
            }
            if (r == _player.x() && c == _player.y())
            {
                str = P;
            }
            else if (str != W && str != B && str != S)
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

std::string Map::at(const int x, const int y) const
{
    return _map.at(y).at(x);
}

void Map::executeAnalyse(std::vector<std::string> &res, std::string &key, mv &copy_map, int &x, int &y) const
{
    int dx = 0;
    int dy = 0;
    if (key == UP)
        dy = -1;
    else if (key == LEFT)
        dx = -1;
    else if (key == DOWN)
        dy = 1;
    else if (key == RIGHT)
        dx = 1;

    auto Boundary_determination = [=]()
    {
        if (key == UP)
        {
            if (y != 1)
                return true;
            else
                return false;
        }
        else if (key == LEFT)
        {
            if (x != 1)
                return true;
            else
                return false;
        }
        else if (key == DOWN)
        {
            if (y != _columns - 2)
                return true;
            else
                return false;
        }
        else if (key == RIGHT)
        {
            if (x != _rows - 2)
                return true;
            else
                return false;
        }
        else
            return false;
    };

    std::string &next = copy_map.at(y + dy).at(x + dx);
    if (next == F || next == S)
    {
        y += dy;
        x += dx;
        res.push_back(COM_P);
        res.push_back(key);
    }
    else if (next == B && Boundary_determination() && (copy_map.at(y + 2 * dy).at(x + 2 * dx) != W && copy_map.at(y + 2 * dy).at(x + 2 * dx) != FINISH))
    {
        std::string &nex_next = copy_map.at(y + 2 * dy).at(x + 2 * dx);

        if (nex_next == S)
        {
            next = F;
            nex_next = FINISH;
        }
        else
        {
            next = F;
            nex_next = B;
        }
        res.push_back(COM_B);
        res.push_back(key);
        res.push_back(COM_P);
        res.push_back(key);
        if (nex_next == FINISH)
            res.push_back(WIN);
        y += dy;
        x += dx;
    }
}

std::vector<std::string> Map::keyAnalyse(std::string &keys) const
{
    std::vector<std::string> result{};
    mv copy_map(_map);
    int x = _player.x();
    int y = _player.y();
    copy_map.at(y).at(x) = F;
    for (const auto &c : keys)
    {
        switch (c)
        {
        case 'w':
            if (y != 0)
            {
                std::string key = UP;
                executeAnalyse(result, key, copy_map, x, y);
            }
            break;
        case 'a':
            if (x != 0)
            {
                std::string key = LEFT;
                executeAnalyse(result, key, copy_map, x, y);
            }
            break;
        case 's':
            if (y != _columns - 1)
            {
                std::string key = DOWN;
                executeAnalyse(result, key, copy_map, x, y);
            }
            break;
        case 'd':
            if (x != _rows - 1)
            {
                std::string key = RIGHT;
                executeAnalyse(result, key, copy_map, x, y);
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

    if (_map.at(y + dy + (dy > 0) - (dy < 0)).at(x + dx + (dx > 0) - (dx < 0)) == S)
    {
        _map.at(y + dy).at(x + dx) = F;
        _map.at(y + dy + (dy > 0) - (dy < 0)).at(x + dx + (dx > 0) - (dx < 0)) = FINISH;
    }
    else
    {
        _map.at(y + dy).at(x + dx) = F;
        _map.at(y + dy + (dy > 0) - (dy < 0)).at(x + dx + (dx > 0) - (dx < 0)) = B;
    }
}
