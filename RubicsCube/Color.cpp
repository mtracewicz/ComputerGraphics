#include "Color.h"
Color::Color(){
    this->r = 0;
    this->g = 0;
    this->b = 0;
    this->a = 255;
}
Color::Color(int r,int g,int b,int a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}
int Color::getR(){
    return this->r;
}
int Color::getG(){
    return this->g;
}
int Color::getB(){
    return this->b;
}
int Color::getA(){
    return this->a;
}
bool Color::operator== (Color other){
    return (this->r == other.r &&
            this->g == other.g &&
            this->b == other.b &&
            this->a == other.a);
}