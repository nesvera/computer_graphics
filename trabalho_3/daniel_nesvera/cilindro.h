#ifndef CILINDRO_H
#define CILINDRO_H

#include "Vector3.h"

#include "glCanvas2d.h"

#include <list>
#include "Edge.h"
#include "matrix4.h"

using namespace std;

class Cilindro
{
public:
    Cilindro(Vector3 *begin, Vector3 *right, Vector3 *up, Vector3 *forward, list<Edge*> *edgeTable);
};


#endif // CILINDRO_H
