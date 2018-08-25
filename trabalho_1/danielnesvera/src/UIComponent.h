#include "gl_canvas2d.h"
#include <stdint.h>

using namespace std;

#ifndef UICOMPONENT_H
#define UICOMPONENT_H

class UIComponent{
public:

   UIComponent();


   void keyboardHandler();
   void setColor(uint8_t _r, uint8_t _g, uint8_t _b);
   void setActive(bool _state);
   bool isActive();

   virtual void mouseHandler(int _button, int _state, int _x, int _y);
   virtual void render();
   virtual bool wasPressed();
   virtual bool isChecked();
   virtual void setText(char *_txt);

protected:
   bool active;
   float r, g, b;
   int x0, y0, x1, y1;

};

#endif // UICOMPONENT_H
