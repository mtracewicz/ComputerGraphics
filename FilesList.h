#ifndef FILESLIST_H
#define FILESLIST_H

#include <vector>
#include <QWidget>
#include <QObject>
#include <QString>
#include <dirent.h>
#include <QByteArray>
#include <QVBoxLayout>
#include "OptionSelector.h"

class FilesList : public QWidget{
    Q_OBJECT
public:
    FilesList();
    ~FilesList();
    void loadDirectory(QString dir);
private:
    QVBoxLayout *layout;
    std::vector<OptionSelector*> files;
    void addImagesToList();
};
#endif
