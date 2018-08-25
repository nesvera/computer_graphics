/**
 * @file    Texto.cpp
 * @date    16/04/2018
 * @author  Daniel André Nesvera
 *
 *    Classe com herança da classe UIComponent.
 *    Implementa um objeto texto
 *
 */

#include "Texto.h"

Texto::Texto(int _x, int _y, char *_str):UIComponent(){
   x = _x;
   y = _y;
   str = _str;

   Texto:setColor(0, 0, 0);

   active = true;
}

Texto::Texto(int _x, int _y, char *_str, uint8_t _r, uint8_t _g, uint8_t _b):UIComponent(){
   x = _x;
   y = _y;
   str = _str;

   Texto:setColor(_r, _g, _b);

   active = true;
}

void Texto::render(){
   // draw on canvas if active
   if( active == true ){
      color(r, g, b);
      text(x, y, str);
   }
}

void Texto::setText(char *_txt){
   str = _txt;
}
