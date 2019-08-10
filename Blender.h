#ifndef BLENDER_H
#define BLENDER_H
#include <QImage>
#include <QWidget>
#include <QObject>
class Blender : public QWidget{
    Q_OBJECT
public:
    Blender();
    ~Blender();
private:
    QImage* blendInNormalMode(QImage *foreground, QImage *background,double alpha);
    QImage* blendInMultiplyMode(QImage *foreground, QImage *background,double alpha);
    QImage* blendInScreenMode(QImage *foreground, QImage *background,double alpha);
};
#endif
