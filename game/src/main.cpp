#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "../include/map.hpp"
#include "../include/maps.hpp"

int main()
{
    std::string input{};
    std::vector<std::string> step{};
    bool flag = true;

    Player player{static_cast<int>(Level_1.rows() / 2), static_cast<int>(Level_1.cols() / 2)};
    std::string position = "player: (" + std::to_string(Level_1.player().where()[0]) + ", " + std::to_string(Level_1.player().where()[1]) + ")\n";
    Level_1.inPlayer(player);

    std::cout << position;

    while (flag)
    {
        system("clear");
        Level_1.refresh();
        Level_1.show();
        position = "player: (" + std::to_string(Level_1.player().where()[0]) + ", " + std::to_string(Level_1.player().where()[1]) + ")\n";

        std::cout << position;
        std::cin >> input;

        step = Level_1.keyAnalyse(input);
        int debug = 0;

        if (step.empty())
            continue;
        for (auto com = step.begin(); com != step.end(); com++)
        {
            if (*com == UP)
                Level_1.movePlayer(0, -1);
            else if (*com == RIGHT)
                Level_1.movePlayer(1, 0);
            else if (*com == DOWN)
                Level_1.movePlayer(0, 1);
            else if (*com == LEFT)
                Level_1.movePlayer(-1, 0);
            else if (*com == QUIT)
            {
                flag = false;
                break;
            }

            system("clear");
            Level_1.refresh();
            Level_1.show();
            position = "player: (" + std::to_string(Level_1.player().where()[0]) + ", " + std::to_string(Level_1.player().where()[1]) + ")\n";

            std::cout << position;
            std::cout << debug << "\n";
            ++debug;
            if (com != --step.end())
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        step.clear();
    }
    return 0;
}