/**
 * @file    pistao.cpp
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Modelagem da pistao
 *
 */

#include "Pistao.h"

#include <gl/glut.h> //gl utility toolkit
#include <gl/gl.h>  //gl utility

Pistao::Pistao(Vector3 *pInit)
{
   posInit = pInit;

   float cilindro_0Raio = 60;
   float cilindro_0Largura = 120;
   Vector3 cilindro_0Pos = Vector3(posInit->x, posInit->y, posInit->z);
   cilindro_0 = new Cilindro(&cilindro_0Pos, cilindro_0Raio, cilindro_0Largura);
   cilindro_0->CloseCilindro(true);
   cilindro_0->SetNumSides(50);
   cilindro_0->SetResolucao(10);

   posTrans = new Vector3(pInit->x, pInit->y, pInit->z);

}

void Pistao::SetPosition(Vector3 *pos){
   posInit = new Vector3(pos->x, pos->y, pos->z);
}

void Pistao::Render(){

   glPushMatrix();

   glTranslated(posInit->x, posInit->y, posInit->z);
   glTranslated(-posTrans->x, -posTrans->y, -posTrans->z);

   glTranslated(+posTrans->x, +posTrans->y, +posTrans->z);
   glRotated(90, 0, 0, 1);
   glTranslated(-posTrans->x, -posTrans->y, -posTrans->z);



   cilindro_0->Render();

   glPopMatrix();

}

