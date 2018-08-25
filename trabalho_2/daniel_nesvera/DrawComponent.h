#ifndef DRAWCOMPONENT_H
#define DRAWCOMPONENT_H

#include "glCanvas2d.h"
#include <stdio.h>

class Canvas2D;

class DrawComponent{

public:
    DrawComponent();

    virtual void render(Canvas2D *canvas, int w, int h);
    virtual void mouseMoveHandler(int x, int y, int w, int h);
    virtual void mouseHandler();
    void disableFocus();
    bool isInFocus();
    virtual bool mouseSelectClickHandler(int x, int y, int w, int h);
    virtual int getMemSize();
    virtual void saveComponent(FILE *f);
    virtual void setControlPoint(int x, int y, int w, int h, int n);
    int getType();
    virtual void addControlPoint(int x, int y, int w, int h);

protected:
    bool isSelected;
    int componentType;
    int qntControlPoints;

};

#endif // DRAWCOMPONENT_H
