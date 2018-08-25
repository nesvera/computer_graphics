#ifndef CILINDRO_H
#define CILINDRO_H

#include "Vector3.h"

using namespace std;

class Cilindro
{
public:
   Cilindro(Vector3 *posInit, float raio, float largura);

   void Render();
   void CloseCilindro(bool fechado);
   void SetNumSides(int num);
   void SetResolucao(int num);
   void SetPosicao(Vector3 *pos);

private:

   Vector3 *posInit;

   float raio;
   float largura;
   int resolucao;          // quantos quadrados tem o cilindro
   int nSides;             // quantos lados tem o circulo

   bool fechado;
};


#endif // CILINDRO_H_INCLUDED
