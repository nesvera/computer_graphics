#ifndef BLOCO_H
#define BLOCO_H

#include "Vector3.h"
#include "Cilindro.h"
#include "Cubo.h"

using namespace std;

class Bloco
{
public:
    Bloco(Vector3 *posInit);
    void Render();

private:
     Vector3 *posInit;

     Cubo *cubo;

};

#endif // BLOCO_H
