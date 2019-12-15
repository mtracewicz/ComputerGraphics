#pragma once
#ifndef WALL_H
#define WALL_H
#include "Color.h"
class Wall{
public:
    Wall(Color color);
    Wall();
    Color color;
    Color getTileColor(int i);
    int tiles[9];
    void rotate(char side);
private:
};
#endif