/**
 * @file    Button.cpp
 * @date    16/04/2018
 * @author  Daniel André Nesvera
 *
 *    Classe com herança da classe UIComponent.
 *    Implementa o componente botão com funçoes de click e hover
 *
 */

#include "Button.h"
Button::Button(int _x0, int _y0, int _x1, int _y1):UIComponent(){
   x0 = _x0;
   y0 = _y0;
   x1 = _x1;
   y1 = _y1;

   txt = NULL;
   texto = NULL;

   Button:setColor(156, 156, 156);

   buttonPressed = false;
}

Button::Button(int _x0, int _y0, int _x1, int _y1, char *_txt):UIComponent(){
   x0 = _x0;
   y0 = _y0;
   x1 = _x1;
   y1 = _y1;

   txt = _txt;

   // Posiciona o texto no centro do botão
   int txt_x0 = ((x1+x0)/2)-(strlen(txt)*character_size/2);
   int txt_y0 = ((y1+y0)/2)-(character_size/2);

   // cria o texto do botao
   texto = new Texto(txt_x0, txt_y0, txt);

   // Seta cor do botão
   Button:setColor(156, 156, 156);

   buttonPressed = false;
}

Button::Button(int _x0, int _y0, char *_txt):UIComponent(){
   x0 = _x0;
   y0 = _y0;

   txt = _txt;

   int txt_x0 = x0 + character_space;
   int txt_y0 = y0 + character_space;
   texto = new Texto(txt_x0, txt_y0, txt);

   x1 = txt_x0 + strlen(txt)*character_size + character_space;
   y1 = txt_y0 + character_size + character_space;

   Button:setColor(156, 156, 156);

   buttonPressed = false;
}


void Button::render(){

   if( UIComponent::active ){
      color(0, 0, 0);
      rect(x0, y0, x1, y1);

      color(r, g, b);
      for(int i = (y0+1) ; i<y1 ; i++){
         line(x0, i, (x1-1), i);
      }

      texto->render();
   }
}

void Button::setTextColor(uint8_t _r, uint8_t _g, uint8_t _b){
   if( texto != NULL ){
      texto->setColor(_r, _g, _b);
   }
}

void Button::mouseHandler(int _button, int _state, int _x, int _y){
   int r,g, b;

   // Hover over
   if( _x >= x0 && _x<= x1 && _y >= y0 && _y <= y1 ){

      // Left button wasPressed
      if( _button == 0 && _state == 0 ){
         r = 116;
         g = 116;
         b = 116;

      // Left button wasReleased
      }else if( _button == 0 && _state == 1 ){
         r = 156;
         g = 156;
         b = 156;

         // do-something
         buttonPressed = true;

      // Hover
      }else{
         r = 146;
         g = 146;
         b = 146;

      }

   // Hover off
   }else{
      r = 156;
      g = 156;
      b = 156;

   }

   Button::setColor(r,g,b);
}

bool Button::wasPressed(){
   bool buttonState = buttonPressed;
   buttonPressed = false;

   return buttonState;
}
