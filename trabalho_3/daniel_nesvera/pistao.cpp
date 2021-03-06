/**
 * @file    pistao.cpp
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Modelagem do pistao
 *
 */

#include "pistao.h"

Pistao::Pistao(Vector3 *posInit, Vector3 *right, Vector3 *up, Vector3 *forward)
{
    Vector3 center = (*posInit);

    /**************** Face 1 - Circle 1 *************/
    int div = 25;
    float raio = 60;
    float step = (2*M_PI)/(float)div;

    Vector3 cyl0Init(center.x, center.y, center.z);
    float length = 120;
    int divHor = 9;
    float stepHor = length/(float)(divHor-1);
    Vector3 cylinder0[div][divHor];

    int lin = 0;
    int col = 0;

    for(float i=0 ; i<2*M_PI; i+=step){

        for(float j=0; j<=length ; j+=stepHor){

            // circle
            Vector3 p0 = cyl0Init;
            p0 += (*forward)*(raio*cos(i));
            p0 += (*right)*(raio*sin(i));

            // forward to cylinder
            p0 += (*up)*j;
            //qDebug("%d %d - %f", lin, col, p0.x);

            cylinder0[lin][col] = p0;
            col++;
        }

        lin++;
        col = 0;
    }

    for(int i=0 ; i<div ; i++){             //linha
        for(int j=0 ; j<divHor ; j++){      //coluna

            // Horizontal lines
            if(j!=(divHor-1)){     // se nao for a ultima coluna
                edgeTable.push_back(new Edge(cylinder0[i][j], cylinder0[i][j+1]));
            }

            // Vertical lines
            if(i!=(div-1)){           // se nao for a ultima linha
                edgeTable.push_back(new Edge(cylinder0[i][j], cylinder0[i+1][j]));

            }else{                  // ultima linha é ligada com a primeira
                edgeTable.push_back(new Edge(cylinder0[i][j], cylinder0[0][j]));
            }

        }
    }

    /**************** Face 1 - Circle 1 *************/
    step = (2*M_PI)/(float)div;

    center.y += length;

    for(float i=0 ; i<2*M_PI; i+=step){

        Vector3 p0 = center;
        p0 += (*forward)*(raio*cos(i));
        p0 += (*right)*(raio*sin(i));

        Vector3 p1 = center;
        p1 += (*forward)*(raio*cos(i+step));
        p1 += (*right)*(raio*sin(i+step));

        edgeTable.push_back(new Edge(center, p0));
        edgeTable.push_back(new Edge(center, p1));
        edgeTable.push_back(new Edge(p0,p1));
    }

}

void Pistao::render(Canvas2D *canvas, Matrix4 *renderMat, int canvasWidth, int canvasHeight){

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

void Pistao::update(float distance){
    // rotaciona o virabrequim em torno de x

    Matrix4 offset(1, 0,        0, 0,
                   0, 1,        0, 0,
                   0, 0,        1, 0,
                   0, distance, 0, 1);

    list<Edge*>::iterator it;

    for (it = edgeTable.begin(); it != edgeTable.end(); ++it){
        Vector3 *p0 = new Vector3((*it)->v0->x, (*it)->v0->y, (*it)->v0->z);
        Vector3 *p1 = new Vector3((*it)->v1->x, (*it)->v1->y, (*it)->v1->z);

        *p0 = (offset)*(*p0);
        *p1 = (offset)*(*p1);

        (*it)->v0->x = p0->x;
        (*it)->v0->y = p0->y;
        (*it)->v0->z = p0->z;

        (*it)->v1->x = p1->x;
        (*it)->v1->y = p1->y;
        (*it)->v1->z = p1->z;

        delete p0;
        delete p1;
    }
}
