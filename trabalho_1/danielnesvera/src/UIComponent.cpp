/**
 * @file    UIComponent.cpp
 * @date    16/04/2018
 * @author  Daniel Andr� Nesvera
 *
 *    Classe base de todos objetos de interface gr�fica do software
 *    Desenvolvido para tornar mais f�cil a chamada de rendezi��o
 *
 */

#include "UIComponent.h"

UIComponent::UIComponent(){
   active = true;
}

void UIComponent::render(){

}

void UIComponent::mouseHandler(int _button, int _state, int _x, int _y){

}

bool UIComponent::isActive(){
   return active;
}

void UIComponent::setColor(uint8_t _r, uint8_t _g, uint8_t _b ){
   r = _r/255.0;
   g = _g/255.0;
   b = _b/255.0;
}

void UIComponent::setActive(bool _state){
   active = _state;
}

bool UIComponent::wasPressed(){
   return false;
}

void UIComponent::setText(char *_txt){

}

bool UIComponent::isChecked(){
   return false;
}
