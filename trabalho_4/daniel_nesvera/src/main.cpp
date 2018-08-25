#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glut.h>

#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#include "Matrix4.h"
#include "Vector3.h"
#include "Virabrequim.h"
#include "Camisa.h"
#include "Pistao.h"
#include "Bloco.h"
#include "Biela.h"

#define M_PI 3.14159265358979323846

void Display();
void MouseHandler(int button, int state, int x, int y);
void KeyboardHandler(unsigned char key, int x, int y);
void Init();
void Menu();
void CreateLight();
void FpsDisplay(int fpsCount, int x, int y);
void reshapeHandler(int w, int h);

int windowHeight = 700;
int windowWidth = 700;

// Elementos do motor
Virabrequim *virabrequim;
Camisa *camisa_0;
Camisa *camisa_1;
Pistao *pistao_0;
Pistao *pistao_1;
Bloco *bloco;
Biela *biela_0;
Biela *biela_1;

// Posicoes do motor
Vector3 virabrequimPos;
Vector3 pistao_0Pos;
Vector3 pistao_1Pos;
Vector3 blocoPos;
Vector3 biela_0Pos;
Vector3 biela_1Pos;
Vector3 posPistao_0;
Vector3 posPistao_1;

// Propriedades do motor
float bielaHolderRaio = 100;
float bielaLargura = 350;

// Comandos preset
bool blocoEnable = true;
bool virabrequimEnable = true;
bool bielaEnable = true;
bool pistaoEnable = true;
bool camisaEnable = true;
float velAngularVirabrequim = 0;       // rps = rotacoes por segundo, mais facil de visualizar
bool preenchimentoEnable = false;       // true = preenchimento       false = wireframe
bool visOrtografica = false;            // true = ortografica         false = perspectiva
bool iluminacaoDifusa = true;          // true = difusa
bool iluminacaoEspecular = true;
float fps = 30;                        // variavel que limita o numero de frames por segundo

// Incremento/Decremento da velocidade angular
float dtVelocidadeAngular = 0.1;

// Incremento/Decremtno do fps
float dtFps = 1;

// save time to fps counter
float lastUpdate = clock();


// Variable for camera control
float cameraXPos = 0;
float cameraYPos = 0;
float cameraZPos = 0;

float cameraZoom = 2000;
float dtZoom = 10;

float cameraTheta = 0;
float cameraPsi = 0;

int lastClickX, lastClickY;

float virabrequimAng = 0;

