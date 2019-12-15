#pragma once
#ifndef POINT3D_H
#define POINT3D_H
#include <math.h>
class Point3d {
public:
    int x,y,z;
    Point3d(int i,int j,int h);
    Point3d();
    Point3d(Point3d *other);
    Point3d rotateOX(int alpha);
    Point3d rotateOY(int alpha);
    Point3d rotateOZ(int alpha);
    Point3d rotate(int alpha,int beta,int gamma);
    Point3d vectorProduct(Point3d other);
    Point3d move(int direction,int step1,int step2);
};
#endif