#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>

using namespace std;

#ifndef ARQUIVO_H
#define ARQUIVO_H

class Arquivo{

public:

   Arquivo(char *_fileName);

   void setData(short *_data, unsigned int _nSamples);
   void saveFile();
   void getData(short *_data);
   void getDataLength(unsigned int *_nSamples);
   void applyDctIdct(short *_dataOut);
   void setBlockSize(int _blockSize);

private:

   char *fileName;
   unsigned int nSamples;
   short *data;
   short *reconstructedData;

   int blockSize = 4;

   void loadFile();
   void dct(short *_x, short *_y);
   void idct(short *_y, short *_x);


};

#endif // ARQUIVO_H
