#include "Sliders.h"

Sliders::Sliders(){
    box  = new QVBoxLayout();
    r_slider = new QSlider(Qt::Horizontal);
    g_slider = new QSlider(Qt::Horizontal);
    b_slider = new QSlider(Qt::Horizontal);
    r_slider -> setRange(0,255);
    g_slider -> setRange(0,255);
    b_slider -> setRange(0,255);
    h_slider = new QSlider(Qt::Horizontal);
    s_slider = new QSlider(Qt::Horizontal);
    v_slider = new QSlider(Qt::Horizontal); 
    h_slider -> setRange(0,100);
    s_slider -> setRange(0,100);
    v_slider -> setRange(0,100);
    
    grid = new QGridLayout();
    grid -> addWidget(new QLabel("R: "),0,0,Qt::AlignLeft);
    grid -> addWidget(r_slider,0,1,Qt::AlignRight);
    grid -> addWidget(new QLabel("G: "),1,0,Qt::AlignLeft);
    grid -> addWidget(g_slider,1,1,Qt::AlignRight);
    grid -> addWidget(new QLabel("B: "),2,0,Qt::AlignLeft);
    grid -> addWidget(b_slider,2,1,Qt::AlignRight);
    grid -> addWidget(new QLabel("H: "),3,0,Qt::AlignLeft);
    grid -> addWidget(h_slider,3,1,Qt::AlignRight);
    grid -> addWidget(new QLabel("S: "),4,0,Qt::AlignLeft);
    grid -> addWidget(s_slider,4,1,Qt::AlignRight);
    grid -> addWidget(new QLabel("V: "),5,0,Qt::AlignLeft);
    grid -> addWidget(v_slider,5,1,Qt::AlignRight);
    box -> addLayout(grid);
    this -> setLayout(box);

    QObject::connect(r_slider,&QSlider::valueChanged,this,&Sliders::sendFurther);
    QObject::connect(g_slider,&QSlider::valueChanged,this,&Sliders::sendFurther);
    QObject::connect(b_slider,&QSlider::valueChanged,this,&Sliders::sendFurther);
}

Sliders::~Sliders(){
    delete r_slider;
    delete g_slider;
    delete b_slider;
    delete h_slider;
    delete s_slider;
    delete v_slider;
    delete box;
    delete grid;
}

void Sliders::sendFurther(int recived){
    if(sender() == r_slider){
        emit valueChanged(recived,'r');
    }else if(sender() == g_slider){
        emit valueChanged(recived,'g');
    }else if(sender() == b_slider){
        emit valueChanged(recived,'b');
    }else if(sender() == h_slider){
        emit valueChanged(recived,'h');
    }else if(sender() == s_slider){
        emit valueChanged(recived,'s');
    }else if(sender() == v_slider){
        emit valueChanged(recived,'v');
    }
}