void Init(){

   // Constroi motor

   // bloco
   blocoPos = Vector3(20, 420, 250);
   bloco = new Bloco(&blocoPos);

   // virabrequim
   virabrequimPos = Vector3(0, 250, 250);
   virabrequim = new Virabrequim(&virabrequimPos);

   // biela
   biela_0Pos.x = 290-20;
   biela_0Pos.y = bielaHolderRaio*cos(virabrequimAng) + virabrequimPos.y;
   biela_0Pos.z = bielaHolderRaio*sin(virabrequimAng) + virabrequimPos.z;

   biela_1Pos.x = 420-20;
   biela_1Pos.y = bielaHolderRaio*cos(virabrequimAng+M_PI) + virabrequimPos.y;
   biela_1Pos.z = bielaHolderRaio*sin(virabrequimAng+M_PI) + virabrequimPos.z;

   float rx = bielaHolderRaio*sin(virabrequimAng);
   float gama = acos(rx/bielaLargura);

   posPistao_0.x = 290;
   posPistao_0.y = biela_0Pos.y + bielaLargura*sin(gama);
   posPistao_0.z = biela_0Pos.z + bielaLargura*cos(gama);

   posPistao_1.x = 420;
   posPistao_1.y = biela_1Pos.y + bielaLargura*sin(gama);
   posPistao_1.z = biela_1Pos.z + bielaLargura*cos(gama);

   // camisas
   camisa_0 = new Camisa(new Vector3(290, 540, 250));
   camisa_1 = new Camisa(new Vector3(420, 540, 250));

   // pistoes
   pistao_0 = new Pistao(new Vector3(posPistao_0.x, posPistao_0.y, posPistao_0.z));
   pistao_1 = new Pistao(new Vector3(posPistao_1.x, posPistao_1.y, posPistao_1.z));

   // bielas

   biela_0 = new Biela(&biela_0Pos);
   rx = bielaHolderRaio*sin(virabrequimAng);
   gama = acos(rx/bielaLargura);
   biela_0->SetAngle(gama);

   biela_1 = new Biela(&biela_1Pos);
   rx = bielaHolderRaio*sin(virabrequimAng + M_PI);
   gama = acos(rx/bielaLargura + M_PI);
   biela_1->SetAngle(gama);

   // Configura openGL

   // Wireframe
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   // Material  - Chrome
   GLfloat matAmbient[] ={0.25f, 0.25f, 0.25f, 1.0f  };
   GLfloat matDiffuse[] ={0.4f, 0.4f, 0.4f, 1.0f };
   GLfloat matSpecular[] ={0.774597f, 0.774597f, 0.774597f, 1.0f };
   GLfloat shine[] = {10.f};

   glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
   glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
   glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, shine);

	// Light
	GLfloat lightPos[4];
	GLfloat lightAmb[4];
	GLfloat lightDif[4];
	GLfloat lightEsp[4];
	GLfloat lightShi[1];

   lightPos[0] = 1000.0f;
   lightPos[1] = 5000.0f;
   lightPos[2] = 1000.0f;
   lightPos[3] = 1.0f;

   lightAmb[0] = 0.8f;
   lightAmb[1] = 0.8f;
   lightAmb[2] = 0.8f;
   lightAmb[3] = 1.0f;

   lightDif[0] = 0.5f;
   lightDif[1] = 0.5f;
   lightDif[2] = 0.5f;
   lightDif[3] = 1.0f;

   lightEsp[0] = 1.0f;
   lightEsp[1] = 1.0f;
   lightEsp[2] = 1.0f;
   lightEsp[3] = 1.0f;

	lightShi[0] = 10;

   glLightfv (GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv (GL_LIGHT0, GL_AMBIENT,  lightAmb);
	glLightfv (GL_LIGHT0, GL_DIFFUSE,  lightDif);

	glLightfv (GL_LIGHT1, GL_POSITION, lightPos);
	glLightfv (GL_LIGHT1, GL_SPECULAR, lightEsp);

  	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);

	/* enable lighting */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// Configura camera
	cameraXPos = cameraZoom*sin(cameraTheta)*cos(cameraPsi);
	cameraYPos = cameraZoom*sin(cameraTheta)*sin(cameraPsi);
	cameraZPos = cameraZoom*cos(cameraTheta);
}

