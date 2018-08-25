#ifndef BIELA_H
#define BIELA_H

#include "Vector3.h"

#include "glCanvas2d.h"

#include <list>
#include "Edge.h"
#include "matrix4.h"
#include "cubo.h"

class Biela
{
public:
    Biela(Vector3 *posInit);

    void render(Canvas2D *canvas, Matrix4 *renderMat, int canvasWidth, int canvasHeight);
    void update(float distance);

    list<Edge*> edgeTable;

private:
    Vector3 pos;
    float width, height, depth;
};

#endif // BIELA_H
