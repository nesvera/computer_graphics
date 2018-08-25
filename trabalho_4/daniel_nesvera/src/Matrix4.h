/**
 * @file    Vector4.h
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Classe implenta matrizes e operacoes 4x4
 *    Utilizado para matrizes homogeneas
 *
 */

#ifndef MATRIX4_H
#define MATRIX4_H

#include "Vector3.h"
#include <math.h>
#include <stdio.h>

class Matrix4
{

public:
    float mat[4][4];

    Matrix4(){
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                mat[i][j] = 0;
            }
        }
    }

    Matrix4(float v00, float v01, float v02, float v03,
            float v10, float v11, float v12, float v13,
            float v20, float v21, float v22, float v23,
            float v30, float v31, float v32, float v33){

        mat[0][0] = v00;
        mat[0][1] = v01;
        mat[0][2] = v02;
        mat[0][3] = v03;
        mat[1][0] = v10;
        mat[1][1] = v11;
        mat[1][2] = v12;
        mat[1][3] = v13;
        mat[2][0] = v20;
        mat[2][1] = v21;
        mat[2][2] = v22;
        mat[2][3] = v23;
        mat[3][0] = v30;
        mat[3][1] = v31;
        mat[3][2] = v32;
        mat[3][3] = v33;

    }

    Matrix4(float m[4][4]){
        for(int i=0; i<4 ; i++ ){
            for(int j=0; j<4 ; j++ ){
                mat[i][j] = m[i][j];
            }
        }
    }

    Matrix4(const Matrix4 &m){
        for(int i=0; i<4 ; i++ ){
            for(int j=0; j<4 ; j++ ){
                mat[i][j] = m.mat[i][j];
            }
        }
    }

    Matrix4 operator += (const Matrix4 &m){
    }

    Matrix4 operator -= (const Matrix4 &m){
    }

    Matrix4 operator * (const Matrix4 &m){
        Matrix4 aux = Matrix4();
        for(int i=0; i<4; i++ ){
            for(int j=0; j<4; j++ ){
                for(int k=0; k<4 ; k++){
                    aux.mat[i][j] += mat[i][k]*m.mat[k][j];
                }
            }
        }

        return aux;
    }


    Vector3 operator * (const Vector3 &v){
        // gambiarra
        Matrix4 inVector;
        inVector.mat[0][0] = v.x;
        inVector.mat[1][0] = v.y;
        inVector.mat[2][0] = v.z;
        inVector.mat[3][0] = 1;

        Matrix4 aux = Matrix4();
        Vector3 outVector;

        for(int i=0; i<4; i++ ){
            for(int j=0; j<4; j++){
                aux.mat[i][0] += mat[i][j]*inVector.mat[j][0];
            }
        }

        outVector.x = aux.mat[0][0]/aux.mat[3][0];
        outVector.y = aux.mat[1][0]/aux.mat[3][0];
        outVector.z = aux.mat[2][0]/aux.mat[3][0];

        return outVector;
    }


    Matrix4 operator + (Vector3 &v){
    }

    Matrix4 operator - (Vector3 &v){
    }

    void print(){
        for(int i=0; i<4 ; i++ ){
            printf("| %.1f %.1f %.1f %.1f |", mat[i][0], mat[i][1], mat[i][2], mat[i][3]);
        }
    }

};

#endif // MATRIX4_H
