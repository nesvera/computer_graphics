/**
 * @file    biela.cpp
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Modelagem da biela
 *
 */

#include "biela.h"


Biela::Biela(Vector3 *posInit)
{
    pos = (*posInit);
    width = 80;
    height = 510;
    depth = 80;

    Cubo b = Cubo(posInit,
                  width, height, depth,
                  new Vector3(1,0,0), new Vector3(0,1,0), new Vector3(0,0,1),
                  &edgeTable, 5);

}

void Biela::render(Canvas2D *canvas, Matrix4 *renderMat, int canvasWidth, int canvasHeight){

    list<Edge*>::iterator it;
    // Visualização 3D
    for (it = edgeTable.begin(); it != edgeTable.end(); ++it){
        Vector3 *p0 = new Vector3((*it)->v0->x, (*it)->v0->y, (*it)->v0->z);
        Vector3 *p1 = new Vector3((*it)->v1->x, (*it)->v1->y, (*it)->v1->z);

        *p0 = (*renderMat)*(*p0);
        p0->x = (int)((p0->x+1.0f)*(canvasWidth)/2.0f);
        p0->y = (int)((p0->y+1.0f)*(canvasHeight)/2.0f);

        *p1 = (*renderMat)*(*p1);
        p1->x = (int)((p1->x+1.0f)*(canvasWidth)/2.0f);
        p1->y = (int)((p1->y+1.0f)*(canvasHeight)/2.0f);

        canvas->line(p0->x, p0->y, p1->x, p1->y);

        delete p0;
        delete p1;
    }

    // Visualização em x-y
    for (it = edgeTable.begin(); it != edgeTable.end(); ++it){
        //canvas->line((*it)->v0->x, (*it)->v0->y, (*it)->v1->x, (*it)->v1->y);
    }

    // Visualização em z-y

    /*for (it = edgeTable.begin(); it != edgeTable.end(); ++it){
        canvas->line((*it)->v0->x, (*it)->v0->z, (*it)->v1->x, (*it)->v1->z);
    }*/

}
