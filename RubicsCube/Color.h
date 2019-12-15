#ifndef COLOR_H
#define COLOR_H
class Color{
private:
    int r,g,b,a;
public:
    Color();
    Color(int r,int g,int b,int a);
    bool operator== (Color other);
    int getR();
    int getG();
    int getB();
    int getA();
protected:
};
#endif