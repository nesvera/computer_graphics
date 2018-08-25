/**
 * @file    Rect.cpp
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Classe com herança da classe DrawComponent.
 *    Implementa retângulo
 *
 */

#include "Rect.h"
#include <algorithm>

Rect::Rect(float _x0, float _y0, int w, int h, int type){
    x0 = (_x0)/w;
    y0 = (_y0)/h;
    x1 = (_x0)/w;
    y1 = (_y0)/h;

    controlPoints.push_back(new ControlPoint(_x0, _y0, w, h));
    controlPoints.push_back(new ControlPoint(_x0, _y0, w, h));


    P0 = new Point(_x0/w, _y0/h);
    P1 = new Point(_x0/w, _y0/h);
    P2 = new Point(_x0/w, _y0/h);
    P3 = new Point(_x0/w, _y0/h);

    componentType = type;
    qntControlPoints = 2;
}

void Rect::render(Canvas2D *canvas, int w, int h){
    list<ControlPoint*>::iterator it;
    it = controlPoints.begin();
    ControlPoint *p0 = (*it);
    it++;
    ControlPoint *p1 = (*it);

    // Seleciona a cor
    canvas->color(0,0,0);

    canvas->rect(p0->getX()*w, p0->getY()*h, p1->getX()*w, p1->getY()*h);

    if(isSelected == true){
        int boundBoxSpace = 0;
        // draw bounding box
        canvas->color(1,0,0);
        canvas->rect(p0->getX()*w-boundBoxSpace, p0->getY()*h-boundBoxSpace, p1->getX()*w+boundBoxSpace, p1->getY()*h+boundBoxSpace);

        // desenha os controlpoints
        p0->render(canvas, w, h);
        p1->render(canvas, w, h);
    }

}

void Rect::mouseMoveHandler(int x, int y, int w, int h){

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

bool Rect::mouseSelectClickHandler(int x, int y, int w, int h){

    list<ControlPoint*>::iterator it;
    it = controlPoints.begin();
    ControlPoint *p0 = (*it);
    it++;
    ControlPoint *p1 = (*it);

    int bb = 5;

    float minX = min(p0->getX(), p1->getX());
    float maxX = max(p0->getX(), p1->getX());
    float minY = min(p0->getY(), p1->getY());
    float maxY = max(p0->getY(), p1->getY());

    if((x >= minX*w-bb) && (x <= maxX*w+bb)){
        if((y >= minY*h-bb) && (y <= maxY*h+bb)){
            isSelected = true;
            return true;
        }
    }


    isSelected = false;
    return false;
}

int Rect::getMemSize(){
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

void Rect::saveComponent(FILE *f){
    fwrite(&componentType, sizeof(componentType), 1, f);
    fwrite(&qntControlPoints, sizeof(qntControlPoints), 1, f);

    list<ControlPoint*>::iterator it;
    for(it = controlPoints.begin() ; it != controlPoints.end() ; ++it){
        (*it)->saveComponent(f);
    }
}

void Rect::setControlPoint(int x, int y, int w, int h, int n){
    list<ControlPoint*>::iterator it;
    it = controlPoints.begin();
    (*it)->setPosition(x, y, w, h);
}

