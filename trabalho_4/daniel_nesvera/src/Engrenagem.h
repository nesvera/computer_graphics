#ifndef ENGRENAGEM_H_INCLUDED
#define ENGRENAGEM_H_INCLUDED

#include "Vector3.h"

using namespace std;

class Engrenagem
{
public:
   Engrenagem(Vector3 *posInit, float raio, float largura);

   void Render();
   void SetNumSides(int num);
   void SetResolucao(int num);
   void SetPosicao(Vector3 *pos);
   void SetRaio(float r1, float r2);
   void SetDentes(int num);

private:

   Vector3 *posInit;

   float raio_1;
   float raio_2;
   float nDentes;
   float largura;
   int resolucao;          // quantos quadrados tem o cilindro
   int nSides;             // quantos lados tem o circulo

   bool fechado;
};

#endif // ENGRENAGEM_H_INCLUDED
