/**
 * @file    Circ.cpp
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Classe com herança da classe DrawComponent.
 *    Implementa círculo
 *
 */

#include "Circ.h"
#include <algorithm>

Circ::Circ(float _x0, float _y0, int w, int h, int type){
    x0 = (_x0)/w;
    y0 = (_y0)/h;
    x1 = (_x0)/w;
    y1 = (_y0)/h;

    controlPoints.push_back(new ControlPoint(_x0, _y0, w, h));
    controlPoints.push_back(new ControlPoint(_x0, _y0, w, h));

    componentType = type;
    qntControlPoints = 2;
}

void Circ::render(Canvas2D *canvas, int w, int h){
    list<ControlPoint*>::iterator it;
    it = controlPoints.begin();
    ControlPoint *p0 = (*it);
    it++;
    ControlPoint *p1 = (*it);

    // Seleciona a cor
    canvas->color(0,0,0);

    float raio = sqrt(pow(p0->getX()*w - p1->getX()*w,2) + pow(p0->getY()*h - p1->getY()*h,2));
    canvas->circle(p1->getX()*w, p1->getY()*h, raio, 100);


    if(isSelected == true){
        int boundBoxSpace = 0;
        // draw bounding box
        canvas->color(1,0,0);

        canvas->rect(p1->getX()*w-raio, p1->getY()*h-raio, p1->getX()*w+raio, p1->getY()*h+raio);

        // desenha os controlpoints
        p0->render(canvas, w, h);
        //p1->render(canvas, w, h);
    }


}

void Circ::mouseMoveHandler(int x, int y, int w, int h){

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

bool Circ::mouseSelectClickHandler(int x, int y, int w, int h){

    list<ControlPoint*>::iterator it;
    it = controlPoints.begin();
    ControlPoint *p0 = (*it);
    it++;
    ControlPoint *p1 = (*it);

    int bb = 5;

    float raio = sqrt(pow(p0->getX()*w - p1->getX()*w,2) + pow(p0->getY()*h - p1->getY()*h,2));

    if((x >= p1->getX()*w-raio-bb) && (x <= p1->getX()*w+raio+bb)){
        if((y >= p1->getY()*h-raio-bb) && (y <= p1->getY()*h+raio+bb)){
            isSelected = true;
            return true;
        }
    }


    isSelected = false;
    return false;
}

int Circ::getMemSize(){
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

void Circ::saveComponent(FILE *f){
    fwrite(&componentType, sizeof(componentType), 1, f);
    fwrite(&qntControlPoints, sizeof(qntControlPoints), 1, f);

    list<ControlPoint*>::iterator it;
    for(it = controlPoints.begin() ; it != controlPoints.end() ; ++it){
        (*it)->saveComponent(f);
    }
}

void Circ::setControlPoint(int x, int y, int w, int h, int n){
    list<ControlPoint*>::iterator it;
    it = controlPoints.begin();
    (*it)->setPosition(x, y, w, h);
}
