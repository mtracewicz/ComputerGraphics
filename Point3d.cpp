#include "Point3d.h"
Point3d::Point3d(int i, int j, int k) {
    this -> x = i;
    this -> y = j;
    this -> z = k;
};
Point3d::Point3d() {
    this -> x = 0;
    this -> y = 0;
    this -> z = 0;
};
Point3d::Point3d(Point3d *other){
    this -> x = other->x;
    this -> y = other->y;
    this -> z = other->z;
}
Point3d Point3d::rotateOX(int alpha){
    float alphaInRadians = (alpha*M_PI)/180;
    int tmpy = y,tmpz = z;
    int ry,rz;
    Point3d point;
    ry = int(tmpy*cos(alphaInRadians)-tmpz*sin(alphaInRadians));
    rz = int(tmpy*sin(alphaInRadians)+tmpz*cos(alphaInRadians));
    point.x = this->x;
    point.y = ry;
    point.z = rz;
    return point;
}
Point3d Point3d::rotateOY(int alpha){
    float alphaInRadians = (alpha*M_PI)/180;
    int tmpx = x,tmpz = z;
    int rx,rz;
    Point3d point;
    rx = int(tmpx*cos(alphaInRadians) + tmpz*sin(alphaInRadians));
    rz = int(tmpz*cos(alphaInRadians) - tmpx*sin(alphaInRadians));
    point.x = rx;
    point.y = this->y;
    point.z = rz;
    return point;
}
Point3d Point3d::rotateOZ(int alpha){
    float alphaInRadians = (alpha*M_PI)/180;
    int tmpx = x,tmpy = y;
    int rx,ry;
    Point3d point;
    rx = int(tmpx*cos(alphaInRadians)-tmpy*sin(alphaInRadians));
    ry = int(tmpx*sin(alphaInRadians)+tmpy*cos(alphaInRadians));
    point.x = rx;
    point.y = ry;
    point.z = this->z;
    return point;
}
Point3d Point3d::rotate(int alpha,int beta,int gamma){
    Point3d tmp = this;
    tmp = tmp.rotateOX(alpha).rotateOY(beta).rotateOZ(gamma);
    return tmp;    
}
Point3d Point3d::vectorProduct(Point3d other){
    Point3d tmp;
    tmp.x = this->y*other.z - this->z*other.y;
    tmp.y = this->z*other.x - this->x*other.z;
    tmp.z = this->x*other.y - this->y*other.x;
    return tmp;
}
Point3d Point3d::move(int direction,int step1,int step2){
    Point3d tmp = this;
    if(direction == 0){
        tmp.y += step1;
        tmp.z += step2;
    }else if(direction == 1){
        tmp.x += step1;
        tmp.z += step2;
    }else if(direction == 2){
        tmp.x += step1;
        tmp.y += step2;
    }
    return tmp;
}