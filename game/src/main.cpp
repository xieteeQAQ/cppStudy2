#include <iostream>
#include "../include/map.hpp"
#include "../include/maps.hpp"

int main()
{
    char input = ' ';
    while (input != 'q')
    {
        Level_1.refresh();
        Level_1.show();
        std::cin >> input;
        switch(input)
        {
            case 'w':
                Level_1.movePlayer(0, -1);
            case 'a':
                Level_1.movePlayer(-1, 0);
            case 's':
                Level_1.movePlayer(0, 1);
            case 'd':
                Level_1.movePlayer(1, 0);
        }
        system("clear");
    }
    return 0;
}