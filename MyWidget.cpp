#include "MyWidget.h"
#include <QDebug>
MyWidget::MyWidget(){
	mainLayout = new QGridLayout();
	selectDir = new QPushButton("Select directory");
	blendButton = new QPushButton("Blend!");
	list = new FilesList();
	img = new QImage(800,600,QImage::Format_RGBA8888);
	imgHolder = new QLabel("");
	map = new QPixmap(QPixmap::fromImage(*img,Qt::AutoColor));
	imgHolder -> setPixmap(*map);

	for(int i = 0;i<800;i++){
		for(int j = 0; j<600;j++){
			mySetPixel(i,j,0,0,0,255);
		}
	}

	mainLayout -> addWidget(selectDir,0,1);
	mainLayout -> addWidget(blendButton,2,1);
	mainLayout -> addWidget(list,1,1);
	mainLayout -> addWidget(imgHolder,1,0);
	this -> setLayout(mainLayout);
	QObject::connect(blendButton,&QPushButton::clicked,this,&MyWidget::blend);
	QObject::connect(selectDir,&QPushButton::clicked,this,&MyWidget::loadFiles);
}
MyWidget::~MyWidget(){
	delete selectDir;
	delete blendButton;
	delete mainLayout;
	delete list;
	delete img;
	delete map;
}
void MyWidget::mySetPixel(int x,int y,int R,int G,int B,int A){
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
void MyWidget::blend(){
	repaint();
}
void MyWidget::loadFiles(){
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
													"/home",
													QFileDialog::ShowDirsOnly
													|QFileDialog::DontResolveSymlinks);
	list->loadDirectory(dir);
}