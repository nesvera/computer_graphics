/**
 * @file    Vector3.h
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Classe implenta matrizes e operacoes 3x3
 *    Utilizado para matrizes homogeneas
 *
 */

#ifndef MATRIX3_H_INCLUDED
#define MATRIX3_H_INCLUDED

class Matrix3
{

public:
    float mat[3][3];

    Matrix3(){
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                mat[i][j] = 0;
            }
        }
    }

    Matrix3(float v00, float v01, float v02,
            float v10, float v11, float v12,
            float v20, float v21, float v22){

        mat[0][0] = v00;
        mat[0][1] = v01;
        mat[0][2] = v02;
        mat[1][0] = v10;
        mat[1][1] = v11;
        mat[1][2] = v12;
        mat[2][0] = v20;
        mat[2][1] = v21;
        mat[2][2] = v22;

    }

    Matrix3(float m[3][3]){
        for(int i=0; i<3 ; i++ ){
            for(int j=0; j<3 ; j++ ){
                mat[i][j] = m[i][j];
            }
        }
    }

    Matrix3(const Matrix3 &m){
        for(int i=0; i<3 ; i++ ){
            for(int j=0; j<3 ; j++ ){
                mat[i][j] = m.mat[i][j];
            }
        }
    }

    Matrix3 operator += (const Matrix3 &m){
    }

    Matrix3 operator -= (const Matrix3 &m){
    }

    Matrix3 operator * (const Matrix3 &m){
        Matrix3 aux = Matrix3();
        for(int i=0; i<3; i++ ){
            for(int j=0; j<3; j++ ){
                for(int k=0; k<3 ; k++){
                    aux.mat[i][j] += mat[i][k]*m.mat[k][j];
                }
            }
        }

        return aux;
    }


    Vector3 operator * (const Vector3 &v){
        // gambiarra
        Matrix3 inVector;
        inVector.mat[0][0] = v.x;
        inVector.mat[1][0] = v.y;
        inVector.mat[2][0] = v.z;

        Matrix3 aux = Matrix3();
        Vector3 outVector;

        for(int i=0; i<3; i++ ){
            for(int j=0; j<3; j++){
                aux.mat[i][0] += mat[i][j]*inVector.mat[j][0];
            }
        }

        outVector.x = aux.mat[0][0];
        outVector.y = aux.mat[1][0];
        outVector.z = aux.mat[2][0];

        return outVector;
    }


    Matrix3 operator + (Vector3 &v){
    }

    Matrix3 operator - (Vector3 &v){
    }

    void print(){
        for(int i=0; i<3 ; i++ ){
            printf("| %.1f %.1f %.1f |", mat[i][0], mat[i][1], mat[i][2]);
        }
    }

};

#endif // MATRIX3_H_INCLUDED
