/**
 * @file    motor.cpp
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Classe motor, instancia os componentes
 *
 */

#include "Motor.h"

Motor::Motor(int x, int y, int z){
    position.x = x;
    position.y = y;
    position.z = z;

    bloco = new Bloco(new Vector3(x,y,z));

    virabrequim = new Virabrequim(new Vector3(x,(y+250),(z+250)),
                                  new Vector3(0,0,1),
                                  new Vector3(0,1,0),
                                  new Vector3(1,0,0));

    camisa0 = new Camisa(new Vector3((x+230+60),(y+500),(z+250)),
                         new Vector3(1,0,0),
                         new Vector3(0,1,0),
                         new Vector3(0,0,1));

    camisa1 = new Camisa(new Vector3((x+360+60),(y+500),(z+250)),
                         new Vector3(1,0,0),
                         new Vector3(0,1,0),
                         new Vector3(0,0,1));



    biela0 = new Biela(new Vector3((x+250),(y+250),(z+210)));
    biela1 = new Biela(new Vector3((x+380),(y+50),(z+210)));


    pistao0 = new Pistao(new Vector3((x+230+60),(y+700),(z+250)),
                         new Vector3(1,0,0),
                         new Vector3(0,1,0),
                         new Vector3(0,0,1));

    pistao1 = new Pistao(new Vector3((x+360+60),(y+500),(z+250)),
                         new Vector3(1,0,0),
                         new Vector3(0,1,0),
                         new Vector3(0,0,1));

    virabrequimActive = false;
    blocoActive = false;
    camisaActive = false;
    pistaoActive = false;
    bielaActive = false;

}

float initAngle = 0;
void Motor::update(float deltaT, float rps){
    float virabrequimAngle = rps*(2*M_PI)*deltaT;

    virabrequim->update(virabrequimAngle);

    initAngle += virabrequimAngle;

    float deslocamento = 2*std::sin(initAngle);

    pistao0->update(-deslocamento);
    pistao1->update(+deslocamento);

}

void Motor::render(Canvas2D *canvas, Matrix4 *renderMat, int canvasWidth, int canvasHeight){

    if(virabrequimActive){
        virabrequim->render(canvas, renderMat, canvasWidth, canvasHeight);
    }

    if(blocoActive){
        bloco->render(canvas, renderMat, canvasWidth, canvasHeight);
    }

    if(camisaActive){
        camisa0->render(canvas, renderMat, canvasWidth, canvasHeight);
        camisa1->render(canvas, renderMat, canvasWidth, canvasHeight);
    }

    if(pistaoActive){
        pistao0->render(canvas, renderMat, canvasWidth, canvasHeight);
        pistao1->render(canvas, renderMat, canvasWidth, canvasHeight);
    }

    if(bielaActive){
        biela0->render(canvas, renderMat, canvasWidth, canvasHeight);
        biela1->render(canvas, renderMat, canvasWidth, canvasHeight);
    }
}

void Motor::setVirabrequimActive(bool enable){
    virabrequimActive = enable;
}

void Motor::setBlocoActive(bool enable){
    blocoActive = enable;
}

void Motor::setCamisaActive(bool enable){
    camisaActive = enable;
}

void Motor::setPistaoActive(bool enable){
    pistaoActive = enable;
}

void Motor::setBielaActive(bool enable){
    bielaActive = enable;
}

void Motor::setRpm(float value){
    rps = value;
}
