#ifndef MYWIDGET_H
#define MYWIDGET_H


#include <QWidget>
#include <QObject>
#include "Holder.h"
#include "Sliders.h"
#include <QHBoxLayout>

class MyWidget : public QWidget{
    Q_OBJECT
public:
    MyWidget();
    ~MyWidget();
private:
    Holder *holder;
    Sliders *sliders;
    QHBoxLayout *mainLayout;
};
#endif
