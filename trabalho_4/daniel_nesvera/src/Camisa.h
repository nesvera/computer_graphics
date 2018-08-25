#ifndef CAMISA_H
#define CAMISA_H

#include "Vector3.h"
#include "Cilindro.h"

using namespace std;

class Camisa
{
public:
   Camisa(Vector3 *posInit);

   void Render();

private:
   Vector3 *posInit;

   Cilindro *cilindro_0;

};

#endif // CAMISA_H
