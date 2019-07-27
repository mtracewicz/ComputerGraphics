#include "Holder.h"
#include <QDebug>
Holder::Holder(){
    img = new QImage(255,255,QImage::Format_RGBA8888);
    x = new QLabel("G");
    y = new QLabel("B");
    imgHolder = new QLabel("");
    map = new QPixmap(QPixmap::fromImage(*img,Qt::AutoColor));
    imgHolder -> setPixmap(*map);
    layout = new QGridLayout();
    layout -> addWidget(y,0,5,Qt::AlignRight);
    layout -> addWidget(x,2,1,Qt::AlignCenter);
    layout -> addWidget(imgHolder,0,1,Qt::AlignCenter);
    this -> setLayout(layout);

    for(int i = 0; i < img -> width();i++){
        for(int j = 0; j < img -> height();j++){
            this -> MySetPixel(i,j,0,0,0,255);
        }
    }
}
Holder::~Holder(){
    delete x;
    delete y;
    delete img;
    delete layout;
    img = NULL;
}

void Holder::MySetPixel(int x,int y,int R,int G,int B,int A){
	unsigned char *ptr = (unsigned char*)img->bits();
	int w = img -> width();
	ptr[4*(x+y*w)] = R;
	ptr[4*(x+y*w)+1] = G;
	ptr[4*(x+y*w)+ 2] = B;
	ptr[4*(x+y*w)+ 3] = A;
}
void Holder::paintEvent(QPaintEvent*){
	QPainter p(this);
	p.drawImage(0,0,*img);
}

void Holder::setColor(int value,char color){
    this -> colorConst = value;
    this -> whichColor = color;

    switch(color){
        case 'r':
            x -> setText("G");
            y -> setText("B");
            for(int i = 0; i < img -> width();i++){
                for(int j = img -> height(); j > 0 ;j--){    
                    this -> MySetPixel(i,j-1,value,i,255-j,255);
                }
            }
            break;
        case 'g':
            x -> setText("R");
            y -> setText("B");
            for(int i = 0; i < img -> width();i++){
                for(int j = img -> height(); j > 0 ;j--){    
                    this -> MySetPixel(i,j-1,i,value,255-j,255);
                }
            }
            break;
        case 'b':
            x -> setText("R");
            y -> setText("G");
            for(int i = 0; i < img -> width();i++){
                for(int j = img -> height(); j > 0 ;j--){    
                    this -> MySetPixel(i,j-1,i,255-j,value,255);
                }
            }
            break;
    }
    repaint();
}