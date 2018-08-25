#ifndef PISTAO_H
#define PISTAO_H

#include "Vector3.h"
#include "Matrix4.h"
#include "Cilindro.h"

using namespace std;

class Pistao
{
public:
   Pistao(Vector3 *posInit);

   void Render();
   void SetPosition(Vector3 *pos);

   Vector3 *posInit;
   Vector3 *posTrans;


   Cilindro *cilindro_0;

};

#endif // PISTAO_H
