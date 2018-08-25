/**
 * @file    Checkbox.cpp
 * @date    16/04/2018
 * @author  Daniel André Nesvera
 *
 *    Classe com herança da classe UIComponent.
 *    Implementa o componente checkbox
 *
 */

#include "Checkbox.h"

Checkbox::Checkbox(int _x, int _y, char *_txt){
   x = _x;
   y = _y;

   txt = _txt;

   box_x0 = x;
   box_y0 = y;
   box_x1 = box_x0 + characterSize + characterSpace;
   box_y1 = box_y0 + characterSize + characterSpace;

   check_x = box_x0 + characterSpace/2;
   check_y = box_y0 + characterSpace/2;

   int txt_x = box_x1 + characterSpace;
   int txt_y = check_y;
   texto = new Texto( txt_x, txt_y, txt, 0, 0, 0);

   checked = true;
}

Checkbox::Checkbox(int _x, int _y, char *_txt, uint8_t _r, uint8_t _g, uint8_t _b){
   x = _x;
   y = _y;

   txt = _txt;

   box_x0 = x;
   box_y0 = y;
   box_x1 = box_x0 + characterSize + characterSpace;
   box_y1 = box_y0 + characterSize + characterSpace;

   check_x = box_x0 + characterSpace/2;
   check_y = box_y0 + characterSpace/2;

   int txt_x = box_x1 + characterSpace;
   int txt_y = check_y;
   texto = new Texto( txt_x, txt_y, txt, _r, _g, _b);

   checked = true;
}

void Checkbox::render(){
   color(0, 0, 0);
   rect(box_x0, box_y0, box_x1, box_y1);

   if( checked ){
      color(0, 0, 0);
      text(check_x, check_y, "X");
   }

   if( texto != NULL ){
      texto->render();
   }
}

void Checkbox::setTextColor(uint8_t _r, uint8_t _g, uint8_t _b){
   if( texto != NULL ){
      texto->setColor(_r, _g, _b);
   }
}

void Checkbox::mouseHandler(int _button, int _state, int _x, int _y){

   if( _x >= box_x0 && _x<= box_x1 && _y >= box_y0 && _y <= box_y1 ){

      if( _button == 0 && _state == 1 ){
         if(isChecked()){
            checked = false;
         }else{
            checked = true;
         }
      }
   }
}

bool Checkbox::isChecked(){
   return checked;
}
