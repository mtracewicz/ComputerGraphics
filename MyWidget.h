#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "Sliders.h"

class MyWidget : public QWidget{
    Q_OBJECT
public:
    MyWidget();
    ~MyWidget();
protected:
    void paintEvent(QPaintEvent*);
private:
    QImage *img;
    Sliders *sliders;
    void MySetPixel(int x,int y,int R,int G,int B,int A);
};
#endif
