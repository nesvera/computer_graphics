/**
 * @file    Arquivo.cpp
 * @date    16/04/2018
 * @author  Daniel André Nesvera
 *
 *    Classe que carrega arquivo, guarda,
 * salva em disco e contém as funções DCT e IDCT 1D
 *
 */

#include "Arquivo.h"

Arquivo::Arquivo(char *_fileName){
   fileName = _fileName;
   nSamples = 0;
   data = NULL;
   reconstructedData = NULL;

   if( _fileName != NULL && strlen(_fileName) > 0 ){
      loadFile();

   }else{
      printf("Arquivo inválido!");
   }
}

void Arquivo::loadFile(){

   FILE *file = fopen(fileName, "rb");

   if( file == NULL ){
      printf("\nErro ao abrir o arquivo %s", fileName);
      return;
   }

   // ler o header do arquivo que contém o número de amostras
   fread(&nSamples, sizeof(unsigned int), 1, file);

   data = (short *)malloc(nSamples*sizeof(short));

   for(int i=0 ; i<nSamples ; i++){
      fread(&data[i], sizeof(short), 1, file);
   }

   fclose(file);
}

void Arquivo::setData(short *_data, unsigned int _nSamples){
   if( nSamples != _nSamples){
      nSamples = _nSamples;

      free(data);
      data = (short *)malloc(nSamples*sizeof(short));
   }

   memcpy(data, _data, nSamples*sizeof(short));
}

void Arquivo::getDataLength(unsigned int *_nSamples){
   *_nSamples = nSamples;
}

void Arquivo::getData(short *_data){
   memcpy(_data, data, nSamples*sizeof(short));
}

void Arquivo::applyDctIdct(short *_dataOut){
   short *dctOutput = new short[nSamples];
   short *idctOutput = new short[nSamples];

   // Apply dct
   dct( data, dctOutput);
   idct(dctOutput, idctOutput);

   for(int i=0 ; i<nSamples ; i++){
     //printf("\n--> %d - %d", data[i], idctOutput[i]);
   }

   memcpy(_dataOut, idctOutput, nSamples*sizeof(short));
}

void Arquivo::dct(short *_x, short *_y){

   // Percorre todo arquivo
   for(int i=0 ; i<nSamples ; i+=blockSize){

      float e = 1/sqrt(2);

      // Percorre o bloco
      for(int k=0 ; k<blockSize ; k++){

         if(k!=0){
            e=1;
         }

         float sum = 0;
         for(int n=0 ; n<blockSize ; n++){
            sum += e*_x[i+n]*cos(((2.*n+1)*3.14*k)/(2.*blockSize));
         }

         _y[i+k] = short(sum);
      }
   }
}

void Arquivo::idct(short *_y, short *_x){

    // Percorre todo arquivo
   for(int i=0 ; i<nSamples ; i+=blockSize){

      float e = 1/sqrt(2);

      // Percorre o bloco
      for(int n=0 ; n<blockSize ; n++){

         if(n!=0){
            e=1;
         }

         float sum = 0;
         for(int k=0 ; k<blockSize ; k++){
            sum += (2./blockSize)*e*_y[i+k]*cos(((2*n+1)*3.14*k)/(2*blockSize));
            //printf("\n--> %f", sum);
         }

         _x[i+n] = short(sum);

      }
   }
}

void Arquivo::setBlockSize(int _blockSize){
   blockSize = _blockSize;
}

void Arquivo::saveFile(){

   FILE *file = fopen(fileName, "wb");

   if( file == NULL ){
      printf("\nErro ao abrir o arquivo %s", fileName);
      return;
   }

   // ler o header do arquivo que contém o número de amostras
   fwrite(&nSamples, sizeof(unsigned int), 1, file);

   for(int i=0 ; i<nSamples ; i++){
      fwrite((short *)&data[i], sizeof(short), 1, file);
   }

   fclose(file);
}
