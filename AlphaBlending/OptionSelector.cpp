#include "OptionSelector.h"
#include <QDebug>
OptionSelector::OptionSelector(){
    layout = new QGridLayout();
    fileName = new QLabel();
    blendingMode = new QComboBox();
    alpha = new QSlider();
}
OptionSelector::OptionSelector(QString fileName){
    layout = new QGridLayout();
    this->fileName = new QLabel(cutName(fileName),this);
    blendingMode = new QComboBox();
    blendingMode -> addItem("Normal");
    blendingMode -> addItem("Multiply");
    blendingMode -> addItem("Overlay");
    blendingMode -> addItem("Screen");
    alpha = new QSlider(Qt::Horizontal);
    alpha->setMaximum(100);
    alpha->setMinimum(1);
    alpha->setMaximumWidth(100);
    blendingMode->setMaximumWidth(100);
    this->fileName->setMaximumWidth(100);
    this->setMinimumWidth(300);
    layout -> addWidget(blendingMode,0,2);
    layout -> addWidget(alpha,0,1);
    layout -> addWidget(this->fileName,0,0);
    image = new QImage(fileName);
    setLayout(layout);
}
OptionSelector::~OptionSelector(){
    delete layout;
    delete fileName;
    delete blendingMode;
    delete alpha;
    delete image;
}
QString OptionSelector::cutName(QString name){
    if( (name.lastIndexOf("/")) != -1){
        int len = name.size() - name.lastIndexOf("/") - 1;
        return name.right(len); 
    }else{
        return name;
    }
}