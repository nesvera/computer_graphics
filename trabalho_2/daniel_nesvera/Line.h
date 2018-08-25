#ifndef LINE_H
#define LINE_H

#include <list>
#include <QOpenGLFunctions_1_1>
#include "DrawComponent.h"
#include "glCanvas2d.h"
#include "controlpoint.h"
#include "Point.h"

using namespace std;

class Line : public DrawComponent{

public:
    Line(float _x0, float _y0, int width, int height, int type);


    void render(Canvas2D *canvas, int w, int h);
    void mouseMoveHandler(int x, int y, int w, int h);
    bool mouseSelectClickHandler(int x, int y, int w, int h);
    int  getMemSize();
    void saveComponent(FILE *f);
    void setControlPoint(int x, int y, int w, int h, int n);

private:
    float x0, y0, x1, y1;

    list<ControlPoint*> controlPoints;
};

#endif // LINE_H
