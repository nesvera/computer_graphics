#ifndef CAMISA_H
#define CAMISA_H

#include "Vector3.h"

#include "glCanvas2d.h"

#include <list>
#include "Edge.h"
#include "matrix4.h"

using namespace std;

class Camisa
{
public:
    Camisa(Vector3 *posInit, Vector3 *right, Vector3 *up, Vector3 *forward);

    void render(Canvas2D *canvas, Matrix4 *renderMat, int canvasWidth, int canvasHeight);

    list<Edge*> edgeTable;
};

#endif // CAMISA_H
