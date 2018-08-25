#include "UIComponent.h"
#include "Texto.h"

using namespace std;

#ifndef CHECKBOX_H
#define CHECKBOX_H

class Checkbox : public UIComponent{

public:
   Checkbox(int _x, int _y, char *txt);
   Checkbox(int _x, int _y, char *txt, uint8_t _r, uint8_t _g, uint8_t _b);
   void render();
   void setTextColor(uint8_t _r, uint8_t _g, uint8_t _b);
   bool isChecked();

   void mouseHandler(int _button, int _state, int _x, int _y);

private:
   int x, y;
   int box_x0, box_y0, box_x1, box_y1;
   int check_x, check_y;

   char *txt;
   Texto *texto;

   // Length e width de um caracter eh aproximadamente 10 pixel
   int characterSize = 10;
   int characterSpace = 10;

   bool checked;

};

#endif // CHECKBOX_H
