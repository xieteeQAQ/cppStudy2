#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Player.hpp"

extern const std::string F;
extern const std::string B;

extern const std::string UP;
extern const std::string RIGHT;
extern const std::string DOWN;
extern const std::string LEFT;
extern const std::string QUIT;

using mv = std::vector<std::vector<std::string>>;

class Map
{
public:
    Map() {};
    explicit Map(const int &rows, const int &cols);
    explicit Map(const std::string &mapName, const int &rows, const int &cols);
    explicit Map(const std::string &mapName, const int &rows, const int &cols, const mv &initMap);
    explicit Map(const std::string &mapName, const mv &initMap);

    Player player() const;
    int rows() const;
    int cols() const;
    mv map() const;
    void inPlayer(Player &player);
    void setMapSize(const int &rows, const int &cols);
    void init(const mv &initMap);
    void refresh();
    void show() const;
    void movePlayer(const int dx, const int dy);
    void setPlayerPosition(const int x, const int y);
    std::vector<std::string> keyAnalyse(std::string &keys) const;

private:
    int _rows = 0;
    int _columns = 0;
    std::string _mapName{};
    mv _map{};
    Player _player{0, 0};
};