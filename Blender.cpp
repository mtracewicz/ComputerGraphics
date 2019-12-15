#include "Blender.h"
#include <QDebug>
Blender::Blender(){
}
Blender::~Blender(){
}
void Blender::blendInNormalMode(QImage *foreground, QImage *background){
    unsigned char *ptrF = (unsigned char*)foreground->bits();
    unsigned char *ptrB = (unsigned char*)background->bits();
	int w = foreground -> width();
	for(int x = 0;x<800;x++){
        for(int y = 0;y<600;y++){
            ptrB[4*(x+y*w)] = ptrF[4*(x+y*w)];
            ptrB[4*(x+y*w)+1] = ptrF[4*(x+y*w)+1];
	        ptrB[4*(x+y*w)+2] = ptrF[4*(x+y*w)+2];
	        ptrB[4*(x+y*w)+3] = 255;
        }
    }
}
void Blender::blendInMultiplyMode(QImage *foreground, QImage *background,double alpha){
    alpha /= 100;
    unsigned char *ptrF = (unsigned char*)foreground->bits();
    unsigned char *ptrB = (unsigned char*)background->bits();
	int w = foreground -> width();
	for(int x = 0;x<800;x++){
        for(int y = 0;y<600;y++){
            ptrB[4*(x+y*w)] = int((alpha*ptrF[4*(x+y*w)] *(1-alpha)* ptrB[4*(x+y*w)])) >> 8;
            ptrB[4*(x+y*w)+1] = int((alpha*ptrF[4*(x+y*w)+1] *(1-alpha)*ptrB[4*(x+y*w)+1])) >> 8;
	        ptrB[4*(x+y*w)+2] = int((alpha*ptrF[4*(x+y*w)+2] *(1-alpha)*ptrB[4*(x+y*w)+2])) >> 8;
	        ptrB[4*(x+y*w)+3] = 255;
        }
    }
}
void Blender::blendInScreenMode(QImage *foreground, QImage *background,double alpha){
    alpha /= 100;
    unsigned char *ptrF = (unsigned char*)foreground->bits();
    unsigned char *ptrB = (unsigned char*)background->bits();
	int w = foreground -> width();
	for(int x = 0;x<800;x++){
        for(int y = 0;y<600;y++){
            ptrB[4*(x+y*w)] = int(255-(alpha*(255-ptrF[4*(x+y*w)]) *(1-alpha)* (255-ptrB[4*(x+y*w)]))) >> 8;
            ptrB[4*(x+y*w)+1] = int(255-(alpha*(255-ptrF[4*(x+y*w)+1]) *(1-alpha)*(255-ptrB[4*(x+y*w)+1]))) >> 8;
	        ptrB[4*(x+y*w)+2] = int(255-(alpha*(255-ptrF[4*(x+y*w)+2]) *(1-alpha)*(255-ptrB[4*(x+y*w)+2])))>> 8;
	        ptrB[4*(x+y*w)+3] = 255;
        }
    }
}
void Blender::blendInOverlayMode(QImage *foreground, QImage *background,double alpha){
    alpha /= 100;
    unsigned char *ptrF = (unsigned char*)foreground->bits();
    unsigned char *ptrB = (unsigned char*)background->bits();
	int w = foreground -> width();
	for(int x = 0;x<800;x++){
        for(int y = 0;y<600;y++){
            if(ptrB[4*(x+y*w)] < 128){
                ptrB[4*(x+y*w)] = int((alpha*ptrF[4*(x+y*w)] *(1-alpha)* ptrB[4*(x+y*w)])) >> 7;
            }else{
                ptrB[4*(x+y*w)] = int(255-(alpha*(255-ptrF[4*(x+y*w)]) *(1-alpha)* (255-ptrB[4*(x+y*w)]))) >> 7;
            }
            if(ptrB[4*(x+y*w)+1] < 128){
                ptrB[4*(x+y*w)+1] = int((alpha*ptrF[4*(x+y*w)+1] *(1-alpha)* ptrB[4*(x+y*w)+1])) >> 7;
            }else{
                ptrB[4*(x+y*w)+1] = int(255-(alpha*(255-ptrF[4*(x+y*w)+1]) *(1-alpha)* (255-ptrB[4*(x+y*w)+1]))) >> 7;
            }
            if(ptrB[4*(x+y*w)+2] < 128){
                ptrB[4*(x+y*w)+2] = int((alpha*ptrF[4*(x+y*w)+2] *(1-alpha)* ptrB[4*(x+y*w)+2]))>> 7;
            }else{
                ptrB[4*(x+y*w)+2] = int(255-(alpha*(255-ptrF[4*(x+y*w)+2]) *(1-alpha)* (255-ptrB[4*(x+y*w)+2])))>> 7;
            }
            ptrB[4*(x+y*w)+3] = 255;
        }
    }
}