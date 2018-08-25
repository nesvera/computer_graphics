/**
 * @file    virabrequim.cpp
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Modelagem do virabrequim
 *
 * Nao repara a bagunça
 *
 * "Ainda que eu andasse pelo vale da sombra da morte,
 * não temeria mal algum, porque tu estás comigo;
 * a tua vara e o teu cajado me consolam." - Salmos 23:4
 *
 */

#include "Virabrequim.h"
#include "Vector3.h"
#include "matrix4.h"

Virabrequim::Virabrequim(Vector3 *posInit, Vector3 *right, Vector3 *up, Vector3 *forward)
{
    //Vector3 center = Vector3(100,350,300);
    center = (*posInit);

    /**************** Face 1 - Circle 1 *************/
    int div = 20;
    float raio = 100;
    float step = (2*M_PI)/(float)div;

    for(float i=0 ; i<2*M_PI; i+=step){

        Vector3 p0 = center;
        p0 += (*up)*(raio*cos(i));
        p0 += (*right)*(raio*sin(i));

        Vector3 p1 = center;
        p1 += (*up)*(raio*cos(i+step));
        p1 += (*right)*(raio*sin(i+step));

        edgeTable.push_back(new Edge(center, p0));
        edgeTable.push_back(new Edge(center, p1));
        edgeTable.push_back(new Edge(p0,p1));
    }

    /**************** Face 2 - Cylinder 1 *************/
    Vector3 cyl0Init(center.x, center.y, center.z);
    float length = 200;
    int divHor = 10;
    float stepHor = length/(float)(divHor-1);
    Vector3 cylinder0[div][divHor];

    int lin = 0;
    int col = 0;

    for(float i=0 ; i<2*M_PI; i+=step){

        for(float j=0; j<=length ; j+=stepHor){

            // circle
            Vector3 p0 = cyl0Init;
            p0 += (*up)*(raio*cos(i));
            p0 += (*right)*(raio*sin(i));

            // forward to cylinder
            p0 += (*forward)*j;
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

    /**************** Face 2 - Circle 2 *************/
    Vector3 cyl1Init(cyl0Init.x+200, cyl0Init.y, cyl0Init.z);
    raio = 200;

    for(float i=0 ; i<2*M_PI; i+=step){

        Vector3 p0 = cyl1Init;
        p0 += (*up)*(raio*cos(i));
        p0 += (*right)*(raio*sin(i));

        Vector3 p1 = cyl1Init;
        p1 += (*up)*(raio*cos(i+step));
        p1 += (*right)*(raio*sin(i+step));

        edgeTable.push_back(new Edge(cyl1Init, p0));
        edgeTable.push_back(new Edge(cyl1Init, p1));
        edgeTable.push_back(new Edge(p0,p1));
    }

    /**************** Face 3 - Cylinder 2 *************/
    length = 50;
    divHor = 3;
    stepHor = length/(float)(divHor-1);
    Vector3 cylinder1[div][divHor];

    lin = 0;
    col = 0;

    for(float i=0 ; i<2*M_PI; i+=step){

        for(float j=0; j<=length ; j+=stepHor){

            // circle
            Vector3 p0 = cyl1Init;
            p0 += (*up)*(raio*cos(i));
            p0 += (*right)*(raio*sin(i));

            // forward to cylinder
            p0 += (*forward)*j;
            //qDebug("%f", p0.x);

            cylinder1[lin][col] = p0;
            col++;
        }

        lin++;
        col = 0;
    }

    for(int i=0 ; i<div ; i++){             //linha
        for(int j=0 ; j<divHor ; j++){      //coluna

            // Horizontal lines
            if(j!=(divHor-1)){     // se nao for a ultima coluna
                edgeTable.push_back(new Edge(cylinder1[i][j], cylinder1[i][j+1]));
            }

            // Vertical lines
            if(i!=(div-1)){           // se nao for a ultima linha
                edgeTable.push_back(new Edge(cylinder1[i][j], cylinder1[i+1][j]));

            }else{                  // ultima linha é ligada com a primeira
                edgeTable.push_back(new Edge(cylinder1[i][j], cylinder1[0][j]));
            }

        }
    }

    /**************** Face 4 - Circle 3 *************/
    cyl1Init.x += 50;
    raio = 200;

    for(float i=0 ; i<2*M_PI; i+=step){

        Vector3 p0 = cyl1Init;
        p0 += (*up)*(raio*cos(i));
        p0 += (*right)*(raio*sin(i));

        Vector3 p1 = cyl1Init;
        p1 += (*up)*(raio*cos(i+step));
        p1 += (*right)*(raio*sin(i+step));

        edgeTable.push_back(new Edge(cyl1Init, p0));
        edgeTable.push_back(new Edge(cyl1Init, p1));
        edgeTable.push_back(new Edge(p0,p1));
    }

    /**************** Face 5 - Cylinder 3 *************/
    cyl1Init.y += 100;
    length = 80;
    raio = 30;
    divHor = 10;
    stepHor = length/(float)(divHor-1);
    Vector3 cylinder2[div][divHor];

    lin = 0;
    col = 0;

    for(float i=0 ; i<2*M_PI; i+=step){

        for(float j=0; j<=length ; j+=stepHor){

            // circle
            Vector3 p0 = cyl1Init;
            p0 += (*up)*(raio*cos(i));
            p0 += (*right)*(raio*sin(i));

            // forward to cylinder
            p0 += (*forward)*j;
            //qDebug("%f", p0.x);

            cylinder2[lin][col] = p0;
            col++;
        }

        lin++;
        col = 0;
    }

    for(int i=0 ; i<div ; i++){             //linha
        for(int j=0 ; j<divHor ; j++){      //coluna

            // Horizontal lines
            if(j!=(divHor-1)){     // se nao for a ultima coluna
                edgeTable.push_back(new Edge(cylinder2[i][j], cylinder2[i][j+1]));
            }

            // Vertical lines
            if(i!=(div-1)){           // se nao for a ultima linha
                edgeTable.push_back(new Edge(cylinder2[i][j], cylinder2[i+1][j]));

            }else{                  // ultima linha é ligada com a primeira
                edgeTable.push_back(new Edge(cylinder2[i][j], cylinder2[0][j]));
            }

        }
    }

    /**************** Face 6 - Circle 4 *************/
    cyl1Init.y -= 100;
    cyl1Init.x += 80;
    raio = 200;

    for(float i=0 ; i<2*M_PI; i+=step){

        Vector3 p0 = cyl1Init;
        p0 += (*up)*(raio*cos(i));
        p0 += (*right)*(raio*sin(i));

        Vector3 p1 = cyl1Init;
        p1 += (*up)*(raio*cos(i+step));
        p1 += (*right)*(raio*sin(i+step));

        edgeTable.push_back(new Edge(cyl1Init, p0));
        edgeTable.push_back(new Edge(cyl1Init, p1));
        edgeTable.push_back(new Edge(p0,p1));
    }

    /**************** Face 7 - Cylinder 4 *************/
    length = 50;
    raio = 200;

    divHor = 3;
    stepHor = length/(float)(divHor-1);
    Vector3 cylinder4[div][divHor];

    lin = 0;
    col = 0;

    for(float i=0 ; i<2*M_PI; i+=step){

        for(float j=0; j<=length ; j+=stepHor){

            // circle
            Vector3 p0 = cyl1Init;
            p0 += (*up)*(raio*cos(i));
            p0 += (*right)*(raio*sin(i));

            // forward to cylinder
            p0 += (*forward)*j;
            //qDebug("%f", p0.x);

            cylinder4[lin][col] = p0;
            col++;
        }

        lin++;
        col = 0;
    }

    for(int i=0 ; i<div ; i++){             //linha
        for(int j=0 ; j<divHor ; j++){      //coluna

            // Horizontal lines
            if(j!=(divHor-1)){     // se nao for a ultima coluna
                edgeTable.push_back(new Edge(cylinder4[i][j], cylinder4[i][j+1]));
            }

            // Vertical lines
            if(i!=(div-1)){           // se nao for a ultima linha
                edgeTable.push_back(new Edge(cylinder4[i][j], cylinder4[i+1][j]));

            }else{                  // ultima linha é ligada com a primeira
                edgeTable.push_back(new Edge(cylinder4[i][j], cylinder4[0][j]));
            }

        }
    }

    /**************** Face 8 - Circle 5 *************/
    cyl1Init.x += 50;
    raio = 200;

    for(float i=0 ; i<2*M_PI; i+=step){

        Vector3 p0 = cyl1Init;
        p0 += (*up)*(raio*cos(i));
        p0 += (*right)*(raio*sin(i));

        Vector3 p1 = cyl1Init;
        p1 += (*up)*(raio*cos(i+step));
        p1 += (*right)*(raio*sin(i+step));

        edgeTable.push_back(new Edge(cyl1Init, p0));
        edgeTable.push_back(new Edge(cyl1Init, p1));
        edgeTable.push_back(new Edge(p0,p1));
    }

    /**************** Face 9 - Cylinder 5 *************/
    cyl1Init.y -= 100;
    length = 80;
    raio = 30;

    divHor = 10;
    stepHor = length/(float)(divHor-1);
    Vector3 cylinder5[div][divHor];

    lin = 0;
    col = 0;

    for(float i=0 ; i<2*M_PI; i+=step){

        for(float j=0; j<=length ; j+=stepHor){

            // circle
            Vector3 p0 = cyl1Init;
            p0 += (*up)*(raio*cos(i));
            p0 += (*right)*(raio*sin(i));

            // forward to cylinder
            p0 += (*forward)*j;
            //qDebug("%f", p0.x);

            cylinder5[lin][col] = p0;
            col++;
        }

        lin++;
        col = 0;
    }

    for(int i=0 ; i<div ; i++){             //linha
        for(int j=0 ; j<divHor ; j++){      //coluna

            // Horizontal lines
            if(j!=(divHor-1)){     // se nao for a ultima coluna
                edgeTable.push_back(new Edge(cylinder5[i][j], cylinder5[i][j+1]));
            }

            // Vertical lines
            if(i!=(div-1)){           // se nao for a ultima linha
                edgeTable.push_back(new Edge(cylinder5[i][j], cylinder5[i+1][j]));

            }else{                  // ultima linha é ligada com a primeira
                edgeTable.push_back(new Edge(cylinder5[i][j], cylinder5[0][j]));
            }

        }
    }

    /**************** Face 10 - Circle 5 *************/
    cyl1Init.y += 100;
    cyl1Init.x += 80;
    raio = 200;

    for(float i=0 ; i<2*M_PI; i+=step){

        Vector3 p0 = cyl1Init;
        p0 += (*up)*(raio*cos(i));
        p0 += (*right)*(raio*sin(i));

        Vector3 p1 = cyl1Init;
        p1 += (*up)*(raio*cos(i+step));
        p1 += (*right)*(raio*sin(i+step));

        edgeTable.push_back(new Edge(cyl1Init, p0));
        edgeTable.push_back(new Edge(cyl1Init, p1));
        edgeTable.push_back(new Edge(p0,p1));
    }

    /**************** Face 10 - Cylinder 6 *************/
    length = 50;
    raio = 200;

    divHor = 3;
    stepHor = length/(float)(divHor-1);
    Vector3 cylinder6[div][divHor];

    lin = 0;
    col = 0;

    for(float i=0 ; i<2*M_PI; i+=step){

        for(float j=0; j<=length ; j+=stepHor){

            // circle
            Vector3 p0 = cyl1Init;
            p0 += (*up)*(raio*cos(i));
            p0 += (*right)*(raio*sin(i));

            // forward to cylinder
            p0 += (*forward)*j;
            //qDebug("%f", p0.x);

            cylinder6[lin][col] = p0;
            col++;
        }

        lin++;
        col = 0;
    }

    for(int i=0 ; i<div ; i++){             //linha
        for(int j=0 ; j<divHor ; j++){      //coluna

            // Horizontal lines
            if(j!=(divHor-1)){     // se nao for a ultima coluna
                edgeTable.push_back(new Edge(cylinder6[i][j], cylinder6[i][j+1]));
            }

            // Vertical lines
            if(i!=(div-1)){           // se nao for a ultima linha
                edgeTable.push_back(new Edge(cylinder6[i][j], cylinder6[i+1][j]));

            }else{                  // ultima linha é ligada com a primeira
                edgeTable.push_back(new Edge(cylinder6[i][j], cylinder6[0][j]));
            }

        }
    }

    /**************** Face 10 - Circle 5 *************/
    cyl1Init.x += 50;
    raio = 200;

    for(float i=0 ; i<2*M_PI; i+=step){

        Vector3 p0 = cyl1Init;
        p0 += (*up)*(raio*cos(i));
        p0 += (*right)*(raio*sin(i));

        Vector3 p1 = cyl1Init;
        p1 += (*up)*(raio*cos(i+step));
        p1 += (*right)*(raio*sin(i+step));

        edgeTable.push_back(new Edge(cyl1Init, p0));
        edgeTable.push_back(new Edge(cyl1Init, p1));
        edgeTable.push_back(new Edge(p0,p1));
    }

    /**************** Face 10 - Cylinder 6 *************/
    length = 220;
    raio = 100;

    divHor = 10;
    stepHor = length/(float)(divHor-1);
    Vector3 cylinder7[div][divHor];

    lin = 0;
    col = 0;

    for(float i=0 ; i<2*M_PI; i+=step){

        for(float j=0; j<=length ; j+=stepHor){

            // circle
            Vector3 p0 = cyl1Init;
            p0 += (*up)*(raio*cos(i));
            p0 += (*right)*(raio*sin(i));

            // forward to cylinder
            p0 += (*forward)*j;
            //qDebug("%f", p0.x);

            cylinder7[lin][col] = p0;
            col++;
        }

        lin++;
        col = 0;
    }

    for(int i=0 ; i<div ; i++){             //linha
        for(int j=0 ; j<divHor ; j++){      //coluna

            // Horizontal lines
            if(j!=(divHor-1)){     // se nao for a ultima coluna
                edgeTable.push_back(new Edge(cylinder7[i][j], cylinder7[i][j+1]));
            }

            // Vertical lines
            if(i!=(div-1)){           // se nao for a ultima linha
                edgeTable.push_back(new Edge(cylinder7[i][j], cylinder7[i+1][j]));

            }else{                  // ultima linha é ligada com a primeira
                edgeTable.push_back(new Edge(cylinder7[i][j], cylinder7[0][j]));
            }

        }
    }

    /**************** Face 10 - Circle 5 *************/
    cyl1Init.x += 220;
    raio = 300;

    for(float i=0 ; i<2*M_PI; i+=step){

        Vector3 p0 = cyl1Init;
        p0 += (*up)*(raio*cos(i));
        p0 += (*right)*(raio*sin(i));

        Vector3 p1 = cyl1Init;
        p1 += (*up)*(raio*cos(i+step));
        p1 += (*right)*(raio*sin(i+step));

        edgeTable.push_back(new Edge(cyl1Init, p0));
        edgeTable.push_back(new Edge(cyl1Init, p1));
        edgeTable.push_back(new Edge(p0,p1));
    }

    /**************** Face 10 - Cylinder 6 *************/
    length = 50;

    divHor = 10;
    stepHor = length/(float)(divHor-1);
    Vector3 cylinder8[div][divHor];

    lin = 0;
    col = 0;

    for(float i=0 ; i<2*M_PI; i+=step){

        for(float j=0; j<=length ; j+=stepHor){

            // circle
            Vector3 p0 = cyl1Init;
            p0 += (*up)*(raio*cos(i));
            p0 += (*right)*(raio*sin(i));

            // forward to cylinder
            p0 += (*forward)*j;
            //qDebug("%f", p0.x);

            cylinder8[lin][col] = p0;
            col++;
        }

        lin++;
        col = 0;
    }

    for(int i=0 ; i<div ; i++){             //linha
        for(int j=0 ; j<divHor ; j++){      //coluna

            // Horizontal lines
            if(j!=(divHor-1)){     // se nao for a ultima coluna
                edgeTable.push_back(new Edge(cylinder8[i][j], cylinder8[i][j+1]));
            }

            // Vertical lines
            if(i!=(div-1)){           // se nao for a ultima linha
                edgeTable.push_back(new Edge(cylinder8[i][j], cylinder8[i+1][j]));

            }else{                  // ultima linha é ligada com a primeira
                edgeTable.push_back(new Edge(cylinder8[i][j], cylinder8[0][j]));
            }

        }
    }

    /**************** Face 10 - Circle 5 *************/
    cyl1Init.x += 50;

    for(float i=0 ; i<2*M_PI; i+=step){

        Vector3 p0 = cyl1Init;
        p0 += (*up)*(raio*cos(i));
        p0 += (*right)*(raio*sin(i));

        Vector3 p1 = cyl1Init;
        p1 += (*up)*(raio*cos(i+step));
        p1 += (*right)*(raio*sin(i+step));

        edgeTable.push_back(new Edge(cyl1Init, p0));
        edgeTable.push_back(new Edge(cyl1Init, p1));
        edgeTable.push_back(new Edge(p0,p1));
    }

}

void Virabrequim::render(Canvas2D *canvas, Matrix4 *renderMat, int canvasWidth, int canvasHeight){

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

void Virabrequim::update(float angle){

    // rotaciona o virabrequim em torno de x

    Matrix4 offset(1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   0, -center.y, -center.z, 1);

    Matrix4 rotacao(1, 0,           0,              0,
                    0, cos(angle),  -sin(angle),    0,
                    0, sin(angle),  cos(angle),     0,
                    0, 0,           0,              1);

    Matrix4 offsetBack(1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, 1, 0,
                       0, center.y, center.z, 1);

    list<Edge*>::iterator it;

    for (it = edgeTable.begin(); it != edgeTable.end(); ++it){
        Vector3 *p0 = new Vector3((*it)->v0->x, (*it)->v0->y, (*it)->v0->z);
        Vector3 *p1 = new Vector3((*it)->v1->x, (*it)->v1->y, (*it)->v1->z);

        *p0 = (offsetBack*(rotacao*offset))*(*p0);
        *p1 = (offsetBack*(rotacao*offset))*(*p1);

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
