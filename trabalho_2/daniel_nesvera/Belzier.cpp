/**
 * @file    Belzier.cpp
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Classe com herança da classe DrawComponent.
 *    Implementa curvas de belzier
 *
 */

#include "Belzier.h"

Belzier::Belzier(float _x0, float _y0, int w, int h, int type){
    x0 = (_x0)/w;
    y0 = (_y0)/h;
    x1 = (_x0)/w;
    y1 = (_y0)/h;

    controlPoints.push_back(new ControlPoint(_x0, _y0, w, h));

    componentType = type;
    qntControlPoints = 1;

    isClosed = false;
}

void Belzier::render(Canvas2D *canvas, int w, int h){
    Point p0 = Point(0, 0);
    Point p1 = Point(0, 0);

    list<ControlPoint*>::iterator it;
    for(it = controlPoints.begin() ; (it) != controlPoints.end() ;){
        p0.x = (*it)->getX();
        p0.y = (*it)->getY();

        canvas->rect(p0.x*w-10, p0.y*h-10, p1.x*w+10, p1.y*h+10);

        /*
        it--;
        p0.x = (*it)->getX();
        p0.y = (*it)->getY();

        if(!isClosed){
            p1.x = (*it+1)->getX();
            p1.y = (*it+1)->getY();
        }else{
            list<ControlPoint*>::iterator first;
            first = controlPoints.begin();
            p1.x = (*first)->getX();
            p1.y = (*first)->getY();
        }

        canvas->line(p0.x*w, p0.y*h, p1.x*w, p1.y*h);
        */
    }


    // Seleciona a cor
    canvas->color(0,0,0);


    if(isSelected == true){
        // draw bounding box
        //canvas->color(1,0,0);
        //canvas->rect(p0->getX()*w, p0->getY()*h, p1->getX()*w, p1->getY()*h);

        // desenha os controlpoints
        for(it = controlPoints.begin() ; it != controlPoints.end() ;){
            (*it)->render(canvas, w, h);
        }
    }

}

void Belzier::mouseMoveHandler(int x, int y, int w, int h){

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

bool Belzier::mouseSelectClickHandler(int x, int y, int w, int h){

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

int Belzier::getMemSize(){
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

void Belzier::saveComponent(FILE *f){
    fwrite(&componentType, sizeof(componentType), 1, f);
    fwrite(&qntControlPoints, sizeof(qntControlPoints), 1, f);

    list<ControlPoint*>::iterator it;
    for(it = controlPoints.begin() ; it != controlPoints.end() ; ++it){
        (*it)->saveComponent(f);
    }
}

void Belzier::setControlPoint(int x, int y, int w, int h, int n){
    list<ControlPoint*>::iterator it;
    it = controlPoints.begin();
    (*it)->setPosition(x, y, w, h);
}

void Belzier::addControlPoint(int x, int y, int w, int h){
    controlPoints.push_back(new ControlPoint(x, y, w, h));
    qntControlPoints++;
}
