#include "UIComponent.h"
#include "bmp.h"
#include "gl_canvas2d.h"

using namespace std;

#ifndef PANELIMAGE_H
#define PANELIMAGE_H

class PanelImage : public UIComponent{

public:
   PanelImage(int _x0, int _y0, int _x1, int _y1, bool _active);
   void render();
   void setBlockSize(int _blockSize);
   void loadImage();

private:
   int numComponents;
   UIComponent **uiComponents;

   unsigned char *data;
   unsigned char *reconstructedData;

   int blockSize = 4;

   int originalX, originalY;
   int recreatedX, recreatedY;

   int imageHeight, imageWidth;
};

#endif // PANELIMAGE_H
