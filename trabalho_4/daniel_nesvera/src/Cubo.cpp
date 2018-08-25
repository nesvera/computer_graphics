/**
 * @author  Daniel André Nesvera
 *
 *    Modelagem de um cubo
 *
 */

#include "Cubo.h"

#include <gl/glut.h> //gl utility toolkit
#include <gl/gl.h>  //gl utility

Cubo::Cubo(Vector3 *pInit, float w, float l, float h )
{
   posInit = new Vector3(pInit->x, pInit->y, pInit->z);

   width = w;
   length = l;
   height = h;

   resolucao = 10;

}

void Cubo::SetPosition(Vector3 *pInit){
   posInit = posInit = new Vector3(pInit->x, pInit->y, pInit->z);
}

void Cubo::Render(){

   double widthInc = (double)width/resolucao;
   double heightInc = (double)height/resolucao;
   double lengthInc = (double)length/resolucao;

   Vector3 edge0;
   Vector3 edge1;
   Vector3 normal;

   Vector3 p0;
   Vector3 p1;
   Vector3 p2;
   Vector3 p3;
   Vector3 mapCilindro[resolucao+1][resolucao+1];

   glShadeModel(GL_SMOOTH);
   glPushMatrix();

   // plano z-x baixo
   for(int i=0; i<resolucao+1; i++){
      for(int j=0; j<resolucao+1; j++ ){
         p0.x = (posInit->x) + i*lengthInc;
         p0.y = (posInit->y - height/2.);
         p0.z = (posInit->z - width/2.) + j*widthInc;

         mapCilindro[i][j] = p0;
      }
   }

   glBegin(GL_QUADS);
      for(int i=0; i<resolucao; i++ ){
         for(int j=0; j<resolucao; j++ ){

            p0 = mapCilindro[i][j];
            p1 = mapCilindro[i+1][j];
            p2 = mapCilindro[i][j+1];
            p3 = mapCilindro[i+1][j+1];

            edge0 = (p0-p1);
            edge1 = (p0-p2);

            normal = edge0^edge1;
            normal = normal.normalize();

            glNormal3f(-normal.x, -normal.y, -normal.z);
            glVertex3f(p0.x, p0.y, p0.z);
            glVertex3f(p1.x, p1.y, p1.z);
            glVertex3f(p3.x, p3.y, p3.z);
            glVertex3f(p2.x, p2.y, p2.z);

         }
      }
   glEnd();

   // plano z-x alto
   for(int i=0; i<resolucao+1; i++){
      for(int j=0; j<resolucao+1; j++ ){
         p0.x = (posInit->x) + i*lengthInc;
         p0.y = (posInit->y + height/2.);
         p0.z = (posInit->z - width/2.) + j*widthInc;

         mapCilindro[i][j] = p0;
      }
   }

   glBegin(GL_QUADS);
      for(int i=0; i<resolucao; i++ ){
         for(int j=0; j<resolucao; j++ ){

            p0 = mapCilindro[i][j];
            p1 = mapCilindro[i+1][j];
            p2 = mapCilindro[i][j+1];
            p3 = mapCilindro[i+1][j+1];

            edge0 = (p0-p1);
            edge1 = (p0-p2);

            normal = edge0^edge1;
            normal = normal.normalize();

            glNormal3f(-normal.x, -normal.y, -normal.z);
            glVertex3f(p0.x, p0.y, p0.z);
            glVertex3f(p1.x, p1.y, p1.z);
            glVertex3f(p3.x, p3.y, p3.z);
            glVertex3f(p2.x, p2.y, p2.z);

         }
      }
   glEnd();

   // plano y-x tras
   for(int i=0; i<resolucao+1; i++){
      for(int j=0; j<resolucao+1; j++ ){
         p0.x = (posInit->x) + i*lengthInc;
         p0.y = (posInit->y - height/2.) + j*heightInc;
         p0.z = (posInit->z - width/2.);

         mapCilindro[i][j] = p0;
      }
   }

   glBegin(GL_QUADS);
      for(int i=0; i<resolucao; i++ ){
         for(int j=0; j<resolucao; j++ ){

            p0 = mapCilindro[i][j];
            p1 = mapCilindro[i+1][j];
            p2 = mapCilindro[i][j+1];
            p3 = mapCilindro[i+1][j+1];

            edge0 = (p0-p1);
            edge1 = (p0-p2);

            normal = edge0^edge1;
            normal = normal.normalize();

            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3f(p0.x, p0.y, p0.z);
            glVertex3f(p1.x, p1.y, p1.z);
            glVertex3f(p3.x, p3.y, p3.z);
            glVertex3f(p2.x, p2.y, p2.z);

         }
      }
   glEnd();

   // plano y-x frente
   for(int i=0; i<resolucao+1; i++){
      for(int j=0; j<resolucao+1; j++ ){
         p0.x = (posInit->x) + i*lengthInc;
         p0.y = (posInit->y - height/2.) + j*heightInc;
         p0.z = (posInit->z + width/2.);

         mapCilindro[i][j] = p0;
      }
   }

   glBegin(GL_QUADS);
      for(int i=0; i<resolucao; i++ ){
         for(int j=0; j<resolucao; j++ ){

            p0 = mapCilindro[i][j];
            p1 = mapCilindro[i+1][j];
            p2 = mapCilindro[i][j+1];
            p3 = mapCilindro[i+1][j+1];

            edge0 = (p0-p1);
            edge1 = (p0-p2);

            normal = edge0^edge1;
            normal = normal.normalize();

            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3f(p0.x, p0.y, p0.z);
            glVertex3f(p1.x, p1.y, p1.z);
            glVertex3f(p3.x, p3.y, p3.z);
            glVertex3f(p2.x, p2.y, p2.z);

         }
      }
   glEnd();

   // plano y-z esquerda
   for(int i=0; i<resolucao+1; i++){
      for(int j=0; j<resolucao+1; j++ ){
         p0.x = (posInit->x);
         p0.y = (posInit->y - height/2.) + j*heightInc;
         p0.z = (posInit->z - width/2.) + i*widthInc;

         mapCilindro[i][j] = p0;
      }
   }

   glBegin(GL_QUADS);
      for(int i=0; i<resolucao; i++ ){
         for(int j=0; j<resolucao; j++ ){

            p0 = mapCilindro[i][j];
            p1 = mapCilindro[i+1][j];
            p2 = mapCilindro[i][j+1];
            p3 = mapCilindro[i+1][j+1];

            edge0 = (p0-p1);
            edge1 = (p0-p2);

            normal = edge0^edge1;
            normal = normal.normalize();

            glNormal3f(-normal.x, -normal.y, -normal.z);
            glVertex3f(p0.x, p0.y, p0.z);
            glVertex3f(p1.x, p1.y, p1.z);
            glVertex3f(p3.x, p3.y, p3.z);
            glVertex3f(p2.x, p2.y, p2.z);

         }
      }
   glEnd();

   // plano y-z direita
   for(int i=0; i<resolucao+1; i++){
      for(int j=0; j<resolucao+1; j++ ){
         p0.x = (posInit->x + length);
         p0.y = (posInit->y - height/2.) + j*heightInc;
         p0.z = (posInit->z - width/2.) + i*widthInc;

         mapCilindro[i][j] = p0;
      }
   }

   glBegin(GL_QUADS);
      for(int i=0; i<resolucao; i++ ){
         for(int j=0; j<resolucao; j++ ){

            p0 = mapCilindro[i][j];
            p1 = mapCilindro[i+1][j];
            p2 = mapCilindro[i][j+1];
            p3 = mapCilindro[i+1][j+1];

            edge0 = (p0-p1);
            edge1 = (p0-p2);

            normal = edge0^edge1;
            normal = normal.normalize();

            glNormal3f(-normal.x, -normal.y, -normal.z);
            glVertex3f(p0.x, p0.y, p0.z);
            glVertex3f(p1.x, p1.y, p1.z);
            glVertex3f(p3.x, p3.y, p3.z);
            glVertex3f(p2.x, p2.y, p2.z);

         }
      }
   glEnd();

 glPopMatrix();

}