void Display(){

   // -- FPS
   // Get fps based on time difference
   float delta_time = (clock()-lastUpdate)/CLOCKS_PER_SEC;
   int fpsCounter = (int)(1/(delta_time));
   lastUpdate = clock();

   // Calcula angulo do virabrequim
   float velAng = velAngularVirabrequim*(360)*delta_time;
   virabrequimAng += velAng;
   virabrequim->SetAngle(virabrequimAng);

   double virabrequimAngRadians = (virabrequimAng*M_PI)/180.;

   // Calcula posicao inferior da biela
   biela_0Pos.y = bielaHolderRaio*cos(virabrequimAngRadians) + virabrequimPos.y;
   biela_0Pos.z = bielaHolderRaio*sin(virabrequimAngRadians) + virabrequimPos.z;

   biela_1Pos.y = bielaHolderRaio*cos(virabrequimAngRadians+M_PI) + virabrequimPos.y;
   biela_1Pos.z = bielaHolderRaio*sin(virabrequimAngRadians+M_PI) + virabrequimPos.z;

   float rx = bielaHolderRaio*sin(virabrequimAngRadians+M_PI);
   float gama = acos(rx/bielaLargura);

   posPistao_0.x = 290;
   posPistao_0.y = biela_0Pos.y + bielaLargura*sin(gama);
   posPistao_0.z = biela_0Pos.z + bielaLargura*cos(gama);

   rx = bielaHolderRaio*sin(virabrequimAngRadians);
   gama = acos(rx/bielaLargura);

   posPistao_1.x = 420;
   posPistao_1.y = biela_1Pos.y + bielaLargura*sin(gama);
   posPistao_1.z = biela_1Pos.z + bielaLargura*cos(gama);

   // pistoes
   pistao_0->SetPosition(&posPistao_0);
   pistao_1->SetPosition(&posPistao_1);

   // bielas
   rx = bielaHolderRaio*sin(virabrequimAngRadians);
   float gama_0 = acos(rx/bielaLargura);
   biela_0->SetAngle(gama_0);
   biela_0->SetPosition(&biela_0Pos);

   rx = bielaHolderRaio*sin(virabrequimAngRadians+M_PI);
   float gama_1 = acos(rx/bielaLargura);
   biela_1->SetAngle(gama_1);
   biela_1->SetPosition(&biela_1Pos);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // -- Orthographic projection
   if( visOrtografica == true ){
      float znear  = 1;
      float zfar   = 10000;
      float worldCoordX = 1000;
      float worldCoordY = 1000;

      glViewport(0, 0, windowWidth, windowHeight);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(-worldCoordX, worldCoordX, -worldCoordY, worldCoordY, znear, zfar);

   // -- Perspective projection
   }else{
      float abertura = 45.0;
      float znear  = 1;
      float zfar   = 10000;
      float aspect = 1;

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(abertura, aspect, znear, zfar);
   }

   // --- Camera
   glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(cameraXPos, 1000, cameraZPos, 355, 300, 250, 0,1,0);
	gluLookAt(cameraXPos, 800, cameraZPos, 355, 300, 250, 0,1,0);

   glColor3f(1,1,1);


   // -- Engine
   // Desenha bloco do motor
   if( blocoEnable ){
      bloco->Render();
   }

   // Desenha virabrequim
   if( virabrequimEnable ){
      virabrequim->Render();
   }

   // Desenha bielas
   if( bielaEnable ){
      biela_0->Render();
      biela_1->Render();
   }

   // Desenha pistoes
   if( pistaoEnable ){
      pistao_0->Render();
      pistao_1->Render();
   }

   // Desenha camisas
   if( camisaEnable ){
      camisa_0->Render();
      camisa_1->Render();
   }

   // Display the fps on screen
   FpsDisplay(fpsCounter, 20, (windowHeight-20));

   glutSwapBuffers();

}

void FpsDisplay(int fpsCount, int x, int y){

   glPushAttrib(GL_ENABLE_BIT);

   //glDisable(GL_COLOR_MATERIAL);
   //glDisable(GL_TEXTURE_2D);
   //glDisable(GL_FOG);
   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);
   //glDisable(GL_BLEND);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, windowWidth, windowHeight, 0);

   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();

   // Cor do texto
   glColor3f(1.,1.,1.);

   char text[16];
   sprintf(text, "FPS: %d", fpsCount);

   char *c;
	for (c=text; *c != '\0'; c++){
		glRasterPos2f(x,y);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
		x = x + glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24,*c) + 5;      // espaço entre letras
	}


	glPopMatrix();
   glPopAttrib();
}

// Callback utilizada para controlar FPS
void Timer(int value){
   glutPostRedisplay();
   glutTimerFunc((unsigned int)(1000/fps), Timer, 0);
}

int main (int argc, char* argv[])
{
	glutInit(&argc, argv);

	// Configura janela
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(400, 0);
	glutCreateWindow("Daniel Nesvera - 3D Engine");

	// Seta callbacks
	glutDisplayFunc(Display);
	glutTimerFunc((unsigned int)(1000/fps), Timer, 0);
	glutMouseFunc(MouseHandler);
	glutKeyboardFunc(KeyboardHandler);
   glutReshapeFunc(reshapeHandler);

   Init();

   // Apresenta comandos para o usuario
   Menu();

	glutMainLoop();

   return 0;
}


