#include "Sliders.h"

Slider::Sliders(){
    r_slider = new QSlider(QT::HORIZONTAL);
    g_slider = new QSlider(QT::HORIZONTAL);
    b_slider = new QSlider(QT::HORIZONTAL);
    r_slider.setRange(0,100);
    g_slider.setRange(0,100);
    b_slider.setRange(0,100);
    h_slider = new QSlider(QT::HORIZONTAL);
    s_slider = new QSlider(QT::HORIZONTAL);
    v_slider = new QSlider(QT::HORIZONTAL); 
}

Sliders::~Sliders(){
    delete r_slider;
    delete g_slider;
    delete b_slider;
    delete h_slider;
    delete s_slider;
    delete v_slider;
}