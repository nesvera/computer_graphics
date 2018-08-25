/**
 * @file    PanelGraph.cpp
 * @date    16/04/2018
 * @author  Daniel André Nesvera
 *
 *    Painel contém o gráfico com os sinal original, reconstruido e a diferença.
 * Contém checkboxes para habilitar e desabilitar a visualização dos sinais
 *
 */

#include "PanelGraph.h"

PanelGraph::PanelGraph(int _x0, int _y0, int _x1, int _y1, bool _active){

   // Initialize the panel shape and background
   x0 = _x0;
   y0 = _y0;
   x1 = _x1;
   y1 = _y1;

   PanelButton:setColor(218, 223, 225);

   active = _active;

   // Load file
   arquivo = new Arquivo(".\\danielnesvera\\resource\\samples.dct");
   arquivo->getDataLength(&nSamples);
   data = new short[nSamples];
   arquivo->getData(data);


   // Add panel components
   numComponents = 4;
   uiComponents = (UIComponent **)malloc(numComponents*sizeof(UIComponent *));

   int xCenter = (x0+x1)/2;
   int yInit = y0+200;

   int hBox = 480;
   int wBox = 720;


   int xInit = xCenter - wBox/2 - 15;

   // Plot data
   Plot *plot = new Plot((xCenter-wBox/2), yInit, (xCenter+wBox/2), (yInit+hBox), data, nSamples);

   // Apply dct&idct and plot
   short *reconstructedData = new short[nSamples];
   arquivo->applyDctIdct(reconstructedData);
   plot->addPlot(reconstructedData, 1);

   // Diferença entre os dados originais e reconstruidos
   short *diferenca = new short[nSamples];
   for(int i=0 ; i<nSamples ; i++ ){
      diferenca[i] = abs(data[i]-reconstructedData[i]);
      //printf("\n >> %d %d %d", data[i], reconstructedData[i], diferenca[i]);
   }
   plot->addPlot(diferenca, 2);

   uiComponents[0] = (UIComponent *)plot;
   uiComponents[1] = new Checkbox((xCenter-wBox/2), yInit-60, "Valores originais", 255, 0, 0);
   uiComponents[2] = new Checkbox((xCenter-wBox/2), yInit-100, "Valores reconstruidos", 0, 180, 0);
   uiComponents[3] = new Checkbox((xCenter-wBox/2), yInit-140, "Diferenca entre os valores", 0, 0, 255);

}

void PanelGraph::render(){

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

void PanelGraph::mouseHandler(int _button, int _state, int _x, int _y){
   for(int i=0 ; i<numComponents ; i++){
      uiComponents[i]->mouseHandler(_button, _state, _x, _y);
   }

   Plot *plt = (Plot *)uiComponents[0];
   // Checkbox botao original
   if( uiComponents[1]->isChecked() ){
      plt->enablePlot(0, true);
   }else{
      plt->enablePlot(0, false);
   }

   // Checkbox botao reconstruido
   if( uiComponents[2]->isChecked() ){
      plt->enablePlot(1, true);
   }else{
      plt->enablePlot(1, false);
   }

   // Checkbox botao diferenca
   if( uiComponents[3]->isChecked() ){
      plt->enablePlot(2, true);
   }else{
      plt->enablePlot(2, false);
   }
}

void PanelGraph::setBlockSize(int _blockSize){
   Plot *plot = (Plot *)uiComponents[0];

   arquivo->setBlockSize(_blockSize);

   plot->addPlot(data, 0);

   // Apply dct&idct and plot
   short *reconstructedData = new short[nSamples];
   arquivo->applyDctIdct(reconstructedData);
   plot->addPlot(reconstructedData, 1);

   // Diferença entre os dados originais e reconstruidos
   short *diferenca = new short[nSamples];
   for(int i=0 ; i<nSamples ; i++ ){
      diferenca[i] = abs(data[i]-reconstructedData[i]);
      //printf("\n >> %d %d %d", data[i], reconstructedData[i], diferenca[i]);
   }
   plot->addPlot(diferenca, 2);
}

void PanelGraph::applyTransform(){
   // Load file
   arquivo = new Arquivo(".\\danielnesvera\\resource\\samples.dct");
   arquivo->getDataLength(&nSamples);
   data = new short[nSamples];
   arquivo->getData(data);

   Plot *plot = (Plot *)uiComponents[0];
   plot->addPlot(data, 0);

   // Apply dct&idct and plot
   short *reconstructedData = new short[nSamples];
   arquivo->applyDctIdct(reconstructedData);
   plot->addPlot(reconstructedData, 1);

   // Diferença entre os dados originais e reconstruidos
   short *diferenca = new short[nSamples];
   for(int i=0 ; i<nSamples ; i++ ){
      diferenca[i] = abs(data[i]-reconstructedData[i]);
      //printf("\n >> %d %d %d", data[i], reconstructedData[i], diferenca[i]);
   }
   plot->addPlot(diferenca, 2);
}
