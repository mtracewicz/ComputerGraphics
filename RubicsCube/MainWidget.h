#pragma once
#include <qwidget.h>
#include <qimage.h>
#include <qpainter.h>
#include <QKeyEvent>
#include <QDebug>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <utility>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "Point3d.h"
#include "Color.h"
#include "Wall.h"
using namespace std;
class MainWidget : public QWidget{
private:
	Q_OBJECT
	QImage *img;
    int orientation;
    Wall walls[6];
    vector<Point3d> points;
    int triangles[12][3];
    int alpha,beta,r,d;
    stack<pair<int,int>> pointsStack;
    Color *white,*black;
    Color* getColorFromPixel(int x,int y);
    void loadPoints(int r);
    void loadWalls();
    void loadTriangles();
    void setPixel(int x,int y,Color color);
    void drawLine(int startX,int sinishX,int startY,int finishY,Color color);
    double drawTriangle(int i);
    void drawWall(int i);
    void drawCube();
    void clearImg();
    void fillWall(int i);
    void hashWall(int i);
    void floodFill(Color backgroundColor,Color colorToFillWith);
    void initializeTiles();
    void rotateLeft(char side);
    void rotateRight(char side);
    void rotateDown(char side);
    void rotateUp(char side);
    void destroyCube();
public:
    MainWidget();
    ~MainWidget();
protected:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
};