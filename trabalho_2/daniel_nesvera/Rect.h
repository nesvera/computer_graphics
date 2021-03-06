#ifndef RECT_H
#define RECT_H

#include <list>
#include <QOpenGLFunctions_1_1>
#include "DrawComponent.h"
#include "glCanvas2d.h"
#include "controlpoint.h"
#include "Point.h"

using namespace std;

class Rect : public DrawComponent{

public:
    Rect(float _x0, float _y0, int width, int height, int type);

    void render(Canvas2D *canvas, int w, int h);
    void mouseMoveHandler(int x, int y, int w, int h);
    bool mouseSelectClickHandler(int x, int y, int w, int h);
    int  getMemSize();
    void saveComponent(FILE *f);
    void setControlPoint(int x, int y, int w, int h, int n);

private:
    float x0, y0, x1, y1;
    Point *P0, *P1, *P2, *P3;

    list<ControlPoint*> controlPoints;

};

#endif // RECT_H
