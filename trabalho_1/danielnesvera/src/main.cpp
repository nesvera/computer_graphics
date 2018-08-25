/**
 * @file    main.cpp
 * @date    16/04/2018
 * @author  Daniel Andr� Nesvera
 * Matr�cula 201320267
 *
 *
 * Instru��es:
 *    A interface do trabalho � intuitiva
 *
 *    No panel do lado esquerdo da janela � poss�vel fazer as seguintes tarefas
 *       - Bot�o Carregar:
 *          - Le o arquivo "samples.dct" e plota o gr�fico
 *          - Utilizando os bot�es abaixo do gr�fico(Senoidal,Dente de serra, ...)
 *            � poss�vel gerar novas ondas. � necess�rio clicar o bot�o SALVAR na
 *            barra de bot�es para escrever no arquivo "samples.dct"
 *          - O gr�fico se auto ajusta aos sinais gerados
 *
 *       - Bot�o Salvar:
 *          - Escreve no arquivo "samples.dct" a onda gerada no panel carregar
 *
 *       - Bot�o Aplicar:
 *          - Aplicar DCT e IDCT sobre o dado lido do arquivo
 *          - Plota no gr�fico os valores originais, recontruidos e a diferen�a entre os anteriores
 *          - Utilizando os checkboxes � poss�vel habilitar/desabilidar os sinais(originais, reconstruidos,
 *            diferen�as) no gr�fico.
 *          - O gr�fico se auto ajusta ao habilitar/desabilitar algum sinal do gr�fico
 *
 *       - Bot�o Carregar Imagem: (Nao est� finalizado, apenas apresenta a imagem original)
 *          - Le o arquivo "lena128_24bits.bmp", aplica DCT-IDCT e imprime a imagem original e reconstruida
 *
 *       - Bot�o Funcoes Ortogonais: (Nao est� finalizado, apenas apresenta os plots)
 *          - Plota 16 fun��es
 *
 *       - Bot�es de tamanho de bloco (4, 8, 16, 32):
 *          - Altera o tamanho do bloco utilizado no c�lculo da DCT e IDCT do sinal 1D e da imagem
 *          - Altera o sinal e gr�fico em tempo real na janela aberta pelo bot�o aplicar
 *          - Altera a imagem na janela aberta pelo bot�o carregar imagem
 *
 *    Foi implementada a fun�ao de hover e click nos bot�es para tornar mais agradav�l a intera��o
 */

#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"

#include "Button.h"
#include "Texto.h"
#include "Checkbox.h"
#include "PanelButton.h"
#include "PanelIntro.h"
#include "PanelGraph.h"
#include "PanelImage.h"
#include "PanelOrtogonal.h"
#include "Arquivo.h"
#include "PanelCarregar.h"

int numPaneis;
int display_height = 720;
int display_width = 1280;

// Ponteiros para os paineis: bot�o, intro, grafico e imagem
UIComponent **panels;

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis
//globais que podem ser setadas pelo metodo keyboard()
void render()
{
   for(int i=0 ; i<numPaneis ; i++ ){
      if( panels[i] != NULL ){
         panels[i]->render();
      }
   }

}

//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key)
{

}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{

}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int x, int y)
{
   //Inverte a indexacao da tela
   y = display_height - y;

   for(int i=0 ; i<numPaneis ; i++ ){
      if( panels[i] != NULL ){
         panels[i]->mouseHandler(button, state, x, y);
      }
   }

}

int main(void)
{
   initCanvas(display_width, display_height);

   numPaneis = 6;
   panels = (UIComponent **)malloc(numPaneis*sizeof(UIComponent*));

   PanelButton *panelButtons = new PanelButton(0, 0, 320, display_height);
   PanelIntro *panelIntro = new PanelIntro(320, 0, display_width, display_height, true);
   PanelCarregar *panelCarregar = new PanelCarregar(320, 0, display_width, display_height, false);
   PanelGraph *panelGraph = new PanelGraph(320, 0, display_width, display_height, false);
   PanelImage *panelImage = new PanelImage(320, 0, display_width, display_height, false);
   PanelOrtogonal *panelOrtogonal = new PanelOrtogonal(320, 0, display_width, display_height, false);

   panels[0] = panelButtons;
   panels[1] = panelIntro;
   panels[2] = panelCarregar;
   panels[3] = panelGraph;
   panels[4] = panelImage;
   panels[5] = panelOrtogonal;

   UIComponent **panelsWithoutButton = (UIComponent **)malloc((numPaneis-1)*sizeof(UIComponent *));
   panelsWithoutButton[0] = panelIntro;
   panelsWithoutButton[1] = panelCarregar;
   panelsWithoutButton[2] = panelGraph;
   panelsWithoutButton[3] = panelImage;
   panelsWithoutButton[4] = panelOrtogonal;
   panelButtons->addPanels(panelsWithoutButton, (numPaneis-1));

   runCanvas();
}
