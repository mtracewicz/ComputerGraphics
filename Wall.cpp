#include "Wall.h"
#include<QDebug>
Wall::Wall(Color color){
    this->color = color;
}
Wall::Wall(){
}
Color Wall::getTileColor(int i){
    Color color;
    Color red(255,52,52,255);
    Color green(139,195,74,255);
    Color blue(44,138,255,255);
    Color orange(245,124,0,255);
    Color grey(00,96,88,255);
    Color pink(194,18,91,255);
    if(tiles[i] < 9){
        color = red;
    }else if(tiles[i]<18){
        color = green;
    }else if(tiles[i]<27){
        color = blue;
    }else if(tiles[i]<36){
        color = orange;
    }else if(tiles[i]<45){
        color = grey;
    }else if(tiles[i]<54){
        color = pink;
    }
    return color;
}
void Wall::rotate(char side){
    if(side == 'l'){
        int tmp = tiles[0];
        tiles[0] = tiles[6];
        tiles[6] = tiles[8];
        tiles[8] = tiles[2];
        tiles[2] = tmp;
        tmp = tiles[1];
        tiles[1] = tiles[3];
        tiles[3] = tiles[7];
        tiles[7] = tiles[5];
        tiles[5] = tmp;
    }else{
        int tmp = tiles[0];
        tiles[0] = tiles[2];
        tiles[2] = tiles[8];
        tiles[8] = tiles[6];
        tiles[6] = tmp;
        tmp = tiles[1];
        tiles[1] = tiles[5];
        tiles[5] = tiles[7];
        tiles[7] = tiles[3];
        tiles[3] = tmp;
    }
}