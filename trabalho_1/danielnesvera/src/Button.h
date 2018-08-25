#include "UIComponent.h"
#include "Texto.h"

using namespace std;

#ifndef BUTTON_H
#define BUTTON_H

class Button : public UIComponent{

public:
   Button(int _x0, int _y0, int _x1, int _y1);
   Button(int _x0, int _y0, int _x1, int _y1, char *_txt);
   Button(int _x0, int _y0, char *_txt);
   void render();
   void setTextColor(uint8_t _r, uint8_t _g, uint8_t _b);
   void mouseHandler(int _button, int _state, int _x, int _y);
   bool wasPressed();

private:
   char *txt;
   Texto *texto;

   // Length e width de um caracter eh aproximadamente 10 pixel
   int character_size = 10;
   int character_space = 10;

   bool buttonPressed;

};

#endif // BUTTON_H
