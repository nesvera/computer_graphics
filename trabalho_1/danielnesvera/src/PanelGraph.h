#include "UIComponent.h"
#include "Plot.h"
#include "Checkbox.h"
#include "Arquivo.h"

using namespace std;

#ifndef PANELGRAPH_H
#define PANELGRAPH_H

class PanelGraph : public UIComponent{

public:
   PanelGraph(int _x0, int _y0, int _x1, int _y1, bool _active);
   void render();
   void setBlockSize(int _blockSize);
   void applyTransform();

   void mouseHandler(int _button, int _state, int _x, int _y);

private:
   int numComponents;
   UIComponent **uiComponents;

   Arquivo *arquivo;
   unsigned int nSamples;
   short *data;
};

#endif // PANELGRAPH_H
