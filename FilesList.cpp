#include "FilesList.h"
#include <QDebug>
FilesList::FilesList(){
    layout = new QVBoxLayout();
    setLayout(layout);
}
FilesList::~FilesList(){
    for(long unsigned int i = 0;i < files.size();i++){
        delete files[i];
    }
    delete layout;
}
void FilesList::loadDirectory(QString dir){
    DIR *dpdf;
	struct dirent *epdf;
	QString fileName;
	QByteArray ba = dir.toLocal8Bit();
  	const char *dirName = ba.data();
	dpdf = opendir(dirName);
	if (dpdf != NULL){
		while ((epdf = readdir(dpdf))){
			if(epdf->d_name[0] != '.'){
				fileName = dir + "/"+epdf->d_name;
                files.push_back(new OptionSelector(fileName));
			}
		}
	}
	closedir(dpdf);
	free(epdf);
    addImagesToList();
}
void FilesList::addImagesToList(){
    for(long unsigned int i = 0;i < files.size();i++){
        layout->addWidget(files[i]);
    }
}