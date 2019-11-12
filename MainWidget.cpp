#include "MainWidget.h"
MainWidget::MainWidget(){
    this->setFixedSize(800,600);
    white = new Color(255,255,255,255);
    black = new Color(61,61,61,255);
    img = new QImage(800,600,QImage::Format_RGBA8888);
    alpha = 0;
    beta = 0;
    r = 100;
    d = 700;
    orientation = 0;
    initializeTiles();
    loadPoints(r);
    loadTriangles();
    loadWalls();
    clearImg();
    drawCube();
}
MainWidget::~MainWidget(){
	delete img;
    delete white;
    delete black;
}
void MainWidget::paintEvent(QPaintEvent*){
	QPainter p(this);
	p.drawImage(0,0,*img);
}
void MainWidget::loadWalls() {
    Color red(255,52,52,255);
    Color green(139,195,74,255);
    Color blue(44,138,255,255);
    Color orange(245,124,0,255);
    Color grey(00,96,88,255);
    Color pink(194,18,91,255);

    walls[0].color = red;
    walls[1].color = green;
    walls[2].color = blue;
    walls[3].color = grey;
    walls[4].color = orange;
    walls[5].color = pink;
}

void MainWidget::loadPoints(int r) {
    Point3d a(-r,-r,-r);//0(-1,-1,-1)
    Point3d b(-r, r,-r);//1(-1, 1,-1)
    Point3d c( r, r,-r);//2( 1, 1,-1)
    Point3d d( r,-r,-r);//3( 1,-1,-1)
    Point3d e( r,-r, r);//4( 1,-1, 1)
    Point3d f( r, r, r);//5( 1, 1, 1)
    Point3d g(-r, r, r);//6(-1, 1, 1)
    Point3d h(-r,-r, r);//7(-1,-1, 1)

    points.push_back(a);
    points.push_back(b);
    points.push_back(c);
    points.push_back(d);
    points.push_back(e);
    points.push_back(f);
    points.push_back(g);
    points.push_back(h);
}
void MainWidget::loadTriangles() {
    //------Wall_0------
    triangles[0][0] = 0;
    triangles[0][1] = 1;
    triangles[0][2] = 2;

    triangles[1][0] = 0;
    triangles[1][1] = 2;
    triangles[1][2] = 3;

    //------Wall_1------
    triangles[2][0] = 3;
    triangles[2][1] = 2;
    triangles[2][2] = 5;

    triangles[3][0] = 3;
    triangles[3][1] = 5;
    triangles[3][2] = 4;
    //------Wall_2------
    triangles[4][0] = 4;
    triangles[4][1] = 5;
    triangles[4][2] = 6;

    triangles[5][0] = 4;
    triangles[5][1] = 6;
    triangles[5][2] = 7;
    //------Wall_3------
    triangles[6][0] = 7;
    triangles[6][1] = 6;
    triangles[6][2] = 1;

    triangles[7][0] = 7;
    triangles[7][1] = 1;
    triangles[7][2] = 0;
    //------Wall_4------
    triangles[8][0] = 1;
    triangles[8][1] = 6;
    triangles[8][2] = 5;

    triangles[9][0] = 1;
    triangles[9][1] = 5;
    triangles[9][2] = 2;
    //------Wall_5------
    triangles[10][0] = 4;
    triangles[10][1] = 7;
    triangles[10][2] = 0;

    triangles[11][0] = 4;
    triangles[11][1] = 0;
    triangles[11][2] = 3;
}
void MainWidget::setPixel(int x,int y,Color color){
	unsigned char *ptr = (unsigned char*)img->bits();
	int w = img -> width();
	ptr[4*(x+y*w)] = color.getR();
	ptr[4*(x+y*w)+ 1] = color.getG();
	ptr[4*(x+y*w)+ 2] = color.getB();
	ptr[4*(x+y*w)+ 3] = color.getA();
}
void MainWidget::drawLine(int startX,int finishX,int startY,int finishY,Color color){
	double a,b;
	int i;
    if(startX == finishX){
			for(i = min( startY,finishY); i <= max(startY,finishY); i++){
				setPixel(startX,i,color);
            }
	}
	else{
		a =( (double) ( (finishY - startY) ) / (finishX - startX) );
		b = startY - (a * startX);
		if( a < 1 && a > -1){
			for(i = min(startX,finishX); i <= max(startX,finishX); i++){
				setPixel(i,(int)(a*i + b),color);
			}
		}else{
			for(i = min( startY,finishY); i <= max(startY,finishY); i++){
				setPixel( (int)( (i - b) / a),i,color);
            }
		}
	}
}
double MainWidget::drawTriangle(int i) {
    Point3d p1,p2,p3;
    int x1,x2,x3,y1,y2,y3;
    p1 = points[triangles[i][0]].rotate(alpha,beta,0);
    p2 = points[triangles[i][1]].rotate(alpha,beta,0);
    p3 = points[triangles[i][2]].rotate(alpha,beta,0);
    Point3d tmp;
    tmp.x = p2.x-p1.x;
    tmp.y = p2.y-p1.y;
    tmp.z = p2.z-p1.z;
    Point3d tmp2;
    tmp2.x = p3.x - p1.x;
    tmp2.y = p3.y - p1.y;
    tmp2.z = p3.z - p1.z;
    Point3d normal = tmp.vectorProduct(tmp2);
    float l = sqrtf(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
    double v = (double)(normal.z / l) + 0.16;
    if(v < 0){
        x1 = (p1.x/(double)(1+((double) p1.z/d))) + img -> width()/2;
        x2 = (p2.x/(double)(1+((double) p2.z/d))) + img -> width()/2;
        x3 = (p3.x/(double)(1+((double) p3.z/d))) + img -> width()/2;
        y1 = -1*(p1.y/(double)(1+((double) p1.z/d))) + img -> height()/2;
        y2 = -1*(p2.y/(double)(1+((double) p2.z/d))) + img -> height()/2;
        y3 = -1*(p3.y/(double)(1+((double) p3.z/d))) + img -> height()/2;
        if(i%2 == 0){
           drawLine(x1,x2,y1,y2,*white);
           drawLine(x1-1,x2-1,y1,y2,*white);
           drawLine(x1+1,x2+1,y1,y2,*white);
           drawLine(x1,x2,y1-1,y2-1,*white);
           drawLine(x1,x2,y1+1,y2+1,*white);
        }else{
           drawLine(x1,x3,y1,y3,*white);
           drawLine(x1-1,x3-1,y1,y3,*white);
           drawLine(x1+1,x3+1,y1,y3,*white);
           drawLine(x1,x3,y1-1,y3-1,*white);
           drawLine(x1,x3,y1+1,y3+1,*white);
        }
        drawLine(x2,x3,y2,y3,*white);
        drawLine(x2-1,x3-1,y2,y3,*white);
        drawLine(x2+1,x3+1,y2,y3,*white);
        drawLine(x2,x3,y2-1,y3-1,*white);
        drawLine(x2,x3,y2+1,y3+1,*white);
        return -v;
    }
    return 0;
}
void MainWidget::drawWall(int i) {
    double visable;
    drawTriangle(2*i);
    visable = drawTriangle(2*i+1);
    if(visable != 0){
        hashWall(i);
        fillWall(i);
    }
}
void MainWidget::hashWall(int i) {
    int x1,x2,y1,y2,x3,x4,y3,y4;
    Point3d p1 = points[triangles[2*i][0]];
    Point3d p2 = points[triangles[2*i][1]];
    Point3d p3 = points[triangles[2*i][2]];
    Point3d p4 = points[triangles[2*i+1][2]];
    Point3d tmp1,tmp2,tmp3,tmp4;
    int step = int(2*r / 3.0);
    if(p1.x == p2.x){
        tmp1.x = p1.x;
        tmp3.x = p1.x;
    }else if(min(p1.x,p2.x) == p1.x){
        tmp1.x = p1.x+step;
        tmp3.x = p1.x+(2*step);
    }else{
        tmp1.x = p2.x+step;
        tmp3.x = p2.x+(2*step);
    }
    if(p1.y == p2.y){
        tmp1.y = p1.y;
        tmp3.y = p1.y;
    }else if(min(p1.y,p2.y) == p1.y){
        tmp1.y = p1.y+step;
        tmp3.y = p1.y+(2*step);
    }else{
        tmp1.y = p2.y+step;
        tmp3.y = p2.y+(2*step);
    }
    if(p1.z == p2.z){
        tmp1.z = p1.z;
        tmp3.z = p1.z;
    }else if(min(p1.z,p2.z) == p1.z){
        tmp1.z = p1.z+step;
        tmp3.z = p1.z+(2*step);
    }else{
        tmp1.z = p2.z+step;
        tmp3.z = p2.z+(2*step);
    }

    if(p3.x == p4.x){
        tmp2.x = p3.x;
        tmp4.x = p3.x;
    }else if(min(p3.x,p4.x) == p3.x){
        tmp2.x = p3.x+step;
        tmp4.x = p3.x+(2*step);
    }else{
        tmp2.x = p4.x+step;
        tmp4.x = p4.x+(2*step);
    }
    if(p3.y == p4.y){
        tmp2.y = p3.y;
        tmp4.y = p3.y;
    }else if(min(p3.y,p4.y) == p3.y){
        tmp2.y = p3.y+step;
        tmp4.y = p3.y+(2*step);
    }else{
        tmp2.y = p4.y+step;
        tmp4.y = p4.y+(2*step);
    }
    if(p3.z == p4.z){
        tmp2.z = p3.z;
        tmp4.z = p3.z;
    }else if(min(p3.z,p4.z) == p3.z){
        tmp2.z = p3.z+step;
        tmp4.z = p3.z+(2*step);
    }else{
        tmp2.z = p4.z+step;
        tmp4.z = p4.z+(2*step);
    }
    tmp1 = tmp1.rotate(alpha,beta,0);
    tmp2 = tmp2.rotate(alpha,beta,0);
    tmp3 = tmp3.rotate(alpha,beta,0);
    tmp4 = tmp4.rotate(alpha,beta,0);
    x1 = (tmp1.x/(double)(1+((double) tmp1.z/d))) + img -> width()/2;
    x2 = (tmp2.x/(double)(1+((double) tmp2.z/d))) + img -> width()/2;
    x3 = (tmp3.x/(double)(1+((double) tmp3.z/d))) + img -> width()/2;
    x4 = (tmp4.x/(double)(1+((double) tmp4.z/d))) + img -> width()/2;
    y1 = -1*(tmp1.y/(double)(1+((double) tmp1.z/d))) + img -> height()/2;
    y2 = -1*(tmp2.y/(double)(1+((double) tmp2.z/d))) + img -> height()/2;
    y3 = -1*(tmp3.y/(double)(1+((double) tmp3.z/d))) + img -> height()/2;
    y4 = -1*(tmp4.y/(double)(1+((double) tmp4.z/d))) + img -> height()/2;
    drawLine(x1,x2,y1,y2,*white);
    drawLine(x1-1,x2-1,y1,y2,*white);
    drawLine(x1+1,x2+1,y1,y2,*white);
    drawLine(x1,x2,y1-1,y2-1,*white);
    drawLine(x1,x2,y1+1,y2+1,*white);
    drawLine(x3,x4,y3,y4,*white);
    drawLine(x3-1,x4-1,y3,y4,*white);
    drawLine(x3+1,x4+1,y3,y4,*white);
    drawLine(x3,x4,y3-1,y4-1,*white);
    drawLine(x3,x4,y3+1,y4+1,*white);

    if(p1.x == p4.x){
        tmp1.x = p1.x;
        tmp3.x = p1.x;
    }else if(min(p1.x,p4.x) == p1.x){
        tmp1.x = p1.x+step;
        tmp3.x = p1.x+(2*step);
    }else{
        tmp1.x = p4.x+step;
        tmp3.x = p4.x+(2*step);
    }
    if(p1.y == p4.y){
        tmp1.y = p1.y;
        tmp3.y = p1.y;
    }else if(min(p1.y,p4.y) == p1.y){
        tmp1.y = p1.y+step;
        tmp3.y = p1.y+(2*step);
    }else{
        tmp1.y = p4.y+step;
        tmp3.y = p4.y+(2*step);
    }
    if(p1.z == p4.z){
        tmp1.z = p1.z;
        tmp3.z = p1.z;
    }else if(min(p1.z,p4.z) == p1.z){
        tmp1.z = p1.z+step;
        tmp3.z = p1.z+(2*step);
    }else{
        tmp1.z = p4.z+step;
        tmp3.z = p4.z+(2*step);
    }

    if(p2.x == p3.x){
        tmp2.x = p2.x;
        tmp4.x = p2.x;
    }else if(min(p2.x,p3.x) == p2.x){
        tmp2.x = p2.x+step;
        tmp4.x = p2.x+(2*step);
    }else{
        tmp2.x = p3.x+step;
        tmp4.x = p3.x+(2*step);
    }
    if(p2.y == p3.y){
        tmp2.y = p2.y;
        tmp4.y = p2.y;
    }else if(min(p2.y,p3.y) == p2.y){
        tmp2.y = p2.y+step;
        tmp4.y = p2.y+(2*step);
    }else{
        tmp2.y = p3.y+step;
        tmp4.y = p3.y+(2*step);
    }
    if(p2.z == p3.z){
        tmp2.z = p2.z;
        tmp4.z = p2.z;
    }else if(min(p2.z,p3.z) == p2.z){
        tmp2.z = p2.z+step;
        tmp4.z = p2.z+(2*step);
    }else{
        tmp2.z = p3.z+step;
        tmp4.z = p3.z+(2*step);
    }
    tmp1 = tmp1.rotate(alpha,beta,0);
    tmp2 = tmp2.rotate(alpha,beta,0);
    tmp3 = tmp3.rotate(alpha,beta,0);
    tmp4 = tmp4.rotate(alpha,beta,0);
    x1 = (tmp1.x/(double)(1+((double) tmp1.z/d))) + img -> width()/2;
    x2 = (tmp2.x/(double)(1+((double) tmp2.z/d))) + img -> width()/2;
    x3 = (tmp3.x/(double)(1+((double) tmp3.z/d))) + img -> width()/2;
    x4 = (tmp4.x/(double)(1+((double) tmp4.z/d))) + img -> width()/2;
    y1 = -1*(tmp1.y/(double)(1+((double) tmp1.z/d))) + img -> height()/2;
    y2 = -1*(tmp2.y/(double)(1+((double) tmp2.z/d))) + img -> height()/2;
    y3 = -1*(tmp3.y/(double)(1+((double) tmp3.z/d))) + img -> height()/2;
    y4 = -1*(tmp4.y/(double)(1+((double) tmp4.z/d))) + img -> height()/2;
    drawLine(x1,x2,y1,y2,*white);
    drawLine(x1-1,x2-1,y1,y2,*white);
    drawLine(x1+1,x2+1,y1,y2,*white);
    drawLine(x1,x2,y1-1,y2-1,*white);
    drawLine(x1,x2,y1+1,y2+1,*white);
    drawLine(x3,x4,y3,y4,*white);
    drawLine(x3-1,x4-1,y3,y4,*white);
    drawLine(x3+1,x4+1,y3,y4,*white);
    drawLine(x3,x4,y3-1,y4-1,*white);
    drawLine(x3,x4,y3+1,y4+1,*white);
}
void MainWidget::drawCube() {
    clearImg();
    for (int i = 0; i < 6; i++){
        drawWall(i);
    }
    repaint();
}
void MainWidget::keyPressEvent(QKeyEvent *event){
    int jump = 25;
    if(event->key() == Qt::Key_Right){
        clearImg();
        beta+=jump;
        beta = beta%360;
        drawCube();
    }else if(event->key() == Qt::Key_Left){
        clearImg();
        beta-=jump;
        beta = beta%360;
        drawCube();
    }else if(event->key() == Qt::Key_Up){
        clearImg();
        alpha+=jump;
        alpha = alpha%360;
        drawCube();
    }else if(event->key() == Qt::Key_Down){
        clearImg();
        alpha-=jump;
        alpha = alpha%360;
        drawCube();
    }else if(event->key() == Qt::Key_W){
        orientation = 0;
    }else if(event->key() == Qt::Key_A){
        orientation = 1;
    }else if(event->key() == Qt::Key_S){
        orientation = 2;
    }else if(event->key() == Qt::Key_D){
        orientation = 3;
    }else if(event->key() == Qt::Key_R){
        destroyCube();
    }
}
void MainWidget::clearImg(){
   for(int i = 0;i<img->width();i++){
       for(int j = 0;j<img->height();j++){
           setPixel(i,j,*black);
       }
   }
}
void MainWidget::fillWall(int i){
    Point3d p1,p2,prev,current,tmp,tmp2;
    int x1,x2,y1,y2,step = (int(2*r / 3.0));
    int moveDirection = 0,direction = 1;
    p1 = points[triangles[2*i][0]];
    p2 = points[triangles[2*i][2]];
    if(p1.x == p2.x){
        moveDirection = 0;
        prev = (min(p1.y,p2.y) == p1.y)?p1:p2;
        tmp = (min(p1.y,p2.y) == p1.y)?p2:p1;
        direction = (prev.z < tmp.z)?1:-1;
    }else if(p1.y == p2.y){
        moveDirection = 1;
        prev = (min(p1.x,p2.x) == p1.x)?p1:p2;
        tmp = (min(p1.x,p2.x) == p1.x)?p2:p1;
        direction = (prev.z < tmp.z)?1:-1;
    }else if(p1.z == p2.z){
        moveDirection = 2;
        prev = (min(p1.x,p2.x) == p1.x)?p1:p2;
        tmp = (min(p1.x,p2.x) == p1.x)?p2:p1;
        direction = (prev.y < tmp.y)?1:-1;
    }
    current = prev;
    tmp = prev;
    tmp2 = prev;
    int count = 0;
    for(int k = 0;k < 3;k++){
        for(int j = 0;j < 3;j++){
            prev = tmp.move(moveDirection,k*step,j*direction*step).rotate(alpha,beta,0);
            current = tmp2.move(moveDirection,(k+1)*step,(j+1)*direction*step).rotate(alpha,beta,0);
            x1 = (prev.x/(double)(1+((double) prev.z/d))) + img -> width()/2;
            x2 = (current.x/(double)(1+((double) current.z/d))) + img -> width()/2;
            y1 = -1*(prev.y/(double)(1+((double) prev.z/d))) + img -> height()/2;
            y2 = -1*(current.y/(double)(1+((double) current.z/d))) + img -> height()/2;
            int xsr = (x1+x2)/2;
            int ysr = (y1+y2)/2;
            pair<int,int> tmp;
            tmp = make_pair(xsr,ysr);
            pointsStack.push(tmp);
            floodFill(*black,walls[i].getTileColor(count)); 
            count++;
        }
    }
}
void MainWidget::floodFill(Color backgroundColor,Color colorToFillWith){
    int x,y;
	pair<int,int> tmp;
	while(!pointsStack.empty()){
		x = pointsStack.top().first;
		y = pointsStack.top().second;
		pointsStack.pop();
        Color *tmpColor = getColorFromPixel(x,y);
		if(*tmpColor == backgroundColor){
			setPixel(x,y,colorToFillWith);
			if(x+1 < img->width()){
				tmp.first = x+1;
				tmp.second = y;
				pointsStack.push(tmp);
			}
			if(y+1 < img->height()){
				tmp.first = x;
				tmp.second = y+1;
				pointsStack.push(tmp);
			}
			if(x-1 > 0){
				tmp.first = x-1;
				tmp.second = y;
				pointsStack.push(tmp);
			}
			if(y-1 > 0){
				tmp.first = x;
				tmp.second = y-1;
				pointsStack.push(tmp);
			}
		}
        delete tmpColor;
	}
}
Color* MainWidget::getColorFromPixel(int x,int y){
    unsigned char *ptr = (unsigned char*)img->bits();
	int w = img -> width();
    return new Color(ptr[4*(x+y*w)],ptr[4*(x+y*w)+1],ptr[4*(x+y*w)+ 2],ptr[4*(x+y*w)+ 3]);
}
void MainWidget::initializeTiles(){
    for(int i = 0;i < 6;i++){
        for(int j = 0;j < 9;j++){
            walls[i].tiles[j] = 9*i+j;
        }
    }
}
void MainWidget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton ){
        if(orientation == 3){
            rotateRight('r');
        }else if(orientation == 1){
            rotateLeft('r');
        }else if(orientation == 0){
            rotateUp('r');
        }else if(orientation == 2){
            rotateDown('r');
        }
    }else{
        if(orientation == 3){
            rotateRight('l');
        }else if(orientation == 1){
            rotateLeft('l');
        }else if(orientation == 0){
            rotateUp('l');
        }else if(orientation == 2){
            rotateDown('l');
        }
    }
    drawCube();
}
void MainWidget::rotateLeft(char side){
    int tmp[3];
    if(side == 'l'){
        tmp[0] = walls[4].tiles[0];
        tmp[1] = walls[4].tiles[1];
        tmp[2] = walls[4].tiles[2];
        walls[4].tiles[0] = walls[0].tiles[0];
        walls[4].tiles[1] = walls[0].tiles[1];
        walls[4].tiles[2] = walls[0].tiles[2];

        walls[0].tiles[0] = walls[5].tiles[0];
        walls[0].tiles[1] = walls[5].tiles[1];
        walls[0].tiles[2] = walls[5].tiles[2];

        walls[5].tiles[0] = walls[2].tiles[0];
        walls[5].tiles[1] = walls[2].tiles[1];
        walls[5].tiles[2] = walls[2].tiles[2];

        walls[2].tiles[0] = tmp[0];
        walls[2].tiles[1] = tmp[1];
        walls[2].tiles[2] = tmp[2];
        walls[3].rotate('l');
    }else{
        tmp[0] = walls[4].tiles[0];
        tmp[1] = walls[4].tiles[1];
        tmp[2] = walls[4].tiles[2];
        walls[4].tiles[0] = walls[2].tiles[0];
        walls[4].tiles[1] = walls[2].tiles[1];
        walls[4].tiles[2] = walls[2].tiles[2];

        walls[2].tiles[0] = walls[5].tiles[0];
        walls[2].tiles[1] = walls[5].tiles[1];
        walls[2].tiles[2] = walls[5].tiles[2];

        walls[5].tiles[0] = walls[0].tiles[0];
        walls[5].tiles[1] = walls[0].tiles[1];
        walls[5].tiles[2] = walls[0].tiles[2];

        walls[0].tiles[0] = tmp[0];
        walls[0].tiles[1] = tmp[1];
        walls[0].tiles[2] = tmp[2];
        walls[3].rotate('r');
    }
}
void MainWidget::rotateRight(char side){
    int tmp[3];
    if(side == 'r'){
        tmp[0] = walls[4].tiles[6];
        tmp[1] = walls[4].tiles[7];
        tmp[2] = walls[4].tiles[8];
        walls[4].tiles[6] = walls[2].tiles[6];
        walls[4].tiles[7] = walls[2].tiles[7];
        walls[4].tiles[8] = walls[2].tiles[8];

        walls[2].tiles[6] = walls[5].tiles[6];
        walls[2].tiles[7] = walls[5].tiles[7];
        walls[2].tiles[8] = walls[5].tiles[8];

        walls[5].tiles[6] = walls[0].tiles[6];
        walls[5].tiles[7] = walls[0].tiles[7];
        walls[5].tiles[8] = walls[0].tiles[8];

        walls[0].tiles[6] = tmp[0];
        walls[0].tiles[7] = tmp[1];
        walls[0].tiles[8] = tmp[2];
        walls[1].rotate('r');
    }else{
        tmp[0] = walls[4].tiles[6];
        tmp[1] = walls[4].tiles[7];
        tmp[2] = walls[4].tiles[8];
        walls[4].tiles[6] = walls[0].tiles[6];
        walls[4].tiles[7] = walls[0].tiles[7];
        walls[4].tiles[8] = walls[0].tiles[8];

        walls[0].tiles[6] = walls[5].tiles[6];
        walls[0].tiles[7] = walls[5].tiles[7];
        walls[0].tiles[8] = walls[5].tiles[8];

        walls[5].tiles[6] = walls[2].tiles[6];
        walls[5].tiles[7] = walls[2].tiles[7];
        walls[5].tiles[8] = walls[2].tiles[8];

        walls[2].tiles[6] = tmp[0];
        walls[2].tiles[7] = tmp[1];
        walls[2].tiles[8] = tmp[2];
        walls[1].rotate('l');
    }
}
void MainWidget::rotateDown(char side){
    int tmp[3];
    if(side == 'l'){
        tmp[0] = walls[1].tiles[0];
        tmp[1] = walls[1].tiles[1];
        tmp[2] = walls[1].tiles[2];
        walls[1].tiles[0] = walls[2].tiles[8];
        walls[1].tiles[1] = walls[2].tiles[5];
        walls[1].tiles[2] = walls[2].tiles[2];

        walls[2].tiles[8] = walls[3].tiles[0];
        walls[2].tiles[5] = walls[3].tiles[1];
        walls[2].tiles[2] = walls[3].tiles[2];

        walls[3].tiles[0] = walls[0].tiles[0];
        walls[3].tiles[1] = walls[0].tiles[3];
        walls[3].tiles[2] = walls[0].tiles[6];

        walls[0].tiles[0] = tmp[0];
        walls[0].tiles[3] = tmp[1];
        walls[0].tiles[6] = tmp[2];
        walls[5].rotate('l');
    }else{
        tmp[0] = walls[1].tiles[0];
        tmp[1] = walls[1].tiles[1];
        tmp[2] = walls[1].tiles[2];
        walls[1].tiles[0] = walls[0].tiles[0];
        walls[1].tiles[1] = walls[0].tiles[3];
        walls[1].tiles[2] = walls[0].tiles[6];

        walls[0].tiles[0] = walls[3].tiles[0];
        walls[0].tiles[3] = walls[3].tiles[1];
        walls[0].tiles[6] = walls[3].tiles[2];

        walls[3].tiles[0] = walls[2].tiles[8];
        walls[3].tiles[1] = walls[2].tiles[5];
        walls[3].tiles[2] = walls[2].tiles[2];

        walls[2].tiles[8] = tmp[0];
        walls[2].tiles[5] = tmp[1];
        walls[2].tiles[2] = tmp[2];
        walls[5].rotate('r');
    }
}
void MainWidget::rotateUp(char side){
    int tmp[3];
    if(side == 'r'){
        tmp[0] = walls[1].tiles[6];
        tmp[1] = walls[1].tiles[7];
        tmp[2] = walls[1].tiles[8];
        walls[1].tiles[6] = walls[0].tiles[2];
        walls[1].tiles[7] = walls[0].tiles[5];
        walls[1].tiles[8] = walls[0].tiles[8];

        walls[0].tiles[2] = walls[3].tiles[6];
        walls[0].tiles[5] = walls[3].tiles[7];
        walls[0].tiles[8] = walls[3].tiles[8];

        walls[3].tiles[6] = walls[2].tiles[6];
        walls[3].tiles[7] = walls[2].tiles[3];
        walls[3].tiles[8] = walls[2].tiles[0];

        walls[2].tiles[6] = tmp[0];
        walls[2].tiles[3] = tmp[1];
        walls[2].tiles[0] = tmp[2];
        walls[4].rotate('r');
    }else{
        tmp[0] = walls[1].tiles[6];
        tmp[1] = walls[1].tiles[7];
        tmp[2] = walls[1].tiles[8];
        walls[1].tiles[6] = walls[2].tiles[6];
        walls[1].tiles[7] = walls[2].tiles[3];
        walls[1].tiles[8] = walls[2].tiles[0];

        walls[2].tiles[6] = walls[3].tiles[6];
        walls[2].tiles[3] = walls[3].tiles[7];
        walls[2].tiles[0] = walls[3].tiles[8];

        walls[3].tiles[6] = walls[0].tiles[2];
        walls[3].tiles[7] = walls[0].tiles[5];
        walls[3].tiles[8] = walls[0].tiles[8];

        walls[0].tiles[2] = tmp[0];
        walls[0].tiles[5] = tmp[1];
        walls[0].tiles[8] = tmp[2];
        walls[4].rotate('l');
    }
}
void MainWidget::destroyCube(){
    srand(time(0));
    for(int i = 0;i < 12;i++){
        int option = rand()%8;
        switch(option){
            case 0:
                rotateDown('l');
                break;
            case 1:
                rotateDown('r');
                break;
            case 2:
                rotateLeft('l');
                break;
            case 3:
                rotateLeft('r');
                break;
            case 4:
                rotateUp('l');
                break;
            case 5:
                rotateUp('r');
                break;
            case 6:
                rotateRight('l');
                break;
            case 7:
                rotateRight('r');
                break;
        }
    }
    drawCube();
}