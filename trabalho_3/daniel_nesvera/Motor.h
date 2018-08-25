#ifndef MOTOR_H
#define MOTOR_H

#include "glCanvas2d.h"

#include "Vector3.h"
#include "matrix4.h"

#include "Virabrequim.h"
#include "Camisa.h"
#include "bloco.h"
#include "biela.h"
#include "pistao.h"


class Motor
{
public:
    Motor(int x, int y, int z);
    void update(float deltaT, float rps);
    void render(Canvas2D *canvas, Matrix4 *renderMat, int canvasWidth, int canvasHeight);

    void setVirabrequimActive(bool enable);
    void setBlocoActive(bool enable);
    void setCamisaActive(bool enable);
    void setPistaoActive(bool enable);
    void setBielaActive(bool enable);
    void setRpm(float value);

private:
    bool virabrequimActive;
    bool blocoActive;
    bool camisaActive;
    bool pistaoActive;
    bool bielaActive;
    float rps;

    Vector3 position;
    Vector3 rotation;

    Virabrequim *virabrequim;
    Camisa *camisa0;
    Camisa *camisa1;
    Bloco *bloco;
    Biela *biela0;
    Biela *biela1;
    Pistao *pistao0;
    Pistao *pistao1;

    // lista de faces
    // lista de vertices
    // lista de pontos

};

#endif // MOTOR_H
