#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Player.hpp"

extern const std::string F;

using mv = std::vector<std::vector<std::string>>;

class Map
{
public:
    Map() {};
    explicit Map(const int &rows, const int &cols);
    explicit Map(const std::string &mapName, const int &rows, const int &cols);
    explicit Map(const std::string &mapName, const int &rows, const int &cols, const mv &initMap);
    explicit Map(const std::string &mapName, const mv &initMap);

    void setMapSize(const int &rows, const int &cols);
    void init(const mv &initMap);
    void refresh();
    void show();
    void movePlayer(const int dx, const int dy);

private:
    int _rows = 0;
    int _columns = 0;
    std::string _mapName{};
    mv _map{};
    Player _player{0, 0};
};