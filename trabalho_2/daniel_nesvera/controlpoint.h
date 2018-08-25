#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H

#include "DrawComponent.h"
#include "glCanvas2d.h"

class ControlPoint : public DrawComponent{

public:
    ControlPoint(float x0, float y0, int w, int h);

    void render(Canvas2D *_canvas, int w, int h);
    void mouseMoveHandler(int x, int y, int w, int h);
    void setPosition(int x, int y, int w, int h);
    float getX();
    float getY();
    bool mouseSelectClickHandler(int x, int y, int w, int h);
    int getMemSize();
    void saveComponent(FILE *f);

private:
    float x0, y0;
    float height = 10;
    float width = 10;

    Canvas2D *canvas;

};

#endif // CONTROLPOINT_H
