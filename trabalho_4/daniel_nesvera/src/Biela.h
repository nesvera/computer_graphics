#ifndef BIELA_H
#define BIELA_H

#include "Vector3.h"
#include "Cubo.h"

class Biela
{
public:
   Biela(Vector3 *pInit);

   void Render();
   void SetAngle(float ang);
   void SetPosition(Vector3 *pInit);

private:
   Vector3 *posInit;

   Cubo *cubo;

   float width;
   float height;
   float length;


   float gamaAngle;
};

#endif // BIELA_H
