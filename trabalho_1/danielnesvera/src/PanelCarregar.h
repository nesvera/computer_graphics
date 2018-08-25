#include "UIComponent.h"
#include "Button.h"
#include "Plot.h"
#include "Checkbox.h"
#include "Arquivo.h"
#include <time.h>

using namespace std;

#ifndef PANELCARREGAR_H
#define PANELCARREGAR_H

class PanelCarregar : public UIComponent{

public:
   PanelCarregar(int _x0, int _y0, int _x1, int _y1, bool _active);
   void render();
   void save();

   void mouseHandler(int _button, int _state, int _x, int _y);

private:
   int numComponents;
   UIComponent **uiComponents;

   Arquivo *arquivo;
   unsigned int nSamples;
   short *data;

};

#endif // PANELCARREGAR_H
