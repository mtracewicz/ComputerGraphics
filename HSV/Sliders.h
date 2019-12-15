#ifndef SLIDERS_H
#define SLIDERS_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QGridLayout>

class Sliders : public QWidget{
    Q_OBJECT
private:
    QVBoxLayout *box;
    QGridLayout *grid;
    QSlider *r_slider;
    QSlider *g_slider;
    QSlider *b_slider;
    QSlider *h_slider;
    QSlider *s_slider;
    QSlider *v_slider;

public slots:
    void sendFurther(int recived);
signals:
    void valueChanged(int value,char color);
public:
    Sliders();
    ~Sliders();
};
#endif