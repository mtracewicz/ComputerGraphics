#ifndef OPTIONSELECTOR_H
#define OPTIONSELECTOR_H

#include <QLabel>
#include <string>
#include <QImage>
#include <QSlider>
#include <QWidget>
#include <QObject>
#include <QComboBox>
#include <QGridLayout>
class OptionSelector : public QWidget{
    Q_OBJECT
public:
    OptionSelector();
    OptionSelector(QString fileName);
    ~OptionSelector();
private:
    QGridLayout *layout;
    QImage *image;
    QLabel *fileName;
    QComboBox *blendingMode;
    QSlider *alpha;
    QString cutName(QString name);
};
#endif
