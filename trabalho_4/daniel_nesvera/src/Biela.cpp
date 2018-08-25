/**
 * @file    biela.cpp
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Modelagem da biela
 *
 *
 *
 */

#include "biela.h"

#include <gl/glut.h> //gl utility toolkit
#include <gl/gl.h>  //gl utility

Biela::Biela(Vector3 *pInit)
{
   posInit = new Vector3(pInit->x, pInit->y, pInit->z);

   width = 40;
   length = 40;
   height = 410;

   cubo = new Cubo(posInit, width, length, height);

   gamaAngle = 0;
}

void Biela::SetAngle(float ang){

   gamaAngle = (ang*180)/3.14 - 90;

}

void Biela::SetPosition(Vector3 *pInit){
   pInit->y += height/2;
   cubo->SetPosition(pInit);
   posInit = new Vector3(pInit->x, pInit->y, pInit->z);
}

void Biela::Render(){

   glPushMatrix();

   glShadeModel(GL_SMOOTH);
   glTranslated(0, +(posInit->y - height/2.), +(posInit->z));
   glRotated(gamaAngle, 1, 0, 0);
   glTranslated(0, -(posInit->y - height/2.), -(posInit->z));


   cubo->Render();

   glPopMatrix();

}
