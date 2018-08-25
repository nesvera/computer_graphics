#include "UIComponent.h"

using namespace std;

#ifndef PLOT_H
#define PLOT_H

class Plot : public UIComponent{

public:
   Plot(int _x0, int _y0, int _x1, int _y1, float _freq, unsigned int _nSamples);
   Plot(int _x0, int _y0, int _x1, int _y1, short *_data, unsigned int _nSamples);
   void render();
   void addPlot(short *_data, int _plotNum);
   void enablePlot(int _plotNum, bool _state);

private:
   int nSamples;
   short **data;

   short minValue, maxValue;

   int height;
   int width;

   int xZero;
   int yZero;

   int xInit;
   int yInit;

   bool signalView[3];

   int minY[3];
   int maxY[3];
   void remap(int _xIn, short _yIn, int *_xOut, short *_yOut, int _plotNum);

};

#endif // PLOT_H
