/**
 * @file    PanelButton.cpp
 * @date    16/04/2018
 * @author  Daniel André Nesvera
 *
 *    Painel de botões
 *
 */

#include "PanelButton.h"

PanelButton::PanelButton(int _x0, int _y0, int _x1, int _y1 ){

   // Initialize the panel shape and background
   x0 = _x0;
   y0 = _y0;
   x1 = _x1;
   y1 = _y1;

   //PanelButton:setColor(46, 204, 113);
   PanelButton:setColor(14, 20, 40);

   //218,223,225

   // Add panel components
   numComponents = 10;
   uiComponents = (UIComponent **)malloc(numComponents*sizeof(UIComponent *));

   int bHeight = 60;
   int bWidth = 250;

   int xCenter = (x0+x1)/2;
   int yCenter = 620;
   Button *carregarArquivo = new Button((xCenter-bWidth/2), (yCenter-bHeight/2), (xCenter+bWidth/2), (yCenter+bHeight/2), "Carregar");

   yCenter -= 80;
   Button *salvarArquivo = new Button((xCenter-bWidth/2), (yCenter-bHeight/2), (xCenter+bWidth/2), (yCenter+bHeight/2), "Salvar");

   yCenter -= 80;
   Button *aplicarCompressao = new Button((xCenter-bWidth/2), (yCenter-bHeight/2), (xCenter+bWidth/2), (yCenter+bHeight/2), "Aplicar");

   yCenter -= 80;
   Button *carregarImagem = new Button((xCenter-bWidth/2), (yCenter-bHeight/2), (xCenter+bWidth/2), (yCenter+bHeight/2), "Carregar Imagem");

   yCenter -= 80;
   Button *funcaoOrtonogal = new Button((xCenter-bWidth/2), (yCenter-bHeight/2), (xCenter+bWidth/2), (yCenter+bHeight/2), "Funcoes Ortogonais");

   yCenter -= 80;
   Texto *text1 = new Texto(35, yCenter, "Tamanho do bloco: 4", 255, 255, 255);

   bWidth = 50;
   bHeight = 50;

   yCenter -= (bHeight);
   Button *bloco4 = new Button((xCenter-bWidth/2)-(bWidth/2)-5, (yCenter-bHeight/2), (xCenter+bWidth/2)-(bWidth/2)-5, (yCenter+bHeight/2), "4");
   Button *bloco16 = new Button((xCenter-bWidth/2)+(bWidth/2)+5, (yCenter-bHeight/2), (xCenter+bWidth/2)+(bWidth/2)+5, (yCenter+bHeight/2), "16");

   yCenter -= (bHeight+10);
   Button *bloco8 = new Button((xCenter-bWidth/2)-(bWidth/2)-5, (yCenter-bHeight/2), (xCenter+bWidth/2)-(bWidth/2)-5, (yCenter+bHeight/2), "8");
   Button *bloco32 = new Button((xCenter-bWidth/2)+(bWidth/2)+5, (yCenter-bHeight/2), (xCenter+bWidth/2)+(bWidth/2)+5, (yCenter+bHeight/2), "32");


   uiComponents[0] = carregarArquivo;
   uiComponents[1] = salvarArquivo;
   uiComponents[2] = aplicarCompressao;
   uiComponents[3] = carregarImagem;
   uiComponents[4] = funcaoOrtonogal;
   uiComponents[5] = text1;
   uiComponents[6] = bloco4;
   uiComponents[7] = bloco8;
   uiComponents[8] = bloco16;
   uiComponents[9] = bloco32;
}

void PanelButton::render(){

   // draw background
   color(r,g,b);
   for(int y = y0 ; y<=y1 ; y++ ){
      line(x0, y, x1, y);
   }

   // draw UI components
   for(int i=0 ; i<numComponents ; i++){
      if( uiComponents[i] != NULL ){
         uiComponents[i]->render();
      }
   }

}

void PanelButton::mouseHandler(int _button, int _state, int _x, int _y){
   for(int i=0 ; i<numComponents ; i++){
      uiComponents[i]->mouseHandler(_button, _state, _x, _y);
   }

   // Botão carregar
   if(uiComponents[0]->wasPressed()){
      panelIntro->setActive(false);
      panelCarregar->setActive(true);
      panelGraph->setActive(false);
      panelImage->setActive(false);
      panelOrtogonal->setActive(false);

   // Botão salvar
   }else if(uiComponents[1]->wasPressed()){
      panelCarregar->save();

   // Botão aplicar
   }else if(uiComponents[2]->wasPressed()){
      panelIntro->setActive(false);
      panelCarregar->setActive(false);
      panelGraph->setActive(true);
      panelImage->setActive(false);
      panelOrtogonal->setActive(false);
      panelGraph->applyTransform();

   // Botao carregar imagem
   }else if(uiComponents[3]->wasPressed()){
      panelIntro->setActive(false);
      panelCarregar->setActive(false);
      panelGraph->setActive(false);
      panelImage->setActive(true);
      panelOrtogonal->setActive(false);
      panelImage->loadImage();

   // Botao funcao ortogonal
   }else if(uiComponents[4]->wasPressed()){
      panelIntro->setActive(false);
      panelCarregar->setActive(false);
      panelGraph->setActive(false);
      panelImage->setActive(false);
      panelOrtogonal->setActive(true);

   // Texto
   //}else if(uiComponents[5]->wasPressed()){

   // Botao blocksize 4
   }else if(uiComponents[6]->wasPressed()){
      uiComponents[5]->setText("Tamanho do bloco: 4");
      panelGraph->setBlockSize(4);
      panelImage->setBlockSize(4);

   // Botao blocksize 8
   }else if(uiComponents[7]->wasPressed()){
      uiComponents[5]->setText("Tamanho do bloco: 8");
      panelGraph->setBlockSize(8);
      panelImage->setBlockSize(8);

   // Botao blocksize 16
   }else if(uiComponents[8]->wasPressed()){
      uiComponents[5]->setText("Tamanho do bloco: 16");
      panelGraph->setBlockSize(16);
      panelImage->setBlockSize(16);

   // Botao blocksize 32
   }else if(uiComponents[9]->wasPressed()){
      uiComponents[5]->setText("Tamanho do bloco: 32");
      panelGraph->setBlockSize(32);
      panelImage->setBlockSize(32);
   }


}

void PanelButton::addPanels(UIComponent **_panels, int _numPanels ){
   panelIntro = (PanelIntro *)_panels[0];
   panelCarregar = (PanelCarregar *)_panels[1];
   panelGraph = (PanelGraph *)_panels[2];
   panelImage = (PanelImage *)_panels[3];
   panelOrtogonal = (PanelOrtogonal *)_panels[4];
}

