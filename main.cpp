#include <QWidget>
#include "MyWidget.h"
int main(int argc, char **argv){
    QApplication app = new QApplication(argc,argv);
    MyWidget w = new MyWidget();
    w.show();
    return app.exec();
}