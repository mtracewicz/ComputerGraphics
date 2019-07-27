#include"MyWidget.h"

MyWidget::MyWidget(){
	img = new QImage(800,600,QImage::Format_RGBA8888);
    sliders = new Sliders();
}
MyWidget::~MyWidget(){
	delete img;
	img = NULL;
}
void MyWidget::MySetPixel(int x,int y,int R,int G,int B,int A){
	unsigned char *ptr = (unsigned char*)img->bits();
	int w = img -> width();
	ptr[4*(x+y*w)] = R;
	ptr[4*(x+y*w)+1] = G;
	ptr[4*(x+y*w)+ 2] = B;
	ptr[4*(x+y*w)+ 3] = A;
}
void MyWidget::paintEvent(QPaintEvent*){
	QPainter p(this);
	p.drawImage(0,0,*img);
}