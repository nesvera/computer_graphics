#ifndef CIRCULO_H
#define CIRCULO_H

#include "Vector3.h"

#include "glCanvas2d.h"

#include <list>
#include "Edge.h"

using namespace std;

class Circulo
{
public:
    Circulo(Vector3 center, Vector3 *right, Vector3 *up, Vector3 *forward, list<Edge*> *edgeTable);
};


#endif // CIRCULO_H
