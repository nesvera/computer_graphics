/**
 * @file    PanelIntro.cpp
 * @date    16/04/2018
 * @author  Daniel André Nesvera
 *
 *    Primeiro painel do software. Apresenta algumas informações para o usuário
 *
 */

#include "PanelIntro.h"

PanelIntro::PanelIntro(int _x0, int _y0, int _x1, int _y1, bool _active){

   // Initialize the panel shape and background
   x0 = _x0;
   y0 = _y0;
   x1 = _x1;
   y1 = _y1;

   //PanelButton:setColor(127, 140, 141);
   PanelButton:setColor(144, 168, 195);

   active = _active;

   // Add panel components
   int xInit = 400;
   int yInit = 635;
   Texto *text1 = new Texto(xInit, yInit, "Trabalho 1 de Computacao grafica: DCT/IDCT");

   yInit -= 30;
   Texto *text8 = new Texto(xInit, yInit, "Funcionalidade dos botoes:");

   xInit += 50;
   yInit -= 30;
   Texto *text2 = new Texto(xInit, yInit, "Carregar: le arquivo ou gera novos dados");

   yInit -= 30;
   Texto *text3 = new Texto(xInit, yInit, "Salvar: sobrescreve arquivo com dados gerados");

   yInit -= 30;
   Texto *text4 = new Texto(xInit, yInit, "Aplicar: aplica a transformada DCT e IDCT nos dados carregados");

   yInit -= 30;
   Texto *text5 = new Texto(xInit, yInit, "Carregar Imagem: carrega a imagem do disco");

   yInit -= 30;
   Texto *text6 = new Texto(xInit, yInit, "Funcoes ortogonais: apresenta funcoes ortogonais");

   yInit -= 30;
   Texto *text7 = new Texto(xInit, yInit, "Tamanho do bloco: parametro para a transformacao (2D=n) (3D=nxn)");

   xInit -= 90;
   yInit -= 50;
   Texto *text9 = new Texto(xInit, yInit, "Obs: Existe uma demora e queda de quadros no painel de imagem, devido ao processo da DCT");


   numComponents = 9;
   uiComponents = (UIComponent **)malloc(numComponents*sizeof(UIComponent *));
   uiComponents[0] = text1;
   uiComponents[1] = text2;
   uiComponents[2] = text3;
   uiComponents[3] = text4;
   uiComponents[4] = text5;
   uiComponents[5] = text6;
   uiComponents[6] = text7;
   uiComponents[7] = text8;
   uiComponents[8] = text9;

}

void PanelIntro::render(){

   if( active ){
      // draw background
      color(r,g,b);
      for(int y = y0 ; y<=y1 ; y++ ){
         line(x0, y, x1, y);
      }

      for(int i=0 ; i<numComponents ; i++){
         uiComponents[i]->render();
      }
   }
}
