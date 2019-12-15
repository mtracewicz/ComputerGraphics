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
    void blendInNormalMode(QImage *foreground, QImage *background);
    void blendInMultiplyMode(QImage *foreground, QImage *background,double alpha);
    void blendInScreenMode(QImage *foreground, QImage *background,double alpha);
    void blendInOverlayMode(QImage *foreground, QImage *background,double alpha);
private:
};
#endif
