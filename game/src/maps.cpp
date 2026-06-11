#include "../include/map.hpp"
#include "../include/maps.hpp"

const mv Level_1_init =
    {
        {S, F, F, F},
        {F, F, F, F},
        {F, F, B, F},
        {F, F, F, P}};
Map Level_1("Level_1", Level_1_init);

const mv Level_2_init =
    {
        {F, F, F, F, F, F, F},
        {F, F, S, F, F, F, F},
        {F, F, W, W, W, F, F},
        {F, F, W, W, W, F, F},
        {F, F, F, F, B, F, F},
        {F, F, F, F, F, F, P}};
Map Level_2("Level_2", Level_2_init);

const mv Level_3_init =
    {
        {F, F, F, F, F, F, S},
        {F, F, F, F, F, F, F},
        {F, F, W, W, W, W, W},
        {F, F, F, F, F, F, F},
        {F, F, F, F, F, F, F},
        {W, W, W, W, W, F, F},
        {F, F, F, B, F, F, F},
        {P, F, F, F, F, F, F}};
Map Level_3("Level_3", Level_3_init);

std::vector<Map> Levels = {Level_1, Level_2, Level_3};
