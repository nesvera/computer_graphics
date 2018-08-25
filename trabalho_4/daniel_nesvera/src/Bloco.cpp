/**
 * @file    bloco.cpp
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Modelagem do bloco
 *
 */

#include "bloco.h"
#include <gl/glut.h> //gl utility toolkit
#include <gl/gl.h>  //gl utility

Bloco::Bloco(Vector3 *pInit)
{
   posInit = pInit;

   cubo = new Cubo(posInit, 500, 670, 810);
}

void Bloco::Render(){
   glPushMatrix();

   cubo->Render();

   glPopMatrix();
}
