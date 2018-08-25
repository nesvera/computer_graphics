/**
 * @file    PanelOrtogonal.cpp
 * @date    16/04/2018
 * @author  Daniel André Nesvera
 *
 *    Painel contém os gráficos das funçÕes ortogonais
 *
 */

#include "PanelOrtogonal.h"

PanelOrtogonal::PanelOrtogonal(int _x0, int _y0, int _x1, int _y1, bool _active){

   // Initialize the panel shape and background
   x0 = _x0;
   y0 = _y0;
   x1 = _x1;
   y1 = _y1;

   PanelOrtogonal:setColor(218, 223, 225);

   active = _active;

   // Add panel components
   numComponents = 16;
   uiComponents = (UIComponent **)malloc(numComponents*sizeof(UIComponent *));



   int plotHeight = 60;
   int plotWidth = 400;

   int xInit = _x0 + 50;
   int yInit = _y1 - 100;
   uiComponents[0] = (UIComponent *)new Plot(xInit, yInit, xInit+plotWidth, yInit+plotHeight, 1, 100);
   yInit -= 80;
   uiComponents[1] = (UIComponent *)new Plot(xInit, yInit, xInit+plotWidth, yInit+plotHeight, 0., 100);
   yInit -= 80;
   uiComponents[2] = (UIComponent *)new Plot(xInit, yInit, xInit+plotWidth, yInit+plotHeight, 0., 100);
   yInit -= 80;
   uiComponents[3] = (UIComponent *)new Plot(xInit, yInit, xInit+plotWidth, yInit+plotHeight, 0., 100);
   yInit -= 80;
   uiComponents[4] = (UIComponent *)new Plot(xInit, yInit, xInit+plotWidth, yInit+plotHeight, 0., 100);
   yInit -= 80;
   uiComponents[5] = (UIComponent *)new Plot(xInit, yInit, xInit+plotWidth, yInit+plotHeight, 0., 100);
   yInit -= 80;
   uiComponents[6] = (UIComponent *)new Plot(xInit, yInit, xInit+plotWidth, yInit+plotHeight, 0., 100);
   yInit -= 80;
   uiComponents[7] = (UIComponent *)new Plot(xInit, yInit, xInit+plotWidth, yInit+plotHeight, 0., 100);

   xInit = _x0 + 500;
   yInit = _y1 - 100;
   uiComponents[8] = (UIComponent *)new Plot(xInit, yInit, xInit+plotWidth, yInit+plotHeight, 0., 100);
   yInit -= 80;
   uiComponents[9] = (UIComponent *)new Plot(xInit, yInit, xInit+plotWidth, yInit+plotHeight, 0., 100);
   yInit -= 80;
   uiComponents[10] = (UIComponent *)new Plot(xInit, yInit, xInit+plotWidth, yInit+plotHeight, 0., 100);
   yInit -= 80;
   uiComponents[11] = (UIComponent *)new Plot(xInit, yInit, xInit+plotWidth, yInit+plotHeight, 0., 100);
   yInit -= 80;
   uiComponents[12] = (UIComponent *)new Plot(xInit, yInit, xInit+plotWidth, yInit+plotHeight, 0., 100);
   yInit -= 80;
   uiComponents[13] = (UIComponent *)new Plot(xInit, yInit, xInit+plotWidth, yInit+plotHeight, 0., 100);
   yInit -= 80;
   uiComponents[14] = (UIComponent *)new Plot(xInit, yInit, xInit+plotWidth, yInit+plotHeight, 0., 100);
   yInit -= 80;
   uiComponents[15] = (UIComponent *)new Plot(xInit, yInit, xInit+plotWidth, yInit+plotHeight, 0., 100);

}

void PanelOrtogonal::render(){

   if( active ){
      // draw background
      color(r,g,b);
      for(int y = y0 ; y<=y1 ; y++ ){
         line(x0, y, x1, y);
      }

      // draw UI components
      for(int i=0 ; i<numComponents ; i++){
         uiComponents[i]->render();
      }
   }
}
