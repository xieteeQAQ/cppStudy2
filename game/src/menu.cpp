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

    std::string position = "player: (" + std::to_string(Level.player().x()) + ", " + std::to_string(Level.player().y()) + ")\n";

    gameLoop(Level, input, step, position, flag);
}

void Menu::startGame(Map &Level, Player &player) const
{
    std::string input{};
    std::vector<std::string> step{};
    bool flag = true;

    std::string position = "player: (" + std::to_string(Level.player().x()) + ", " + std::to_string(Level.player().y()) + ")\n";
    Level.inPlayer(player);

    gameLoop(Level, input, step, position, flag);
}

void Menu::gameLoop(Map &Level, std::string &input, std::vector<std::string> &step, std::string &position, bool &flag)
{
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

        std::string mode = step[0];
        for (auto com = step.begin(); com != step.end(); ++com)
        {
            if (*com == COM_B)
            {
                mode = COM_B;
                continue;
            }
            else if (*com == COM_P)
            {
                mode = COM_P;
                continue;
            }
            else if (*com == QUIT)
            {
                flag = false;
                break;
            }

            if (mode == COM_P)
            {
                if (com != step.end() && *com != COM_B)
                {
                    if (*com == UP)
                        Level.movePlayer(0, -1);
                    else if (*com == RIGHT)
                        Level.movePlayer(1, 0);
                    else if (*com == DOWN)
                        Level.movePlayer(0, 1);
                    else if (*com == LEFT)
                        Level.movePlayer(-1, 0);
                }
                else if (com != step.end() && *com == COM_B)
                    mode = COM_B;
            }
            else if (mode == COM_B)
            {
                if (com != step.end() && *com != COM_P)
                {
                    if (*com == UP)
                        Level.moveBox(0, -1);
                    else if (*com == RIGHT)
                        Level.moveBox(1, 0);
                    else if (*com == DOWN)
                        Level.moveBox(0, 1);
                    else if (*com == LEFT)
                        Level.moveBox(-1, 0);
                }
                else if (com != step.end() && *com == COM_P)
                    mode = COM_P;
            }
            else
            {
                std::cout << "mode未定义!\n";
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
            if (com != --step.end() && mode != COM_B)
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        step.clear();
    }
}
