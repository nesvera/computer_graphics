#include "UIComponent.h"
#include "Plot.h"

using namespace std;

#ifndef PANELORTOGONAL_H
#define PANELORTOGONAL_H

class PanelOrtogonal : public UIComponent{

public:
   PanelOrtogonal(int _x0, int _y0, int _x1, int _y1, bool _active);
   void render();

private:
   int numComponents;
   UIComponent **uiComponents;

};

#endif // PANELORTOGONAL_H
