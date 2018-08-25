#ifndef VIRABREQUIM_H
#define VIRABREQUIM_H

#include <list>
#include "matrix4.h"
#include "Vector3.h"
#include "Cilindro.h"
#include "Engrenagem.h"

using namespace std;

class Virabrequim
{
public:
   float angle;

   Virabrequim(Vector3 *posInit);

   void Render();
   void SetAngle(float ang);

private:

   Vector3 *posInit;
   Vector3 *rightVec;
   Vector3 *upVec;
   Vector3 *forwardVec;

   Vector3 *biela_0Pos;
   Vector3 *biela_1Pos;

   Cilindro *cilindro_0;
   Cilindro *cilindro_1;
   Cilindro *cilindro_2;
   Cilindro *cilindro_3;
   Cilindro *cilindro_4;
   Cilindro *cilindro_5;
   Cilindro *cilindro_6;
   Cilindro *cilindro_7;
   Engrenagem *engrenagem;


};

#endif // VIRABREQUIM_H
