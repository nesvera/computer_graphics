/**
 * @file    Plot.cpp
 * @date    16/04/2018
 * @author  Daniel André Nesvera
 *
 *    Classe com herança da classe UIComponent.
 *    Implementa a janela de um gráfico com até 3 sinais.
 *    Contém funções de auto ajuste e habilitar/desabiltar sinal
 *
 */

#include "Plot.h"

Plot::Plot(int _x0, int _y0, int _x1, int _y1, float freq, unsigned int _nSamples){
   x0 = _x0;
   y0 = _y0;
   x1 = _x1;
   y1 = _y1;

   PanelButton:setColor(255, 255, 255);

   active = true;

   // magic
   height = 0.83*(y1-y0);
   width = 0.83*(x1-x0);

   nSamples = _nSamples;
   short *newData = new short[nSamples];
   for(int i=0 ; i<nSamples ; i++ ){
      newData[i] = 1.*cos(i*freq);
   }

   data = (short **)malloc(3*sizeof(short *));

   data[0] = newData;
   data[1] = NULL;
   data[2] = NULL;

   signalView[0] = true;
   signalView[1] = false;
   signalView[2] = false;

   int _minY = 1000;
   int _maxY = -1000;
   for(int i=0 ; i<nSamples ;i++){
      if(data[0][i] < _minY) _minY = data[0][i];
      if(data[0][i] > _maxY) _maxY = data[0][i];
   }

   minY[0] = _minY;
   maxY[0] = _maxY;

   if(_minY == _maxY && maxY[0] <= 0) maxY[0] += 1;
   if(_minY == _maxY && maxY[0] > 0) minY[0] -= 1;

}

Plot::Plot(int _x0, int _y0, int _x1, int _y1, short *_data, unsigned int _nSamples){
   x0 = _x0;
   y0 = _y0;
   x1 = _x1;
   y1 = _y1;

   PanelButton:setColor(255, 255, 255);

   active = true;

   // magic
   height = 0.83*(y1-y0);
   width = 0.83*(x1-x0);


   data = (short **)malloc(3*sizeof(short *));

   nSamples = _nSamples;
   data[0] = _data;
   data[1] = NULL;
   data[2] = NULL;

   signalView[0] = true;
   signalView[1] = false;
   signalView[2] = false;

   int _minY = 1000;
   int _maxY = -1000;
   for(int i=0 ; i<nSamples ;i++){
      if(data[0][i] < _minY) _minY = data[0][i];
      if(data[0][i] > _maxY) _maxY = data[0][i];

      //printf("\n >>%d", data[0][i]);
   }

   minY[0] = _minY;
   maxY[0] = _maxY;

   if(_minY == _maxY && maxY[0] <= 0) maxY[0] += 1;
   if(_minY == _maxY && maxY[0] > 0) minY[0] -= 1;
}

