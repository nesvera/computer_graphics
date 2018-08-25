#ifndef CUBO_H_INCLUDED
#define CUBO_H_INCLUDED

#include "Vector3.h"
#include "Cilindro.h"

using namespace std;

class Cubo
{
public:
    Cubo(Vector3 *posInit, float w, float l, float h );

    void Render();
    void SetPosition(Vector3 *pInit);

private:
     Vector3 *posInit;

     Cilindro *cilindro_0;

     float width;
     float height;
     float length;

     int resolucao;

};

#endif // CUBO_H_INCLUDED
