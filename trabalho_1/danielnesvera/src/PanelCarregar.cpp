/**
 * @file    PanelCarregar.cpp
 * @date    16/04/2018
 * @author  Daniel André Nesvera
 *
 *    Contém o gráfico do sinal carregado da memória e botões para geração de
 * novas formas de ondas.
 *
 */

#include "PanelCarregar.h"

PanelCarregar::PanelCarregar(int _x0, int _y0, int _x1, int _y1, bool _active){

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
   numComponents = 6;
   uiComponents = (UIComponent **)malloc(numComponents*sizeof(UIComponent *));

   int xCenter = (x0+x1)/2;
   int yInit = y0+200;

   int hBox = 480;
   int wBox = 720;


   int xInit = xCenter - wBox/2 - 15;

   uiComponents[0] = new Plot((xCenter-wBox/2), yInit, (xCenter+wBox/2), (yInit+hBox), data, nSamples);

   uiComponents[1] = new Button(xInit, (yInit-150), (xInit+150), (yInit-80), "Senoidal");
   xInit += 200;
   uiComponents[2] = new Button(xInit, (yInit-150), (xInit+150), (yInit-80), "Dente de serra");
   xInit += 200;
   uiComponents[3] = new Button(xInit, (yInit-150), (xInit+150), (yInit-80), "Quadratica");
   xInit += 200;
   uiComponents[4] = new Button(xInit, (yInit-150), (xInit+150), (yInit-80), "Aleatorio");
   uiComponents[5] = new Texto((xCenter - wBox/2 - 15), (yInit-50), "Gerar novo sinal:");

   srand(time(NULL));
}

void PanelCarregar::render(){

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

void PanelCarregar::mouseHandler(int _button, int _state, int _x, int _y){
   for(int i=0 ; i<numComponents ; i++){
      uiComponents[i]->mouseHandler(_button, _state, _x, _y);
   }

   // Botão senoidal
   if(uiComponents[1]->wasPressed()){
      int amplitude = (rand()%200)-100;
      int frequencia = (rand()%200)-100;
      for(int i=0 ; i<nSamples ; i++ ){
         data[i] = amplitude*sin(i*frequencia);
      }

      arquivo->setData(data, nSamples);
      Plot *plot = (Plot *)uiComponents[0];
      plot->addPlot(data, 0);

   // Botão dente de serra
   }else if(uiComponents[2]->wasPressed()){
      int amplitude = (rand()%20)-10;

      int nPoint = 0;
      for(int i=0 ; i<nSamples ; i++ ){
         data[i] = amplitude*nPoint;
         nPoint++;

         if(nPoint == 8){
            nPoint = 0;
         }
      }

      arquivo->setData(data, nSamples);
      Plot *plot = (Plot *)uiComponents[0];
      plot->addPlot(data, 0);

   // Botão quatratica
   }else if(uiComponents[3]->wasPressed()){
      short amplitude = (rand()%200)-100;

      bool active = 0;
      for(int i=0 ; i<nSamples ; i++ ){
         if(active){
            data[i] = amplitude;
         }else{
            data[i] = 0;
         }

         if(i%3==0){
            active = !active;
         }

      }

      arquivo->setData(data, nSamples);
      Plot *plot = (Plot *)uiComponents[0];
      plot->addPlot(data, 0);

   // Botao aleatoria
   }else if(uiComponents[4]->wasPressed()){
      for(int i=0 ; i<nSamples ; i++ ){
         data[i] = (rand()%200)-100;
      }

      arquivo->setData(data, nSamples);
      Plot *plot = (Plot *)uiComponents[0];
      plot->addPlot(data, 0);

   }
}

void PanelCarregar::save(){
   arquivo->saveFile();
}
