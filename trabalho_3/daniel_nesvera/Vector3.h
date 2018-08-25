#ifndef VECTOR3_H
#define VECTOR3_H

#include <QDebug>

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
        float length = std::sqrt(std::pow(x,2)+std::pow(y,2)+std::pow(z,2));
        aux.x = x/length;
        aux.y = y/length;
        aux.z = z/length;

        return aux;
    }

    void print(){
        qDebug("(%f %f %f)", x, y, z );
    }

};

#endif // VECTOR3_H
