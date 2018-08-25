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

#include <stdio.h>

#include "DrawComponent.h"
#include "Line.h"

#include "Point.h"
#include "ControlPoint.h"
#include "Rect.h"
#include "Point.h"
#include "Circ.h"
#include "Belzier.h"

using namespace std;

// Funcoes referentes aos botoes que o usuario pode usar
enum DrawFunctions{
    selecionar = 0,
    linha,
    retangulo,
    maoLivre,
    triangulo,
    circulo,
    poligono
};

// Sobre variaveis globais https://devrant.com/search?term=%23variables
list<DrawComponent*> drawComponentList;
DrawFunctions currentFunction = DrawFunctions::selecionar;

// *******************************************************************************
//Coloque seu codigo aqui, usando as funcoes da Canvas2D defindas na classe Canvas2D (arquivo glCanvas2d.h).
// *******************************************************************************
void Canvas2D::paintGL() //callback de desenho na canvas. Chamado pelo Timer definido em mainWindow.cpp
{
    height = this->geometry().height();
    width = this->geometry().width();

    clear(1.0, 1.0, 1.0);

    list<DrawComponent*>::iterator it;
    for (it = drawComponentList.begin(); it != drawComponentList.end(); ++it){
        (*it)->render(this, width, height);
    }

}

//**********************************************************
// Funcoes para tratar cada funcao ao clicar sobre o canvas
//**********************************************************

void Canvas2D::mousePressEvent(QMouseEvent *event) //callback de mouse
{
    //seta o foco para a canvas2D, desse modo pode-se pegar eventos de teclado dentro da canvas.
    setFocus();

    height = this->geometry().height();
    width = this->geometry().width();

    list<DrawComponent*>::iterator it;
    for (it = drawComponentList.begin(); it != drawComponentList.end(); ++it){
        (*it)->disableFocus();
    }

    switch(currentFunction){
        case DrawFunctions::selecionar:
            for (it = drawComponentList.begin(); it != drawComponentList.end(); ++it){
                bool somethingSelected = (*it)->mouseSelectClickHandler(event->x(), (height-event->y()), width, height);
                if(somethingSelected){
                    break;
                }
            }
            break;

        case DrawFunctions::linha:
            drawComponentList.push_back(new Line(event->x(), (height-event->y()), width, height, currentFunction));
            break;

        case DrawFunctions::retangulo:
            drawComponentList.push_back(new Rect(event->x(), (height-event->y()), width, height, currentFunction));
            break;

        case DrawFunctions::maoLivre:
            DrawComponent *lastComponent;
            lastComponent = drawComponentList.back();

            int compType;
            compType = (*lastComponent).getType();

            if(compType != DrawFunctions::maoLivre){
                //drawComponentList.push_back(new Belzier(event->x(), (height-event->y()), width, height, currentFunction));
            }else{
                //lastComponent->addControlPoint(event->x(), (height-event->y()), width, height);
            }


            break;

        case DrawFunctions::triangulo:
            break;

        case DrawFunctions::circulo:
            drawComponentList.push_back(new Circ(event->x(), (height-event->y()), width, height, currentFunction));
            break;

        case DrawFunctions::poligono:
            break;

        default:
            break;
    }
}

void Canvas2D::mouseMoveEvent(QMouseEvent * event) //callback de mouse
{
    //qDebug("\nMouse Move: %d %d", event->x(), (height-event->y()));
    height = this->geometry().height();
    width = this->geometry().width();

    list<DrawComponent*>::iterator it;
    for (it = drawComponentList.begin(); it != drawComponentList.end(); ++it){
        (*it)->mouseMoveHandler(event->x(), (height-event->y()), width, height);
    }
}

void Canvas2D::keyPressEvent(QKeyEvent* event)
{
    //qDebug("\nTecla pessionada  %d", event->key() );

    if(event->key() == 16777223){
        DrawComponent *toRemove;
        bool somethingInFocus;

        list<DrawComponent*>::iterator it;
        for (it = drawComponentList.begin(); it != drawComponentList.end(); ++it){
            somethingInFocus = (*it)->isInFocus();

            if(somethingInFocus){
                toRemove = *it;
                break;
            }
        }

        drawComponentList.remove(toRemove);
    }
}


// salvar arquivo seguindo
// 0 - numero de bytes
// --> primeira forma
// 1 - tipo de componente
// 2 - quantidade de pontos de controle
// 3 - ponto de controle 0 - x
// 4 - ponto de controle 0 - y
// 5 - ponto de controle 1 - x
// 6 - ponto de controle 1 - y
// --> segunda forma
// 7 - tipo de componente
// ....
void Canvas2D::saveFile(std::string fileName){
    int sizeSum = 0;

    list<DrawComponent*>::iterator it;
    for (it = drawComponentList.begin(); it != drawComponentList.end(); ++it){
        sizeSum += (*it)->getMemSize();
    }

    // Open the file
    const char *fileNameChar = fileName.c_str();
    FILE *f = fopen(fileNameChar, "w");

    // Save the numero of bytes to be read
    fwrite(&sizeSum, sizeof(sizeSum), 1, f);

    for (it = drawComponentList.begin(); it != drawComponentList.end(); ++it){
        (*it)->saveComponent(f);
    }

    fclose(f);
}

