/**
 * @file    virabrequim.cpp
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Modelagem do virabrequim
 *
 */

#include "Virabrequim.h"
#include "Vector3.h"
#include "matrix4.h"
#include "Cilindro.h"
#include "Engrenagem.h"

#include <gl/glut.h> //gl utility toolkit
#include <gl/gl.h>  //gl utility

Virabrequim::Virabrequim(Vector3 *pInit){

   posInit = pInit;

   angle = 0;

   float bielaOffset = 100;

   float cilindro_0Raio = 100;
   float cilindro_0Largura = 200;
   Vector3 cilindro_0Pos = Vector3(posInit->x, posInit->y, posInit->z);
   cilindro_0 = new Cilindro(&cilindro_0Pos, cilindro_0Raio, cilindro_0Largura);
   cilindro_0->CloseCilindro(true);
   cilindro_0->SetNumSides(50);
   cilindro_0->SetResolucao(10);

   float cilindro_1Raio = 200;
   float cilindro_1Largura = 50;
   Vector3 cilindro_1Offset = Vector3(200, 0, 0);
   Vector3 cilindro_1Pos = cilindro_0Pos + cilindro_1Offset;
   cilindro_1 = new Cilindro(&cilindro_1Pos, cilindro_1Raio, cilindro_1Largura);
   cilindro_1->CloseCilindro(true);
   cilindro_1->SetNumSides(50);
   cilindro_1->SetResolucao(10);

   float cilindro_2Raio = 40;
   float cilindro_2Largura = 80;
   Vector3 cilindro_2Offset = Vector3(50, bielaOffset, 0);
   Vector3 cilindro_2Pos = cilindro_1Pos + cilindro_2Offset;
   cilindro_2 = new Cilindro(&cilindro_2Pos, cilindro_2Raio, cilindro_2Largura);
   cilindro_2->CloseCilindro(true);
   cilindro_2->SetNumSides(50);
   cilindro_2->SetResolucao(10);

   float cilindro_3Raio = 200;
   float cilindro_3Largura = 50;
   Vector3 cilindro_3Offset = Vector3(80, -bielaOffset, 0);
   Vector3 cilindro_3Pos = cilindro_2Pos + cilindro_3Offset;
   cilindro_3 = new Cilindro(&cilindro_3Pos, cilindro_3Raio, cilindro_3Largura);
   cilindro_3->CloseCilindro(true);
   cilindro_3->SetNumSides(50);
   cilindro_3->SetResolucao(10);

   float cilindro_4Raio = 40;
   float cilindro_4Largura = 80;
   Vector3 cilindro_4Offset = Vector3(50, -bielaOffset, 0);
   Vector3 cilindro_4Pos = cilindro_3Pos + cilindro_4Offset;
   cilindro_4 = new Cilindro(&cilindro_4Pos, cilindro_4Raio, cilindro_4Largura);
   cilindro_4->CloseCilindro(true);
   cilindro_4->SetNumSides(50);
   cilindro_4->SetResolucao(10);

   float cilindro_5Raio = 200;
   float cilindro_5Largura = 50;
   Vector3 cilindro_5Offset = Vector3(80, +bielaOffset, 0);
   Vector3 cilindro_5Pos = cilindro_4Pos + cilindro_5Offset;
   cilindro_5 = new Cilindro(&cilindro_5Pos, cilindro_5Raio, cilindro_5Largura);
   cilindro_5->CloseCilindro(true);
   cilindro_5->SetNumSides(50);
   cilindro_5->SetResolucao(10);

   float cilindro_6Raio = 100;
   float cilindro_6Largura = 210;
   Vector3 cilindro_6Offset = Vector3(50, 0, 0);
   Vector3 cilindro_6Pos = cilindro_5Pos + cilindro_6Offset;
   cilindro_6 = new Cilindro(&cilindro_6Pos, cilindro_6Raio, cilindro_6Largura);
   cilindro_6->CloseCilindro(true);
   cilindro_6->SetNumSides(50);
   cilindro_6->SetResolucao(10);

   float engrenagem_Raio1 = 300;
   float engrenagem_Raio2 = 270;
   float engrenagem_Largura = 80;
   Vector3 engrenagem_Offset = Vector3(210, 0, 0);
   Vector3 engrenagem_Pos = cilindro_6Pos + engrenagem_Offset;
   engrenagem = new Engrenagem(&engrenagem_Pos, engrenagem_Raio1, engrenagem_Largura);
   engrenagem->SetNumSides(150);
   engrenagem->SetResolucao(10);
   engrenagem->SetDentes(50);
   engrenagem->SetRaio(engrenagem_Raio1, engrenagem_Raio2);

}

void Virabrequim::SetAngle(float ang){
   angle = ang;
}

void Virabrequim::Render(){


   glPushMatrix();

   glShadeModel(GL_SMOOTH);
   glTranslated(+posInit->x, +posInit->y, +posInit->z);
   glRotated(angle, 1, 0, 0);
   glTranslated(-posInit->x, -posInit->y, -posInit->z);

   cilindro_0->Render();
   cilindro_1->Render();
   cilindro_2->Render();
   cilindro_3->Render();
   cilindro_4->Render();
   cilindro_5->Render();
   cilindro_6->Render();
   engrenagem->Render();

   glPopMatrix();

}

