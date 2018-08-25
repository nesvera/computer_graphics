#include <list>

#include "glCanvas2d.h"
#include "mainwindow.h"

#include <math.h>
#include <QMessageBox>
#include <QInputDialog>
#include <QWheelEvent>
#include <qdebug.h>
#include <QFileDialog>
#include <QCoreApplication>
#include <string>
#include <QTime>

#include <stdio.h>
#include <math.h>

#include "Vector3.h"
#include "Matrix4.h"
#include "Pipeline.h"
#include "Motor.h"


int i=0;
using namespace std;

Vector3 p[8];
float l = 100;
float eyeX = 0;
float eyeZ = 0;
float aux = 0;

Pipeline *pipeline;
Motor *motor;
Vector3 *eye;

bool firstExe = true;

float distancia = 0;
float velocidade = 0;

QTime t;
float lastTime;

// camera interaction
bool bRight = false;
bool bLeft = false;
bool bUp = false;
bool bDown = false;
bool zoom = false;
int zoomValue;
int dtZoom = 0;
float camZAngle = M_PI/2;
bool dMouse = false;
Vector3 dtMouse;
Vector3 lastPosMouse;



// *******************************************************************************
//Coloque seu codigo aqui, usando as funcoes da Canvas2D defindas na classe Canvas2D (arquivo glCanvas2d.h).
// *******************************************************************************
void Canvas2D::paintGL() //callback de desenho na canvas. Chamado pelo Timer definido em mainWindow.cpp
{
    clear(1.0, 1.0, 1.0);
    canvasHeight = this->geometry().height();
    canvasWidth = this->geometry().width();

    if(firstExe){
        t.start();
        lastTime = t.elapsed();

        float fov = 60.0f;
        float znear = 0.1f;
        float zfar = 1000.0f;


        pipeline = new Pipeline(fov, znear, zfar);
        motor = new Motor(0.1, 0.1, 0.1);
        eye = new Vector3(0, l/2, 0);
        zoomValue = 700;

        firstExe = false;

        return;
    }

    // update periodo de atualizacao (frame rate independent)
    deltaT = (t.elapsed() - lastTime)/1000.0;
    lastTime = t.elapsed();

    // Atualizacao posicao dos componentes do motor - passa velocidadeAngular(rps)
    motor->update(deltaT, velocidade);

    /* Processo de visualização */

    /*
     *  --> Chain of coordinate transformations
     * Viewport * Projection * View * Model * v.
    */

    // --> v is the model created in their own local frame(object coordinate)

    // --> Model is a tranformation of the model to the world coordinates (resize, rotate, translate to the desired positon)
    // Aqui faremos as alterações sobre o modelo(rotaçao,translação)

    color(0,0,0);

    // posiciona o "centro" do motor em (0,0,0)
    Matrix4 model = Matrix4(1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            -365, -370, -250, 1);

    // --> View
    // --> Projection

    // camera interaction control
    if(bRight){

        bRight = false;

    }else if(bLeft){
        bLeft = false;

    }else if(bUp){

        bUp = false;

    }else if(bDown){

        bDown = false;

    }else if(zoom){

        // zoom usando a roda do mouse
        zoomValue += 5*dtZoom;
        dtZoom = 0;
        zoom = false;

    }else if(dMouse){

        // Sensibilidade do mouse = precisa arrastar 1*width pra girar 180 graus
        camZAngle += dtMouse.x*(M_PI/canvasWidth);
        dMouse = false;

    }

    eyeX = zoomValue*std::cos(camZAngle);
    eyeZ = zoomValue*std::sin(camZAngle);

    Matrix4 view = pipeline->lookAt(Vector3(eyeX,l/2,eyeZ), Vector3(l/2+0.1,l/2+0.1,l/2+0.1), Vector3(0,1,0));
    Matrix4 projection = pipeline->getProjection();
    Matrix4 renderMat = projection*(view*model);

    // renderiza o motor
    motor->render(this, &renderMat, canvasWidth, canvasHeight);

}

//**********************************************************
// Funcoes para tratar cada funcao ao clicar sobre o canvas
//**********************************************************

void Canvas2D::mousePressEvent(QMouseEvent *event) //callback de mouse
{
    //qDebug("\nMouse press: %d %d", event->x(), (canvasHeight-event->y()));
    lastPosMouse.x = event->x();
    lastPosMouse.y = (canvasHeight-event->y());
}

void Canvas2D::mouseMoveEvent(QMouseEvent * event) //callback de mouse
{
    //qDebug("\nMouse Move: %d %d", event->x(), (canvasHeight-event->y()));
}

void Canvas2D::mouseReleaseEvent(QMouseEvent *event) //callback de mouse
{
    //qDebug("\nMouse Release: %d %d", event->x(), (canvasHeight-event->y()));
    dMouse = true;
    dtMouse.x = event->x() - lastPosMouse.x;
    dtMouse.y = (canvasHeight-event->y()) - lastPosMouse.y;

}

void Canvas2D::keyPressEvent(QKeyEvent* event)
{
    qDebug("\nTecla pessionada  %d", event->key() );

    // esquerda(16777234) ou a(65)
    if(event->key() == 16777234 || event->key() == 65 ){
        bLeft = true;

    // direita(16777236) ou d(68)
    }else if(event->key() == 16777236 || event->key() == 68 ){
        bRight = true;

    // baixo(16777237) ou s(83)
    }else if(event->key() == 16777237 || event->key() == 83 ){
        bUp = true;

    // cima(16777235) ou w(87)
    }else if(event->key() == 16777235 || event->key() == 87 ){
        bDown = true;

    }

}
void Canvas2D::wheelEvent(QWheelEvent *event) //callback de mouse
{
    //printf("\nMouse Wheel event: %d", event->delta() );
    //qDebug("Mouse Wheel event %d", event->delta() );

    if(event->delta()>0){
        dtZoom -= 1;
    }else{
        dtZoom += 1;
    }

    zoom = true;
}

//callback para botao definido na mainWindow.
void Canvas2D::showMsg()
{
    QMessageBox* msg = new QMessageBox(this);
    msg->setText("testando som");
    msg->show();
}

// Save the canvas windows size
void Canvas2D::setWindowSize(int w, int h){
    canvasHeight = this->geometry().height();
    canvasWidth = this->geometry().width();

    //qDebug("alterou --> %d - %d", height, width);
}

void Canvas2D::virabrequimCheckBoxChanged(bool enabled){
    motor->setVirabrequimActive(enabled);
}

void Canvas2D::blocoCheckBoxChanged(bool enabled){
    motor->setBlocoActive(enabled);
}

void Canvas2D::camisaCheckBoxChanged(bool enabled){
    motor->setCamisaActive(enabled);
}

void Canvas2D::pistaoCheckBoxChanged(bool enabled){
    motor->setPistaoActive(enabled);
}

void Canvas2D::bielaCheckBoxChanged(bool enabled){
    motor->setBielaActive(enabled);
}

void Canvas2D::rpmSpinBoxChanged(double value){
    velocidade = value;
}
