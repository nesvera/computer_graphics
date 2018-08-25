#include "UIComponent.h"
#include "Texto.h"

using namespace std;

#ifndef PANELINTRO_H
#define PANELINTRO_H

class PanelIntro : public UIComponent{

public:
   PanelIntro(int _x0, int _y0, int _x1, int _y1, bool _active);
   void render();

private:
   int numComponents;
   UIComponent **uiComponents;

};

#endif // PANELINTRO_H
