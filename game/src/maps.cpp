#include "../include/map.hpp"
#include "../include/maps.hpp"

std::vector<Map> Levels{};

const mv Level_1_init =
    {
        {S, F, F, F},
        {F, F, F, F},
        {F, F, B, F},
        {F, F, F, P}};

const mv Level_2_init =
    {
        {F, F, F, F, F, F, F},
        {F, F, S, F, F, F, F},
        {F, F, W, W, W, F, F},
        {F, F, W, W, W, F, F},
        {F, F, F, F, B, F, F},
        {F, F, F, F, F, F, P}};

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

const mv Level_4_init =
    {
        {F, F, F, B, B, F, S},
        {F, F, F, B, B, F, F},
        {F, F, W, W, W, W, W},
        {F, F, F, B, B, F, F},
        {F, F, F, B, B, F, P}};

const mv Level_5_init =
    {
        {F, F, F, B, F, F, F},
        {B, F, F, B, F, B, F},
        {F, F, F, W, F, F, P},
        {B, B, W, W, W, W, W},
        {F, F, F, W, F, F, S},
        {F, F, F, B, F, F, F},
        {F, B, B, B, F, F, F}};

const mv Level_6_init =
    {
        {P, W, W, W, W, W, S},
        {B, B, B, B, B, B, F},
        {B, B, B, B, B, B, F},
        {B, B, B, B, B, B, F},
        {B, B, B, B, B, B, F},
        {B, B, B, B, B, B, F},
        {F, F, F, F, F, F, F}};