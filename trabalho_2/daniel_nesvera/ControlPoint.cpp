/**
 * @file    ControlPoint.cpp
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Classe com herança da classe DrawComponent.
 *    Implementa pontos de controle para as formas
 *
 */

#include "ControlPoint.h"
#include "glCanvas2d.h"
#include "mainwindow.h"

#include <math.h>
#include <QMessageBox>
#include <QWheelEvent>

#include "Point.h"
#include "ControlPoint.h"

ControlPoint::ControlPoint(float _x0, float _y0, int w, int h):DrawComponent(){
    x0 = _x0/w;
    y0 = _y0/h;
}

void ControlPoint::render(Canvas2D *canvas, int w, int h){
    canvas->rectFill((x0*w-width/2), (y0*h-height/2), (x0*w+width/2), (y0*h+height/2));
}

void ControlPoint::mouseMoveHandler(int x, int y, int w, int h){

}

void ControlPoint::setPosition(int x, int y, int w, int h){
    x0 = (float)x/w;
    y0 = (float)y/h;
}

float ControlPoint::getX(){
    return x0;
}

float ControlPoint::getY(){
    return y0;
}

bool ControlPoint::mouseSelectClickHandler(int x, int y, int w, int h){
    int mouseSpeed = 30;

    if((x >= (x0*w-width/2-mouseSpeed)) && (x <= (x0*w+width/2+mouseSpeed))){
        if((y >= (y0*h-height/2-mouseSpeed)) && (y <= (y0*h+height/2+mouseSpeed))){
            return true;
        }
    }

    return false;
}

int ControlPoint::getMemSize(){
    int sizeSum = 0;

    // posicao x - 1 float
    sizeSum += sizeof(x0);

    // posicao y - 1 float
    sizeSum += sizeof(y0);

    return sizeSum;
}

void ControlPoint::saveComponent(FILE *f){
    fwrite(&x0, sizeof(x0), 1, f);
    fwrite(&y0, sizeof(y0), 1, f);
}
