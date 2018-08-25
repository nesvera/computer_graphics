#ifndef VIRABREQUIM_H
#define VIRABREQUIM_H

#include "glCanvas2d.h"

#include <list>
#include "matrix4.h"
#include "Edge.h"

using namespace std;

class Virabrequim
{
public:
    Virabrequim(Vector3 *posInit, Vector3 *right, Vector3 *up, Vector3 *forward);
    void render(Canvas2D *canvas, Matrix4 *renderMat, int canvasWidth, int canvasHeight);
    void update(float angle);

    list<Edge*> edgeTable;

    Vector3 center;
};

#endif // VIRABREQUIM_H
