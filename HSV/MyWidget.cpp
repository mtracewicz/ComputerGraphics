#include"MyWidget.h"

MyWidget::MyWidget(){
	holder = new Holder();
    sliders = new Sliders();
	mainLayout = new QHBoxLayout();
	mainLayout -> addWidget(holder);
	mainLayout -> addWidget(sliders);
	this -> setLayout(mainLayout);
	QObject::connect(sliders,&Sliders::valueChanged,holder,&Holder::setColor);
}
MyWidget::~MyWidget(){
	delete holder;
	delete sliders;
	delete mainLayout;
}