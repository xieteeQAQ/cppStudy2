#include <algorithm>
#include "../include/map.hpp"

// Internal tokens (ASCII) used for game logic — stable across platforms
const std::string P = "P";
const std::string F = "F";
const std::string W = "W";
const std::string B = "B";
const std::string S = "S";
const std::string FINISH = "FIN";

// Display glyphs (may be UTF-8). Console/font support varies by platform.
const std::string DISP_P = "@ ";
const std::string DISP_F = ". ";
#ifdef _WIN32
const std::string DISP_W = "# ";
const std::string DISP_B = "[]";
const std::string DISP_S = "* ";
const std::string DISP_FINISH = "[X]";
#else
const std::string DISP_W = u8"■ ";
const std::string DISP_B = u8"□ ";
const std::string DISP_S = u8"⭑ ";
const std::string DISP_FINISH = u8"☑ ";
#endif

const std::string UP = "UP";
const std::string RIGHT = "RIGHT";
const std::string DOWN = "DOWN";
const std::string LEFT = "LEFT";
const std::string QUIT = "QUIT";
const std::string RESTART = "RESTART";

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
    _init_map = _map;
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
    _init_map = _map;
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
            {
                _orign_x = r;
                _orign_y = c;
                _player.to(r, c);
            }
            else if (initMap[c][r] == S)
                _star = {r, c};
        }
    }

    _map = initMap;
    _init_map = initMap;
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
            {
                _orign_x = r;
                _orign_y = c;
                _player.to(r, c);
            }
            else if (initMap[c][r] == S)
                _star = {r, c};
        }
    }

    _map = initMap;
    _init_map = initMap;
}

void Map::reInit()
{
    if (_init_map.empty())
        std::clog << "地图初始化失败!\n";
    else
    {
        _player.to(_orign_x, _orign_y);
        _map = _init_map;
    }
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
                else if (r == P)
                    std::cout << DISP_P;
                else if (r == F)
                    std::cout << DISP_F;
                else if (r == W)
                    std::cout << DISP_W;
                else if (r == B)
                    std::cout << DISP_B;
                else if (r == S)
                    std::cout << DISP_S;
                else if (r == FINISH)
                    std::cout << DISP_FINISH;
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
    else if (next == B && Boundary_determination())
    {
        std::string &nex_next = copy_map.at(y + 2 * dy).at(x + 2 * dx);
        if (nex_next == W && nex_next == FINISH)
            return;

        else if (nex_next == S)
        {
            next = F;
            nex_next = FINISH;
        }
        else if (nex_next == B)
        {
            int check_x = x + 3 * dx, check_y = y + 3 * dy;
            bool x_boundary = check_x >= 0 && check_x <= _rows - 1;
            bool y_boundary = check_y >= 0 && check_y <= _columns - 1;
            if (!(x_boundary && y_boundary))
                return;
            while (x_boundary && y_boundary)
            {
                std::string &now = copy_map.at(check_y).at(check_x);
                if (now == B)
                {
                    check_x += dx;
                    check_y += dy;
                    x_boundary = check_x >= 0 && check_x <= _rows - 1;
                    y_boundary = check_y >= 0 && check_y <= _columns - 1;
                    if (!(x_boundary && y_boundary))
                        return;
                    else
                        continue;
                }
                else if (now == S)
                {
                    now = FINISH;
                    next = F;
                    break;
                }
                else if (now == F)
                {
                    now = B;
                    next = F;
                    break;
                }
                else if (now == W || now == FINISH)
                    return;
                else
                    return;
            }
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
        case 'r':
            result.push_back(RESTART);
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
    int next_x = x + dx;
    int next_y = y + dy;
    int nex_next_x = x + dx + (dx > 0) - (dx < 0);
    int nex_next_y = y + dy + (dy > 0) - (dy < 0);

    if (next_x < 0 || next_x > _rows - 1 || nex_next_x < 0 || nex_next_x > _rows - 1)
        return;
    else if (next_y < 0 || next_y > _columns - 1 || nex_next_y < 0 || nex_next_y > _columns - 1)
        return;

    std::string &self = _map.at(y).at(x);
    std::string &next = _map.at(y + dy).at(x + dx);
    std::string &nex_next = _map.at(y + dy + (dy > 0) - (dy < 0)).at(x + dx + (dx > 0) - (dx < 0));

    if (self == P)
    {
        if (nex_next == F)
        {
            next = F;
            nex_next = B;
        }
        else if (nex_next == S)
        {
            next = F;
            nex_next = FINISH;
        }
        else if (nex_next == B)
        {
            moveBox((dx > 0) - (dx < 0), (dy > 0) - (dy < 0), next_x, next_y);
        }
    }
    else if (self == B)
    {
        if (nex_next == F)
        {
            self = F;
            nex_next = B;
        }
        else if (nex_next == S)
        {
            self = F;
            nex_next = FINISH;
        }
        else if (nex_next == B)
        {
            moveBox((dx > 0) - (dx < 0), (dy > 0) - (dy < 0), next_x, next_y);
            if (next == F)
            {
                next = B;
                self = F;
            }
        }
    }
}

void Map::moveBox(const int dx, const int dy, const int x, const int y)
{
    int next_x = x + dx;
    int next_y = y + dy;
    int nex_next_x = x + dx + (dx > 0) - (dx < 0);
    int nex_next_y = x + dy + (dy > 0) - (dy < 0);

    if (next_x < 0 || next_x > _rows - 1 || nex_next_x < 0 || nex_next_x > _rows - 1)
        return;
    else if (next_y < 0 || next_y > _columns - 1 || nex_next_y < 0 || nex_next_y > _columns - 1)
        return;

    std::string &self = _map.at(y).at(x);
    std::string &next = _map.at(y + dy).at(x + dx);
    std::string &nex_next = _map.at(y + dy + (dy > 0) - (dy < 0)).at(x + dx + (dx > 0) - (dx < 0));

    if (self == P)
    {
        if (nex_next == F)
        {
            next = F;
            nex_next = B;
        }
        else if (nex_next == S)
        {
            next = F;
            nex_next = FINISH;
        }
        else if (nex_next == B)
        {
            moveBox((dx > 0) - (dx < 0), (dy > 0) - (dy < 0), next_x, next_y);
        }
    }
    else if (self == B)
    {
        if (nex_next == F)
        {
            self = F;
            nex_next = B;
        }
        else if (nex_next == S)
        {
            self = F;
            nex_next = FINISH;
        }
        else if (nex_next == B)
        {
            moveBox((dx > 0) - (dx < 0), (dy > 0) - (dy < 0), next_x, next_y);
            if (next == F)
            {
                next = B;
                self = F;
            }
        }
    }
}

bool Map::empty() const
{
    if (_map.empty())
        return true;
    else
        return false;
}

int Map::checkStar()
{
    if (_map[_star[1]][_star[0]] == FINISH)
        return 1;
    else
        return 0;
}

void Map::generateMaps(mv &init_map, std::vector<Map> &Levels)
{
    Map Level(init_map);
    Levels.push_back(Level);
}

void Map::generateMaps(std::string name, mv init_map, std::vector<Map> &Levels)
{
    Map Level(name, init_map);
    Levels.push_back(Level);
}
