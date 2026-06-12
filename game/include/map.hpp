#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Player.hpp"

extern const std::string P;
extern const std::string F;
extern const std::string W;
extern const std::string B;
extern const std::string S;
extern const std::string FINISH;

extern const std::string UP;
extern const std::string RIGHT;
extern const std::string DOWN;
extern const std::string LEFT;
extern const std::string QUIT;
extern const std::string RESTART;

extern const std::string COM_P;
extern const std::string COM_B;
extern const std::string WIN;

using mv = std::vector<std::vector<std::string>>;

class Map
{
public:
    Map() {};
    explicit Map(const int &rows, const int &cols);
    explicit Map(const std::string &mapName, const int &rows, const int &cols);
    explicit Map(const std::string &mapName, const mv &initMap);
    explicit Map(const mv &initMap);

    Player player() const;
    int rows() const;
    int cols() const;
    mv map() const;
    void reInit();
    void inPlayer(Player &player);
    void setMapSize(const int &rows, const int &cols);
    void refresh();
    void show() const;
    void movePlayer(const int dx, const int dy);
    void setPlayerPosition(const int x, const int y);
    void moveBox(const int dx, const int dy);
    std::string at(const int x, const int y) const;
    void executeAnalyse(std::vector<std::string> &res, std::string &key, mv &copy_map, int &x, int &y) const;
    std::vector<std::string> keyAnalyse(std::string &keys) const;
    bool empty() const;

private:
    int _rows = 0;
    int _columns = 0;
    std::string _mapName{};
    mv _map{};
    mv _init_map{};
    Player _player{0, 0};
    int _orign_x = 0;
    int _orign_y = 0;
    std::vector<int> _star{0, 0};
};