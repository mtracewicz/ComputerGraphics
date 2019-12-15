#include "Holder.h"
#include <QDebug>
Holder::Holder(){
    img = new QImage(360,315,QImage::Format_RGBA8888);
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
    switch(color){
        case 'r':
        {
            if(img -> width() != 255){
                img = new QImage(255,255,QImage::Format_RGBA8888);
            }
            x -> setText("G");
            y -> setText("B");
            for(int i = 0; i < 255; i++){
                for(int j = 0; j < 255; j++){
                    this -> MySetPixel(i,j,value,i,255 - j,255);
                }
            }
            break;
        }
        case 'g':
        {
            if(img -> width() != 255){
                img = new QImage(255,255,QImage::Format_RGBA8888);
            }
            x -> setText("R");
            y -> setText("B");
            for(int i = 0; i < 255; i++){
                for(int j = 0; j < 255; j++){
                    this -> MySetPixel(i,j,i,value,255-j,255);
                }
            }
            break;
        }
        case 'b':
        {
            if(img -> width() != 255){
                img = new QImage(255,255,QImage::Format_RGBA8888);
            }
            x -> setText("R");
            y -> setText("G");
            for(int i = 0; i < 255; i++){
                for(int j = 0; j < 255; j++){
                    this -> MySetPixel(i,j,i,255-j,value,255);
                }
            }
            break;
        }
        case 'h':
        {
            if(img -> width() != 315){
                img = new QImage(315,315,QImage::Format_RGBA8888);
            }
            x -> setText("S");
            y -> setText("V");
            for(int s = 0; s <= 100;s++){
                for(int v = 0; v <= 100 ;v++){
                    double r = 0.0,g = 0.0,b = 0.0;
                    double c = (((double)s/100) * ((double)v/100));
                    double hh = value / 60.0;
                    double x = c * (1 - std::abs(fmod(hh, 2) - 1));
                    double m = ((double)v/100) - c; 
                    if(0 <= hh && hh <= 1){
                        r = c;
                        g = x;
                        b = 0;
                    }else if(1 < hh && hh <= 2){
                        r = x;
                        g = c;
                        b = 0;
                    }else if(2 < hh && hh <= 3){
                        r = 0;
                        g = c;
                        b = x;
                    }else if(3 < hh && hh <= 4){
                        r = 0;
                        g = x;
                        b = c;
                    }else if(4 < hh && hh <= 5){
                        r = x;
                        g = 0;
                        b = c;
                    }else if(5 < hh && hh <= 6){
                        r = c;
                        g = 0;
                        b = x;
                    }
                    r = (r+m)*255.0;
                    g = (g+m)*255.0;
                    b = (b+m)*255.0;
                    for(int i = 0;i < 3;i++){
                        for(int j = 0; j < 3;j++){
                            this -> MySetPixel(3*s+i,314 - (3*v-j),int(r),int(g),int(b),255);
                        }
                    }
                }
            }
            break;
        }
        case 's':
        {
            if(img -> width() != 360){
                img = new QImage(360,315,QImage::Format_RGBA8888);
            }
            x -> setText("H");
            y -> setText("V");
            for(int h = 0; h < 360;h++){
                for(int v = 0; v <= 100 ;v++){
                    double r = 0.0,g = 0.0,b = 0.0;
                    double c = (((double)value/100) * ((double)v/100));
                    double hh = h / 60.0;
                    double x = c * (1 - std::abs(fmod(hh, 2) - 1));
                    double m = ((double)v/100) - c; 
                    if(0 <= hh && hh <= 1){
                        r = c;
                        g = x;
                        b = 0;
                    }else if(1 < hh && hh <= 2){
                        r = x;
                        g = c;
                        b = 0;
                    }else if(2 < hh && hh <= 3){
                        r = 0;
                        g = c;
                        b = x;
                    }else if(3 < hh && hh <= 4){
                        r = 0;
                        g = x;
                        b = c;
                    }else if(4 < hh && hh <= 5){
                        r = x;
                        g = 0;
                        b = c;
                    }else if(5 < hh && hh <= 6){
                        r = c;
                        g = 0;
                        b = x;
                    }
                    r = (r+m)*255.0;
                    g = (g+m)*255.0;
                    b = (b+m)*255.0;
                    this -> MySetPixel(h,314-(3*v),int(r),int(g),int(b),255);
                    this -> MySetPixel(h,314-(3*v+1),int(r),int(g),int(b),255);
                    this -> MySetPixel(h,314-(3*v+2),int(r),int(g),int(b),255);
                }
            }
            break;
        }
        case 'v':
        {
            if(img -> width() != 360){
                img = new QImage(360,315,QImage::Format_RGBA8888);
            }
            x -> setText("H");
            y -> setText("S");
            for(int h = 0; h < 360;h++){
                for(int s = 0; s <= 100 ;s++){
                    double r = 0.0,g = 0.0,b = 0.0;
                    double c = (((double)s/100) * ((double)value/100));
                    double hh = h / 60.0;
                    double x = c * (1 - std::abs(fmod(hh, 2) - 1));
                    double m = ((double)value/100) - c; 
                    if(0 <= hh && hh <= 1){
                        r = c;
                        g = x;
                        b = 0;
                    }else if(1 < hh && hh <= 2){
                        r = x;
                        g = c;
                        b = 0;
                    }else if(2 < hh && hh <= 3){
                        r = 0;
                        g = c;
                        b = x;
                    }else if(3 < hh && hh <= 4){
                        r = 0;
                        g = x;
                        b = c;
                    }else if(4 < hh && hh <= 5){
                        r = x;
                        g = 0;
                        b = c;
                    }else if(5 < hh && hh <= 6){
                        r = c;
                        g = 0;
                        b = x;
                    }
                    r = (r+m)*255.0;
                    g = (g+m)*255.0;
                    b = (b+m)*255.0;
                    this -> MySetPixel(h,314-(3*s),int(r),int(g),int(b),255);
                    this -> MySetPixel(h,314-(3*s+1),int(r),int(g),int(b),255);
                    this -> MySetPixel(h,314-(3*s+2),int(r),int(g),int(b),255);
                }
            }
            break;
        }
    }
    repaint();
}