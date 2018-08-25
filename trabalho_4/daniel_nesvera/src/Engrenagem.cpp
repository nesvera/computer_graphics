/**
 * @author  Daniel André Nesvera
 *
 *    Modelagem de um engrenagem
 *
 */

#include "Engrenagem.h"

#include "Cilindro.h"

#include <GL/gl.h>
#include <GL/glut.h>

#include <math.h>

#include "Vector3.h"
#include "Matrix3.h"

#define M_PI 3.14159265358979323846

Engrenagem::Engrenagem(Vector3 *_posInit, float _raio, float _largura){

   posInit = new Vector3(_posInit->x, _posInit->y, _posInit->z);

   raio_1 = _raio;
   raio_2 = _raio;
   largura = _largura;

   resolucao = 10;

   nSides = 6;

   fechado = true;
}

void Engrenagem::SetDentes(int num ){
   nDentes = num;
}

void Engrenagem::SetRaio(float r1, float r2){
   raio_1 = r1;
   raio_2 = r2;
}

void Engrenagem::SetNumSides(int num){
   nSides = num;
}

void Engrenagem::SetResolucao(int num){
   resolucao = num;
}

void Engrenagem::SetPosicao(Vector3 *pos){
   posInit = new Vector3(pos->x, pos->y, pos->z);
}

void Engrenagem::Render(){

   float raio;

   double angInc = (2*M_PI)/nSides;
   double ladoInc = (double)largura/resolucao;

   int pontosPorDente = nSides/nDentes;

   int countPontosPorDente = 0;
   bool usarRaio1 = true;

   Vector3 p0 = Vector3(posInit->x, posInit->y, posInit->z);      //center
   Vector3 p1 = p0;
   Vector3 p2 = p0;
   Vector3 p3 = p0;
   Vector3 edge0, edge1;
   Vector3 normal;

   glShadeModel(GL_SMOOTH);
   glPushMatrix();

   // Lateral do cilindro

   glBegin(GL_TRIANGLE_FAN);
      for(int i=0 ; i<nSides; i++ ){

         if( i%pontosPorDente == 0){
            usarRaio1 = !usarRaio1;
         }

         if( usarRaio1 ){
            raio = raio_1;
         }else{
            raio = raio_2;
         }

         p1.y = raio*cos(i*angInc) + posInit->y;
         p1.z = raio*sin(i*angInc) + posInit->z;

         p2.y = raio*cos((i+1)*angInc) + posInit->y;
         p2.z = raio*sin((i+1)*angInc) + posInit->z;

         if( i == 0 ){
            edge0 = (p0-p1);
            edge1 = (p0-p2);

            normal = edge0^edge1;
            normal = normal.normalize();

            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3f(p0.x, p0.y, p0.z);
         }

         glVertex3f(p1.x, p1.y, p1.z);
         glVertex3f(p2.x, p2.y, p2.z);
      }
   glEnd();


   p0 = Vector3(posInit->x+largura, posInit->y, posInit->z);
   p1 = p0;
   p2 = p0;

   glBegin(GL_TRIANGLE_FAN);
      for(int i=0 ; i<nSides; i++ ){

         if( i%pontosPorDente == 0){
            usarRaio1 = !usarRaio1;
         }

         if( usarRaio1 ){
            raio = raio_1;
         }else{
            raio = raio_2;
         }

         p1.y = raio*cos(i*angInc) + posInit->y;
         p1.z = raio*sin(i*angInc) + posInit->z;

         p2.y = raio*cos((i+1)*angInc) + posInit->y;
         p2.z = raio*sin((i+1)*angInc) + posInit->z;

         if( i == 0 ){
            edge0 = (p0-p1);
            edge1 = (p0-p2);

            normal = edge0^edge1;
            normal = normal.normalize();

            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3f(p0.x, p0.y, p0.z);
         }

         glVertex3f(p1.x, p1.y, p1.z);
         glVertex3f(p2.x, p2.y, p2.z);
      }
   glEnd();


   // Corpo do cilindro
   Vector3 mapCilindro[nSides][resolucao+1];

   for(int i=0; i<nSides; i++){

      if( i%pontosPorDente == 0){
         usarRaio1 = !usarRaio1;
      }

      if( usarRaio1 ){
         raio = raio_1;
      }else{
         raio = raio_2;
      }

      p0.x = posInit->x;
      p0.y = raio*cos(i*angInc) + posInit->y;
      p0.z = raio*sin(i*angInc) + posInit->z;

      for(int j=0; j<resolucao+1; j++ ){
         p0.x = j*ladoInc + posInit->x;

         mapCilindro[i][j] = p0;
      }
   }

   glBegin(GL_QUADS);
      for(int i=0; i<nSides; i++ ){
         for(int j=0; j<resolucao; j++ ){

            if(i<nSides-1){
               p0 = mapCilindro[i][j];
               p1 = mapCilindro[i+1][j];
               p2 = mapCilindro[i][j+1];
               p3 = mapCilindro[i+1][j+1];
            }else{
               p0 = mapCilindro[i][j];
               p1 = mapCilindro[0][j];
               p2 = mapCilindro[i][j+1];
               p3 = mapCilindro[0][j+1];
            }

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

 glPopMatrix();

}
