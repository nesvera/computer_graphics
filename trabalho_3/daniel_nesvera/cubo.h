#ifndef CUBO_H
#define CUBO_H

#include "Vector3.h"

#include "glCanvas2d.h"

#include <list>
#include "Edge.h"

using namespace std;

class Cubo
{
public:
    Cubo(Vector3 *init, float width, float height, float depth, Vector3 *right, Vector3 *up, Vector3 *forward, list<Edge*> *edgeTable, int div){

        /************** Plano 0 ********************************/
        Vector3 p0Init = Vector3(init->x, init->y, init->z);

        float step0 = width/(float)(div-1);
        float step1 = depth/(float)(div-1);
        Vector3 plano0[div][div];

        int lin = 0;
        int col = 0;

        for(float i=0 ; i<=width; i+=step0){
            for(float j=0; j<=depth ; j+=step1){

                // square
                Vector3 p0 = p0Init;
                p0 += (*right)*(i);
                p0 += (*forward)*(j);

                plano0[lin][col] = p0;
                col++;
            }

            lin++;
            col = 0;
        }

        for(int i=0 ; i<div ; i++){             //linha
            for(int j=0 ; j<div ; j++){      //coluna

                // Horizontal lines
                if(j!=(div-1)){     // se nao for a ultima coluna
                    edgeTable->push_back(new Edge(plano0[i][j], plano0[i][j+1]));
                }

                // Vertical lines
                if(i!=(div-1)){           // se nao for a ultima linha
                    edgeTable->push_back(new Edge(plano0[i][j], plano0[i+1][j]));

                }
            }
        }


        /************** Plano 1 ********************************/
        Vector3 p1Init = Vector3(init->x, init->y, init->z);

        step0 = width/(float)(div-1);
        step1 = height/(float)(div-1);
        Vector3 plano1[div][div];

        lin = 0;
        col = 0;

        for(float i=0 ; i<=width; i+=step0){
            for(float j=0; j<=height ; j+=step1){

                // square
                Vector3 p0 = p1Init;
                p0 += (*right)*(i);
                p0 += (*up)*(j);

                //qDebug("%f %f %d %d %f %f %f", i, width, lin, col, p0.x, p0.y, p0.z);

                plano1[lin][col] = p0;
                col++;
            }

            lin++;
            col = 0;
        }
        //qDebug("");

        for(int i=0 ; i<div ; i++){             //linha
            for(int j=0 ; j<div ; j++){      //coluna

                //qDebug("%d %d %f %f %f", i, j, plano1[i][j].x, plano1[i][j].y, plano1[i][j].z);

                // Horizontal lines
                if(j!=(div-1)){     // se nao for a ultima coluna
                    edgeTable->push_back(new Edge(plano1[i][j], plano1[i][j+1]));
                }

                // Vertical lines
                if(i!=(div-1)){           // se nao for a ultima linha
                    edgeTable->push_back(new Edge(plano1[i][j], plano1[i+1][j]));

                }
            }
        }

        /************** Plano 2 ********************************/
        Vector3 p2Init = Vector3(init->x, init->y, init->z);

        step0 = depth/(float)(div-1);
        step1 = height/(float)(div-1);
        Vector3 plano2[div][div];

        lin = 0;
        col = 0;

        for(float i=0 ; i<=depth; i+=step0){
            for(float j=0; j<=height ; j+=step1){

                // square
                Vector3 p0 = p2Init;
                p0 += (*forward)*(i);
                p0 += (*up)*(j);

                plano2[lin][col] = p0;
                col++;
            }

            lin++;
            col = 0;
        }

        for(int i=0 ; i<div ; i++){             //linha
            for(int j=0 ; j<div ; j++){      //coluna

                // Horizontal lines
                if(j!=(div-1)){     // se nao for a ultima coluna
                    edgeTable->push_back(new Edge(plano2[i][j], plano2[i][j+1]));
                }

                // Vertical lines
                if(i!=(div-1)){           // se nao for a ultima linha
                    edgeTable->push_back(new Edge(plano2[i][j], plano2[i+1][j]));

                }
            }
        }

        /************** Plano 3 ********************************/
        Vector3 p3Init = Vector3(init->x+width, init->y, init->z);

        step0 = depth/(float)(div-1);
        step1 = height/(float)(div-1);
        Vector3 plano3[div][div];

        lin = 0;
        col = 0;

        for(float i=0 ; i<=depth; i+=step0){
            for(float j=0; j<=height ; j+=step1){

                // square
                Vector3 p0 = p3Init;
                p0 += (*forward)*(i);
                p0 += (*up)*(j);

                plano3[lin][col] = p0;
                col++;
            }

            lin++;
            col = 0;
        }

        for(int i=0 ; i<div ; i++){             //linha
            for(int j=0 ; j<div ; j++){      //coluna

                // Horizontal lines
                if(j!=(div-1)){     // se nao for a ultima coluna
                    edgeTable->push_back(new Edge(plano3[i][j], plano3[i][j+1]));
                }

                // Vertical lines
                if(i!=(div-1)){           // se nao for a ultima linha
                    edgeTable->push_back(new Edge(plano3[i][j], plano3[i+1][j]));

                }
            }
        }

        /************** Plano 4 ********************************/
        Vector3 p4Init = Vector3(init->x, init->y+height, init->z);

        step0 = depth/(float)(div-1);
        step1 = width/(float)(div-1);
        Vector3 plano4[div][div];

        lin = 0;
        col = 0;

        for(float i=0 ; i<=depth; i+=step0){
            for(float j=0; j<=width ; j+=step1){

                // square
                Vector3 p0 = p4Init;
                p0 += (*forward)*(i);
                p0 += (*right)*(j);

                plano4[lin][col] = p0;
                col++;
            }

            lin++;
            col = 0;
        }

        for(int i=0 ; i<div ; i++){             //linha
            for(int j=0 ; j<div ; j++){      //coluna

                // Horizontal lines
                if(j!=(div-1)){     // se nao for a ultima coluna
                    edgeTable->push_back(new Edge(plano4[i][j], plano4[i][j+1]));
                }

                // Vertical lines
                if(i!=(div-1)){           // se nao for a ultima linha
                    edgeTable->push_back(new Edge(plano4[i][j], plano4[i+1][j]));

                }
            }
        }

        /************** Plano 55 ********************************/
        Vector3 p5Init = Vector3(init->x, init->y, init->z+depth);

        step0 = width/(float)(div-1);
        step1 = height/(float)(div-1);
        Vector3 plano5[div][div];

        lin = 0;
        col = 0;

        for(float i=0 ; i<=width; i+=step0){
            for(float j=0; j<=height ; j+=step1){

                // square
                Vector3 p0 = p5Init;
                p0 += (*right)*(i);
                p0 += (*up)*(j);

                //qDebug("%f %f %d %d %f %f %f", i, width, lin, col, p0.x, p0.y, p0.z);

                plano5[lin][col] = p0;
                col++;
            }

            lin++;
            col = 0;
        }

        for(int i=0 ; i<div ; i++){             //linha
            for(int j=0 ; j<div ; j++){      //coluna

                // Horizontal lines
                if(j!=(div-1)){     // se nao for a ultima coluna
                    edgeTable->push_back(new Edge(plano5[i][j], plano5[i][j+1]));
                }

                // Vertical lines
                if(i!=(div-1)){           // se nao for a ultima linha
                    edgeTable->push_back(new Edge(plano5[i][j], plano5[i+1][j]));

                }
            }
        }
    }
};

#endif // CUBO_H
