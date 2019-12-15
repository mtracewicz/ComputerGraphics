#include <qapplication.h>
#include "MainWidget.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );

    MainWidget m;
    m.show();

	a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
