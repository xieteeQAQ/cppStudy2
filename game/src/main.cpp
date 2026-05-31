#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "../include/map.hpp"
#include "../include/maps.hpp"

int main()
{
    char input = ' ';
    std::string str{0};
    Player player{static_cast<int>(Level_1.rows() / 2), static_cast<int>(Level_1.cols() / 2)};
    Level_1.inPlayer(player);
    while (input != 'q')
    {
        system("clear");
        Level_1.refresh();
        Level_1.show();
        std::cout << Level_1.player().where()[0] << ", " << Level_1.player().where()[1] << "\n";
        std::cin >> str;
        int str_len = str.length();
        for (auto &s : str)
        {
            input = s;
            switch (input)
            {
            case 'w':
                Level_1.movePlayer(0, -1);
                break;
            case 'a':
                Level_1.movePlayer(-1, 0);
                break;
            case 's':
                Level_1.movePlayer(0, 1);
                break;
            case 'd':
                Level_1.movePlayer(1, 0);
                break;
            }
            system("clear");
            Level_1.refresh();
            Level_1.show();
            std::cout << Level_1.player().where()[0] << ", " << Level_1.player().where()[1] << "\n";
            if (input == 'q')
            {
                break;
            }
            if (str_len > 1)
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    return 0;
}