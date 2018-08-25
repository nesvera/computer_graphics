#include "UIComponent.h"
#include "Button.h"
#include "PanelIntro.h"
#include "PanelGraph.h"
#include "PanelImage.h"
#include "PanelOrtogonal.h"
#include "PanelCarregar.h"

using namespace std;

#ifndef PANELBUTTON_H
#define PANELBUTTON_H

class PanelButton : public UIComponent{

public:
   PanelButton(int _x0, int _y0, int _x1, int _y1);
   void render();
   void mouseHandler(int _button, int _state, int _x, int _y);

   void addPanels(UIComponent **_panels, int _numPanels);

private:
   int numComponents;
   UIComponent **uiComponents;

   PanelIntro *panelIntro;
   PanelCarregar *panelCarregar;
   PanelGraph *panelGraph;
   PanelImage *panelImage;
   PanelOrtogonal *panelOrtogonal;


};

#endif // PANELBUTTON_H
