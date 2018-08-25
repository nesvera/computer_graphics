/**
 * @file    PanelImage.cpp
 * @date    16/04/2018
 * @author  Daniel André Nesvera
 *
 *    Painel que apresenta a imagem original carregada da memória e a
 * reconstruída pela função DCT e IDCT
 *
 */

#include "PanelImage.h"

PanelImage::PanelImage(int _x0, int _y0, int _x1, int _y1, bool _active){

   // Initialize the panel shape and background
   x0 = _x0;
   y0 = _y0;
   x1 = _x1;
   y1 = _y1;

   PanelButton:setColor(218, 223, 225);

   active = _active;

   // Add panel components

}

void PanelImage::render(){

   if( active ){
      // draw background
      color(r,g,b);
      for(int y = y0 ; y<=y1 ; y++ ){
         line(x0, y, x1, y);
      }


      // draw image
      for(int i=0 ; i<imageHeight ; i++ ){
         for(int j=0 ; j<imageWidth ; j++ ){
            float r = data[i*imageWidth*3 + j*3 + 0]/255.;
            float g = data[i*imageWidth*3 + j*3 + 1]/255.;
            float b = data[i*imageWidth*3 + j*3 + 2]/255.;

            color(r, g, b);
            point(originalX+j, originalY+i);
         }
      }

      // draw recreated image
      for(int i=0 ; i<imageHeight ; i++ ){
         for(int j=0 ; j<imageWidth ; j++ ){
            float r = data[i*imageWidth*3 + j*3 + 0]/255.;
            float g = data[i*imageWidth*3 + j*3 + 1]/255.;
            float b = data[i*imageWidth*3 + j*3 + 2]/255.;

            color(r, g, b);
            point(recreatedX+j, recreatedY+i);
         }
      }

   }
}

void PanelImage::setBlockSize(int _blockSize){
   blockSize = _blockSize;
}

void PanelImage::loadImage(){
   Bmp *img = new Bmp(".\\danielnesvera\\resource\\lena128_24bits.bmp");
   img->convertBGRtoRGB();
   data = img->getImage();

   imageHeight = img->getHeight();
   imageWidth = img->getWidth();

   originalX = x0+200;
   recreatedX = originalX + imageWidth + 50;
   originalY = recreatedY = (y0+y1)/2 -imageHeight/2;

}

/*
void PanelImage::dct(unsigned *X, unsignd char *x, long N)
{
    long n, k;
    double xk[N][N];
    double pi = 3.14;
    for(n=0; n<N; n++)
        xk[0][n]=1.0/sqrt(N) * x[n];

    for(k=1; k<N; k++)
        for(n=0; n<N; n++)
            xk[k][n] = sqrt(2.0/N) * cos(k*pi/(2.0*N)*(2.0*n+1)) * x[n];

    for(k=0; k<N; k++)
        X[k]=0;

    for(k=0; k<N; k++)
    {
        for(n=0; n<N; n++)
        {
            X[k]+=xk[k][n];
        }
    }
    for (k=0; k<N; k++)
    {
        if (abs(X[k]) < threshold)
            X[k]=0;
    }

}

void PanelImage::idct(char *x, double *X, long N)
{
    long n, k;
    double xk[N][N];
    double sum[N];

    for(n=0; n<N; n++)
        xk[0][n]= sqrt(1.0/N) * X[0] * cos(0);

    for(k=1; k<N; k++)
        for(n=0; n<N; n++)
            xk[k][n] = sqrt(2.0/N) * X[k] * cos(k*(2*n+1)*3.14/(2.0*N));

    for(k=0; k<N; k++)
        sum[k]=0;

    for(k=0; k<N; k++)
    {
        for(n=0; n<N; n++)
        {
            sum[k]+=xk[n][k];
            termoSomatorio[k][n]= xk[n][k];
        }
        x[k] = round(sum[k]);
    }
}
*/
