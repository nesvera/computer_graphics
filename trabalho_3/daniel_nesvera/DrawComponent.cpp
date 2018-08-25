/**
 * @file    DrawComponent.cpp
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 * Implementa classe pai
 *
 */

#include "DrawComponent.h"

DrawComponent::DrawComponent(){
    isSelected = true;
}

void DrawComponent::render(Canvas2D *canvas, int w, int h){
}

void DrawComponent::mouseHandler(){

}

void DrawComponent::mouseMoveHandler(int x, int y, int w, int h){

}

bool DrawComponent::isInFocus(){
    return isSelected;
}

void DrawComponent::disableFocus(){
    isSelected = false;
}

bool DrawComponent::mouseSelectClickHandler(int x, int y, int w, int h){

}

int DrawComponent::getMemSize(){

}

void DrawComponent::saveComponent(FILE *f){

}

void DrawComponent::addControlPoint(int x, int y, int w, int h){

}

void DrawComponent::setControlPoint(int x, int y, int w, int h, int n){

}

int DrawComponent::getType(){
    return componentType;
}
