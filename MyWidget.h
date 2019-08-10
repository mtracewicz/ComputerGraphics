#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <string>
#include <vector>
#include <QWidget>
#include <QObject>
#include "FilesList.h"
#include <QPushButton>
#include <QGridLayout>
#include <QPainter>
#include <QFileDialog>
#include <QString>
#include"FilesList.h"

class MyWidget : public QWidget{
    Q_OBJECT

public:
    MyWidget();
    ~MyWidget();
public slots:
    void blend();
    void loadFiles();
signals:

private:
    QGridLayout *mainLayout;
    std::string directory;
    QPushButton *selectDir;
    QPushButton *blendButton;
    FilesList *list;
    QImage *img;
    QLabel *imgHolder;
    QPixmap *map;
    void mySetPixel(int x,int y,int R,int G,int B,int A);
    void paintEvent(QPaintEvent*);
};
#endif
