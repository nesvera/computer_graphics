#include "UIComponent.h"

using namespace std;

#ifndef TEXTO_H
#define TEXTO_H

class Texto : public UIComponent{

public:
   Texto(int _x, int _y, char *_str );
   Texto(int _x, int _y, char *_str, uint8_t _r, uint8_t _g, uint8_t _b);
   void render();
   void setText(char *_txt);

private:
   char *str;
   int x, y;

};

#endif // TEXTO_H
