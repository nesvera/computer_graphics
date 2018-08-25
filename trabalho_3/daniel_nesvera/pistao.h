#ifndef PISTAO_H
#define PISTAO_H

#include "Vector3.h"

#include "glCanvas2d.h"

#include <list>
#include "Edge.h"
#include "matrix4.h"

using namespace std;

class Pistao
{
public:
    Pistao(Vector3 *posInit, Vector3 *right, Vector3 *up, Vector3 *forward);

    void render(Canvas2D *canvas, Matrix4 *renderMat, int canvasWidth, int canvasHeight);
    void update(float distance);

    list<Edge*> edgeTable;
};

#endif // PISTAO_H
