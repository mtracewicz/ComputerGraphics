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
    QImage *image;
    QLabel *fileName;
    QComboBox *blendingMode;
    QSlider *alpha;
private:
    QGridLayout *layout;
    QString cutName(QString name);
};
#endif
