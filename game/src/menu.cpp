#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include "../include/menu.hpp"

void Menu::startGame(Map &Level) const
{
    std::string input{};
    std::vector<std::string> step{};
    bool flag = true;

    Level.setPlayerPosition(static_cast<int>(Level.rows() / 2), static_cast<int>(Level.cols() / 2));
    std::string position = "player: (" + std::to_string(Level.player().x()) + ", " + std::to_string(Level.player().y()) + ")\n";

    std::cout << position;

    while (flag)
    {
        system("clear");
        Level.refresh();
        Level.show();
        position = "player: (" + std::to_string(Level.player().x()) + ", " + std::to_string(Level.player().y()) + ")\n";

        std::cout << position;
        std::cin >> input;

        step = Level.keyAnalyse(input);
        int debug = 0;

        if (step.empty())
            continue;
        for (auto com = step.begin(); com != step.end(); com++)
        {
            if (*com == UP)
                Level.movePlayer(0, -1);
            else if (*com == RIGHT)
                Level.movePlayer(1, 0);
            else if (*com == DOWN)
                Level.movePlayer(0, 1);
            else if (*com == LEFT)
                Level.movePlayer(-1, 0);
            else if (*com == QUIT)
            {
                flag = false;
                break;
            }

            system("clear");
            Level.refresh();
            Level.show();
            position = "player: (" + std::to_string(Level.player().x()) + ", " + std::to_string(Level.player().y()) + ")\n";

            std::cout << position;
            std::cout << debug << "\n";
            ++debug;
            if (com != --step.end())
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        step.clear();
    }
}

void Menu::startGame(Map &Level, Player &player) const
{
    std::string input{};
    std::vector<std::string> step{};
    bool flag = true;

    std::string position = "player: (" + std::to_string(Level.player().x()) + ", " + std::to_string(Level.player().y()) + ")\n";
    Level.inPlayer(player);

    std::cout << position;

    while (flag)
    {
        system("clear");
        Level.refresh();
        Level.show();
        position = "player: (" + std::to_string(Level.player().x()) + ", " + std::to_string(Level.player().y()) + ")\n";

        std::cout << position;
        std::cin >> input;

        step = Level.keyAnalyse(input);
        int debug = 0;

        if (step.empty())
            continue;
        for (auto com = step.begin(); com != step.end(); com++)
        {
            if (*com == UP)
                Level.movePlayer(0, -1);
            else if (*com == RIGHT)
                Level.movePlayer(1, 0);
            else if (*com == DOWN)
                Level.movePlayer(0, 1);
            else if (*com == LEFT)
                Level.movePlayer(-1, 0);
            else if (*com == QUIT)
            {
                flag = false;
                break;
            }

            system("clear");
            Level.refresh();
            Level.show();
            position = "player: (" + std::to_string(Level.player().x()) + ", " + std::to_string(Level.player().y()) + ")\n";

            std::cout << position;
            std::cout << debug << "\n";
            ++debug;
            if (com != --step.end())
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        step.clear();
    }
}