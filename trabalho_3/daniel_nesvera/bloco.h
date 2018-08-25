#ifndef BLOCO_H
#define BLOCO_H

#include "Vector3.h"

#include "glCanvas2d.h"

#include <list>
#include "Edge.h"
#include "matrix4.h"
#include "cubo.h"

using namespace std;

class Bloco
{
public:
    Bloco(Vector3 *posInit);
    void render(Canvas2D *canvas, Matrix4 *renderMat, int canvasWidth, int canvasHeight);

    list<Edge*> edgeTable;
};

#endif // BLOCO_H
