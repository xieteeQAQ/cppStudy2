#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include "../include/menu.hpp"

Menu::Menu(std::vector<Map> &Levels)
{
    _Levels = Levels;
    _LevelsCount = _Levels.size();
}

void Menu::startMenu()
{
    std::string input{};
    bool flag = true;
    while (flag)
    {
        int num = 0;
        std::cout << "请选择接下来的行动\n [1]输入q退出 [2]输入数字选择关卡\n";
        std::cin >> input;
        clear();
        char key = input[0];
        switch (key)
        {
        case 'q':
            flag = false;
            break;
        default:
            if (isdigit(key))
            {
                num = key - '0';
                if (num <= _LevelsCount && num >= 1)
                {
                    this->startGame(this->selectLevel(num));
                    clear();
                }
                else
                    std::cout << "· 没有这个关卡!\n";
            }
            break;
        }
    }
}

int Menu::LevelsCount() const
{
    return _LevelsCount;
}

void Menu::startGame(Map &Level) const
{
    if (Level.empty())
    {
        std::clog << "开始游戏的地图为空!\n";
        return;
    }
    Level.reInit();

    std::string input{};
    std::vector<std::string> step{};
    bool flag = true;

    std::string position = "player: (" + std::to_string(Level.player().x()) + ", " + std::to_string(Level.player().y()) + ")\n";

    gameLoop(Level, input, step, position, flag);
}

void Menu::startGame(Map &Level, Player &player) const
{
    if (Level.empty())
    {
        std::clog << "开始游戏的地图为空!\n";
        return;
    }
    Level.reInit();

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
        clear();
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
            else if (*com == WIN)
            {
                flag = false;
                std::cout << "通关!\n\n请输入任意内容继续\n";
                std::cin >> input;
                return;
            }
            else if (*com == RESTART)
            {
                Level.reInit();
                continue;
            }
            else if (*com == QUIT)
            {
                flag = false;
                return;
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

            clear();
            Level.refresh();
            Level.show();
            position = "player: (" + std::to_string(Level.player().x()) + ", " + std::to_string(Level.player().y()) + ")\n";

            std::cout << position;
            if (debug > 0)
                std::cout << "debug信息: " << debug << "\n";
            ++debug;
            if (com != --step.end() && mode != COM_B)
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        if (Level.checkStar())
        {
            flag = false;
            std::cout << "通关!\n请输入任意内容继续\n";
            std::cin >> input;
            return;
        }
        step.clear();
    }
}

Map &Menu::selectLevel(int number)
{
    int index = number - 1;
    if (_Levels.empty())
    {
        std::cout << "关卡容器为空!\n";
        static Map empty_map{};
        return empty_map;
    }
    else if (index >= _Levels.size())
    {
        std::cout << "下标超出关卡容器!\n";
        static Map empty_map{};
        return empty_map;
    }
    else
    {
        return _Levels[index];
    }
}

void Menu::initLevels()
{
    Map::generateMaps("Level_1", Level_1_init, Levels);
    Map::generateMaps("Level_2", Level_2_init, Levels);
    Map::generateMaps("Level_3", Level_3_init, Levels);
    Map::generateMaps("Level_4", Level_4_init, Levels);
    Map::generateMaps("Level_5", Level_5_init, Levels);
    Map::generateMaps("Level_6", Level_6_init, Levels);
}

void clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}