void Plot::render(){

   if( active ){
      // draw background
      color(r,g,b);
      for(int y = y0 ; y<=y1 ; y++ ){
         line(x0, y, x1, y);
      }

      // contorno
      color(0, 0, 0);
      rect(x0, y0, x1, y1);

      int xCenter = (x0+x1)/2+0.07*width;
      int yCenter = (y0+y1)/2;

      // draw x&y axis lines
      int abscissaX;
      short abscissaY;
      remap(0, 0, &abscissaX, &abscissaY, 0);
      // abscissa line
      if(abscissaY<=(yInit+height) && abscissaY >= yInit){
         line((x0+0.15*width), abscissaY, (x1-0.03*width), abscissaY);
      }

      // ordenada line
      line((xCenter-width/2), (y0+0.05*height), (xCenter-width/2), (y1-0.05*height));

      color(1, 0, 0);
      //rect((xCenter-width/2), (yCenter-height/2), (xCenter+width/2), (yCenter+height/2));

      color(0, 0, 0);
      // min e max lines
      line((xCenter-width/2)-0.01*width, (yCenter+height/2), (xCenter-width/2)+0.01*width, (yCenter+height/2));
      line((xCenter-width/2)-0.01*width, (yCenter-height/2), (xCenter-width/2)+0.01*width, (yCenter-height/2));


      char strMin[6];
      char strMax[6];
      sprintf(strMin, "%d", minY[0]);
      sprintf(strMax, "%d", maxY[0]);

      text((xCenter-width/2)-50, (yCenter+height/2)-5, strMax);
      text((xCenter-width/2)-50, (yCenter-height/2)-5, strMin);

      // draw the signal
      xInit = xCenter - width/2;
      yInit = yCenter - height/2;

      if(signalView[0]){
         color(1, 0, 0);

         for(int i=0 ; i<nSamples ; i++){
            int x;
            short y;
            remap(i, data[0][i], &x, &y, 0);
            circleFill(x, y, 0.012*height, 10);

            if(i<nSamples-1){
               int x2;
               short y2;
               remap(i+1, data[0][i+1], &x2, &y2, 0);
               line(x, y, x2, y2);
            }

         }
      }

      if(signalView[1]){
         color(0, 0.7   , 0);

         for(int i=0 ; i<nSamples ; i++){
            int x;
            short y;
            remap(i, data[1][i], &x, &y, 0);
            circleFill(x, y, 0.012*height, 10);

            if(i<nSamples-1){
               int x2;
               short y2;
               remap(i+1, data[1][i+1], &x2, &y2, 0);
               line(x, y, x2, y2);
            }
         }
      }

      if(signalView[2]){
         color(0, 0, 1);

         for(int i=0 ; i<nSamples ; i++){
            int x;
            short y;
            remap(i, data[2][i], &x, &y, 0);
            circleFill(x, y, 0.012*height, 10);

            if(i<nSamples-1){
               int x2;
               short y2;
               remap(i+1, data[2][i+1], &x2, &y2, 0);
               line(x, y, x2, y2);
            }
         }
      }
   }
}

void Plot::remap(int _xIn, short _yIn, int *_xOut, short *_yOut, int _plotNum){

   int xInicio = xInit;
   int xFim = xInit + width;

   int yInicio = yInit;
   int yFim = yInit + height;

   *_xOut = xInicio + (xFim - xInicio) * ((_xIn) / float(nSamples));
   *_yOut = yInicio + (yFim - yInicio) * ((_yIn - minY[_plotNum]) / float(maxY[_plotNum] - minY[_plotNum]));
}

void Plot::addPlot(short *_data, int _plotNum){
   data[_plotNum] = _data;

   minY[0] = 1000;
   maxY[0] = -1000;

   // resize the plot
   for( int j=0 ; j<3 ; j++ ){

      if(signalView[j] == true){

         for(int i=0 ; i<nSamples ;i++){
            if(data[j][i] < minY[0]) minY[0] = data[j][i];
            if(data[j][i] > maxY[0]) maxY[0] = data[j][i];

            //printf("\n >>%d", data[0][i]);
         }

         if(minY[0] == maxY[0] && maxY[0] <= 0) maxY[0] += 1;
         if(minY[0] == maxY[0] && maxY[0] > 0) minY[0] -= 1;

      }
   }
   signalView[_plotNum] = true;
}

void Plot::enablePlot(int _plotNum, bool _state){
   signalView[_plotNum] = _state;

   minY[0] = 1000;
   maxY[0] = -1000;

   // resize the plot
   for( int j=0 ; j<3 ; j++ ){

      if(signalView[j] == true){

         for(int i=0 ; i<nSamples ;i++){
            if(data[j][i] < minY[0]) minY[0] = data[j][i];
            if(data[j][i] > maxY[0]) maxY[0] = data[j][i];

            //printf("\n >>%d", data[0][i]);
         }

         if(minY[0] == maxY[0] && maxY[0] <= 0) maxY[0] += 1;
         if(minY[0] == maxY[0] && maxY[0] > 0) minY[0] -= 1;

      }
   }
}