// salvar arquivo seguindo
// 0 - numero de bytes
// --> primeira forma
// 1 - tipo de componente
// 2 - quantidade de pontos de controle
// 3 - ponto de controle 0 - x
// 4 - ponto de controle 0 - y
// 5 - ponto de controle 1 - x
// 6 - ponto de controle 1 - y
// --> segunda forma
// 7 - tipo de componente
// ....
void Canvas2D::loadFile(std::string fileName){
    drawComponentList.clear();

    height = this->geometry().height();
    width = this->geometry().width();

    int sizeSum = 0;

    // Open the file
    const char *fileNameChar = fileName.c_str();
    FILE *f = fopen(fileNameChar, "r");

    fread(&sizeSum, sizeof(sizeSum), 1, f);

    while(sizeSum>0){

        int component;
        fread(&component, sizeof(component), 1, f);
        sizeSum -= sizeof(component);

        int qntControlPoints;
        fread(&qntControlPoints, sizeof(qntControlPoints), 1, f);
        sizeSum -= sizeof(qntControlPoints);
        float x, y;
        float x0, y0, x1, y1;
        switch(component){
            case DrawFunctions::linha:
                fread(&x, sizeof(x), 1, f);
                sizeSum -= sizeof(x);
                fread(&y, sizeof(y), 1, f);
                sizeSum -= sizeof(y);

                Line *newLine;
                newLine = new Line(x*width, y*height, width, height, component);

                fread(&x, sizeof(x), 1, f);
                sizeSum -= sizeof(x);
                fread(&y, sizeof(y), 1, f);
                sizeSum -= sizeof(y);

                newLine->setControlPoint((x*width), (y*height), width, height, 1);

                drawComponentList.push_back(newLine);

                break;

            case DrawFunctions::retangulo:
                fread(&x, sizeof(x), 1, f);
                sizeSum -= sizeof(x);
                fread(&y, sizeof(y), 1, f);
                sizeSum -= sizeof(y);

                Rect *newRect;
                newRect = new Rect(x*width, y*height, width, height, component);

                fread(&x, sizeof(x), 1, f);
                sizeSum -= sizeof(x);
                fread(&y, sizeof(y), 1, f);
                sizeSum -= sizeof(y);

                newRect->setControlPoint((x*width), (y*height), width, height, 1);

                drawComponentList.push_back(newRect);
                break;

            case DrawFunctions::maoLivre:
                break;

            case DrawFunctions::triangulo:
                break;

            case DrawFunctions::circulo:
                fread(&x0, sizeof(x0), 1, f);
                sizeSum -= sizeof(x0);
                fread(&y0, sizeof(y0), 1, f);
                sizeSum -= sizeof(y0);

                fread(&x1, sizeof(x1), 1, f);
                sizeSum -= sizeof(x1);
                fread(&y1, sizeof(y1), 1, f);
                sizeSum -= sizeof(y1);

                Circ *newCirc;
                newCirc = new Circ(x1*width, y1*height, width, height, component);
                newCirc->setControlPoint((x0*width), (y0*height), width, height, 1);

                drawComponentList.push_back(newCirc);
                break;

            case DrawFunctions::poligono:
                break;

            default:
                break;
        }
    }

    fclose(f);

    list<DrawComponent*>::iterator it;
    for (it = drawComponentList.begin(); it != drawComponentList.end(); ++it){
        (*it)->disableFocus();
    }
}

// **********************************************************
// Handlers dos botoes da interface
// **********************************************************
void Canvas2D::btnSelectHandler(){
    currentFunction = DrawFunctions::selecionar;
}

void Canvas2D::btnLineHandler(){
    currentFunction = DrawFunctions::linha;
}

void Canvas2D::btnRectHandler(){
    currentFunction = DrawFunctions::retangulo;
}

void Canvas2D::btnFreeHandHandler(){
    currentFunction = DrawFunctions::maoLivre;
}

void Canvas2D::btnTriangleHandler(){
    currentFunction = DrawFunctions::triangulo;
}

void Canvas2D::btnCircleHandler(){
    currentFunction = DrawFunctions::circulo;
}

void Canvas2D::btnPolygonHandler(){
    currentFunction = DrawFunctions::poligono;
}

void Canvas2D::btnContornoHandler(){
    QMessageBox* msg = new QMessageBox(this);
    msg->setText("Em obras");
    msg->show();
}

void Canvas2D::btnPreenchimentoHandler(){
    QMessageBox* msg = new QMessageBox(this);
    msg->setText("Em obras");
    msg->show();
}

void Canvas2D::btnNewHandler(){
    drawComponentList.clear();
}

void Canvas2D::btnOpenHandler(){
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Load File"), "/",
            tr("Canvas (*.dat)"));

    if (fileName.isEmpty()){
        return;
    }else{

        std::string file = fileName.toUtf8().constData();
        Canvas2D::loadFile(file);
     }
}

void Canvas2D::btnSaveHandler(){
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save File"), "/",
            tr("Canvas (*.dat)"));


    if (fileName.isEmpty()){
        return;
    }else {
        std::string file = fileName.toUtf8().constData();
        Canvas2D::saveFile(file);
    }
}

// **********************************************************
// Funcoes nao utilizadas
// **********************************************************
void Canvas2D::wheelEvent(QWheelEvent *event) //callback de mouse
{
    //printf("\nMouse Wheel event: %d", event->delta() );
    qDebug("Mouse Wheel event %d", event->delta() );
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
    height = this->geometry().height();
    width = this->geometry().width();

    //qDebug("alterou --> %d - %d", height, width);
}

void Canvas2D::mouseReleaseEvent(QMouseEvent *event) //callback de mouse
{
    //qDebug("\nMouse Release: %d %d", event->x(), (height-event->y()));
}
