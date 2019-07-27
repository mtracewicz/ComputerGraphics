#ifndef SLIDERS_H
#define SLIDERS_H

#include <QWidget>

class Sliders : public QWidget{
    Q_OBJECT
private:
    QSlider *r_slider;
    QSlider *g_slider;
    QSlider *b_slider;
    QSlider *h_slider;
    QSlider *s_slider;
    QSlider *v_slider;
public:
    Sliders();
    ~Sliders();

};
#endif