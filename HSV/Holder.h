#ifndef HOLDER_H
#define HOLDER_H

#include <cmath>
#include <QLabel>
#include <QWidget>
#include <QSlider>
#include <QPainter>
#include <QGridLayout>


class Holder : public QWidget{
    Q_OBJECT
private:
    QImage *img;
    QLabel *x;
    QLabel *y;
    QLabel *imgHolder;
    QPixmap *map;
    QGridLayout *layout;
    void MySetPixel(int x,int y,int R,int G,int B,int A);
protected:
    void paintEvent(QPaintEvent*);
public slots:
    void setColor(int value,char color);
public:
    Holder();
    ~Holder();
};
#endif