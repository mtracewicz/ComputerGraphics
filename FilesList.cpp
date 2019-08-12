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
	files.clear();
    delete layout;
}
void FilesList::loadDirectory(QString dir){
    for(long unsigned int i = 0;i < files.size();i++){
        delete files[i];
    }
	files.clear();
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
	if(files.size()>0){
    for(long unsigned int i = 0;i < files.size()-1;i++){
        layout->addWidget(files[i]);
    }
	layout->addWidget(files[files.size()-1]->fileName);
	}
}