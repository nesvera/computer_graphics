/**
 * @file    Line.cpp
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Classe com herança da classe DrawComponent.
 *    Implementa linha
 *
 */

#include "Line.h"

Line::Line(float _x0, float _y0, int w, int h, int type){
    x0 = (_x0)/w;
    y0 = (_y0)/h;
    x1 = (_x0)/w;
    y1 = (_y0)/h;

    controlPoints.push_back(new ControlPoint(_x0, _y0, w, h));
    controlPoints.push_back(new ControlPoint(_x0, _y0, w, h));

    componentType = type;
    qntControlPoints = 2;
}

void Line::render(Canvas2D *canvas, int w, int h){
    list<ControlPoint*>::iterator it;
    it = controlPoints.begin();
    ControlPoint *p0 = (*it);
    it++;
    ControlPoint *p1 = (*it);

    // Seleciona a cor
    canvas->color(0,0,0);

    canvas->line(p0->getX()*w, p0->getY()*h, p1->getX()*w, p1->getY()*h);

    if(isSelected == true){
        // draw bounding box
        canvas->color(1,0,0);
        canvas->rect(p0->getX()*w, p0->getY()*h, p1->getX()*w, p1->getY()*h);

        // desenha os controlpoints
        p0->render(canvas, w, h);
        p1->render(canvas, w, h);
    }

}

void Line::mouseMoveHandler(int x, int y, int w, int h){

    if(isSelected){
        list<ControlPoint*>::iterator it;
        for(it = controlPoints.begin() ; it != controlPoints.end() ; ++it){
            bool somethingSelected = (*it)->mouseSelectClickHandler(x, y, w, h);

            if(somethingSelected){

                (*it)->setPosition(x, y, w, h);
                return;
            }
        }

        Point centerPoint = Point(0, 0);
        // Se o clique nao foi nos pontos de controle, transladar objeto
        for(it = controlPoints.begin() ; it != controlPoints.end() ; ++it){
            centerPoint.x += (*it)->getX()*w;
            centerPoint.y += (*it)->getY()*h;
        }
        centerPoint.x /= controlPoints.size();
        centerPoint.y /= controlPoints.size();

        Point difCenterToMouse = Point(centerPoint.x-x, centerPoint.y-y);

        for(it = controlPoints.begin() ; it != controlPoints.end() ; ++it){
            float nX = (*it)->getX()*w - difCenterToMouse.x;
            float nY = (*it)->getY()*h - difCenterToMouse.y;

            (*it)->setPosition(nX, nY, w, h);
        }
    }
}

bool Line::mouseSelectClickHandler(int x, int y, int w, int h){

    list<ControlPoint*>::iterator it;
    it = controlPoints.begin();
    ControlPoint *p0 = (*it);
    it++;
    ControlPoint *p1 = (*it);

    float dist_c_p0 = sqrt((pow(p0->getX()*w-x,2))+(pow(p0->getY()*h-y,2)));
    float dist_c_p1 = sqrt((pow(p1->getX()*w-x,2))+(pow(p1->getY()*h-y,2)));
    float dist_p0_p1 = sqrt((pow(p1->getX()*w-p0->getX()*w,2))+(pow(p1->getY()*h-p0->getY()*h,2)));

    float distDif = abs((dist_c_p0+dist_c_p1) - dist_p0_p1);

    if(distDif < 10){
        isSelected = true;
        return true;
    }else{
        isSelected = false;
        return false;
    }

}

int Line::getMemSize(){
    int sizeSum = 0;

    // tipo - 1 int
    sizeSum += sizeof(componentType);

    // numeros de pontos de controle - 1 int
    sizeSum += sizeof(qntControlPoints);

    // pontos de controle - 2 float por ponto
    list<ControlPoint*>::iterator it;
    for(it = controlPoints.begin() ; it != controlPoints.end() ; ++it){
        sizeSum += (*it)->getMemSize();
    }

    return sizeSum;
}

void Line::saveComponent(FILE *f){
    fwrite(&componentType, sizeof(componentType), 1, f);
    fwrite(&qntControlPoints, sizeof(qntControlPoints), 1, f);

    list<ControlPoint*>::iterator it;
    for(it = controlPoints.begin() ; it != controlPoints.end() ; ++it){
        (*it)->saveComponent(f);
    }
}

void Line::setControlPoint(int x, int y, int w, int h, int n){
    list<ControlPoint*>::iterator it;
    it = controlPoints.begin();
    (*it)->setPosition(x, y, w, h);
}