/********************* Apreseta comandos para o usuario ********************** */
void Menu(){
   printf("Comandos: ");
   printf("\n\n");
   printf("B      - Ativa/Desativa visualizacao do bloco \n");
   printf("V      - Ativa/Desativa visualizacao do virabrequim \n");
   printf("N      - Ativa/Desativa visualizacao da biela \n");
   printf("P      - Ativa/Desativa visualizacao do pistao \n");
   printf("C      - Ativa/Desativa visualizacao da camisa \n");
   printf("A      - Aumenta velocidade angular do virabrequim (RPM) \n");
   printf("D      - Diminui velocidade angular do virabrequim (RPM) \n");
   printf("W      - Altera entre wireframe e preenchimento \n");
   printf("H      - Altera entre visualizacao ortografica e perspectiva \n");
   printf("I      - Ativa/Desativa iluminacao difusa \n");
   printf("O      - Ativa/Desativa iluminacao especular \n");
   printf("F      - Aumenta taxa de atualizacao da tela FPS \n");
   printf("R      - Diminiu taxa de atualizacao da tela FPS \n");
   printf("Mouse  - Altera angulo de visualizacao da camera \n");
   printf("ESC    - Fecha janela \n");
}

/*************************** Callback mouse ************************************ */
void MouseHandler(int button, int state, int x, int y){

   // Zoom out
   if(button == 0 && state == 0){
      lastClickX = x;
      lastClickY = y;

   }else if(button == 0 && state == 1){
      float mouseInc = M_PI;
      float dtX = ((x - lastClickX)/(float)windowWidth)*mouseInc;
      float dtY = ((y - lastClickY)/(float)windowHeight)*mouseInc;

      cameraTheta -= dtX;
      //cameraPsi += dtY;

   }else if(button == 3){
      cameraZoom -= dtZoom;

   }else if(button == 4){
      cameraZoom += dtZoom;
   }

   // Configura camera
	cameraXPos = cameraZoom*sin(cameraTheta)*cos(cameraPsi);
	cameraYPos = cameraZoom*sin(cameraTheta)*sin(cameraPsi);
	cameraZPos = cameraZoom*cos(cameraTheta);
}

void reshapeHandler(int w, int h) {
  windowHeight = h;
  windowWidth = w;
}


/************************** Callback keyboard *********************************** */
void KeyboardHandler(unsigned char key, int x, int y){

   key = towlower(key);

   switch(key){
      case 'b':
         blocoEnable = !blocoEnable;
         break;

      case 'v':
         virabrequimEnable = !virabrequimEnable;
         break;

      case 'n':
         bielaEnable = !bielaEnable;
         break;

      case 'p':
         pistaoEnable = !pistaoEnable;
         break;

      case 'a':
         velAngularVirabrequim += dtVelocidadeAngular;
         break;

      case 'd':
         velAngularVirabrequim -= dtVelocidadeAngular;
         break;

      case 'w':

         if( preenchimentoEnable == true ){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

         }else{
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         }

         preenchimentoEnable = !preenchimentoEnable;

         break;

      case 'c':
         camisaEnable = !camisaEnable;
         break;

      case 'h':
         visOrtografica = !visOrtografica;
         break;

      case 'i':
         if( iluminacaoDifusa == true ){
            glDisable(GL_LIGHT0);
         }else{
            glEnable(GL_LIGHT0);
         }

         iluminacaoDifusa = !iluminacaoDifusa;
         break;

      case 'o':
         if( iluminacaoEspecular == true ){
            glDisable(GL_LIGHT1);
         }else{
            glEnable(GL_LIGHT1);
         }

         iluminacaoEspecular = !iluminacaoEspecular;
         break;

      case 'f':
         fps += dtFps;
         break;

      case 'r':
         if(fps > 1){
            fps -= dtFps;
         }
         break;

      case 27:
         exit(0);
         break;
   }
}
