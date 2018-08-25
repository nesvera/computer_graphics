/**
 * @file    camisa.cpp
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Modelagem da camisa
 *
 */

#include "Camisa.h"

#include <gl/glut.h> //gl utility toolkit
#include <gl/gl.h>  //gl utility

Camisa::Camisa(Vector3 *pInit)
{
   posInit = pInit;

   float cilindro_0Raio = 60;
   float cilindro_0Largura = 280;
   Vector3 cilindro_0Pos = Vector3(posInit->x, posInit->y, posInit->z);
   cilindro_0 = new Cilindro(&cilindro_0Pos, cilindro_0Raio, cilindro_0Largura);
   cilindro_0->CloseCilindro(false);
   cilindro_0->SetNumSides(50);
   cilindro_0->SetResolucao(10);

}

void Camisa::Render(){

   glPushMatrix();

   glTranslated(+posInit->x, +posInit->y, +posInit->z);
   glRotated(90, 0, 0, 1);
   glTranslated(-posInit->x, -posInit->y, -posInit->z);

   cilindro_0->Render();

   glPopMatrix();

}
