/**
 * @file    Vector3.h
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Classe implenta vetores e operacoes 3D
 *
 */

#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>
#include <stdio.h>

class Vector3
{

public:
    float x, y, z;

    Vector3(){
        x = 0;
        y = 0;
        z = 0;
    }

    Vector3(float vx, float vy, float vz){
        x = vx;
        y = vy;
        z = vz;
    }

    Vector3(const Vector3 &v){
        x = v.x;
        y = v.y;
        z = v.z;
    }

    void operator += (const Vector3 &v){
        x += v.x;
        y += v.y;
        z += v.z;
    }

    void operator -= (const Vector3 &v){
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }

    // Produto vetorial
    Vector3 operator ^ (Vector3 &v){
        Vector3 aux((y*v.z - z*v.y), (z*v.x - x*v.z), (x*v.y - y*v.x));
        return aux;
    }

    // Produto interno
    float operator * (Vector3 &v){
        float aux = (x*v.x + y*v.y + z*v.z);
        return aux;
    }

    Vector3 operator * (float a){
        Vector3 aux(a*x, a*y, a*z);
        return aux;
    }

    Vector3 operator * (double a){
        Vector3 aux(a*x, a*y, a*z);
        return aux;
    }

    Vector3 operator + (Vector3 &v){
        Vector3 aux((x+v.x), (y+v.y), (z+v.z));
        return aux;
    }

    Vector3 operator - (Vector3 &v){
        Vector3 aux((x-v.x), (y-v.y), (z-v.z));
        return aux;
    }

    Vector3 normalize(){
        Vector3 aux = Vector3();
        float length = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
        aux.x = x/length;
        aux.y = y/length;
        aux.z = z/length;

        return aux;
    }

    void print(){
        printf("(%f %f %f)\n", x, y, z );
    }

};

#endif // VECTOR3_H
