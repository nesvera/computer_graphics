No panel do lado esquerdo da janela � poss�vel fazer as seguintes tarefas
      - Bot�o Carregar:
      - Le o arquivo "samples.dct" e plota o gr�fico
      - Utilizando os bot�es abaixo do gr�fico(Senoidal,Dente de serra, ...)
        � poss�vel gerar novas ondas. � necess�rio clicar o bot�o SALVAR na
        barra de bot�es para escrever no arquivo "samples.dct"
       - O gr�fico se auto ajusta aos sinais gerados

       - Bot�o Salvar:
       - Escreve no arquivo "samples.dct" a onda gerada no panel carregar
 
       - Bot�o Aplicar:
          - Aplicar DCT e IDCT sobre o dado lido do arquivo
          - Plota no gr�fico os valores originais, recontruidos e a diferen�a entre os anteriores
          - Utilizando os checkboxes � poss�vel habilitar/desabilidar os sinais(originais, reconstruidos,
            diferen�as) no gr�fico.
          - O gr�fico se auto ajusta ao habilitar/desabilitar algum sinal do gr�fico

      - Bot�o Carregar Imagem: (Nao est� finalizado, apenas apresenta a imagem original) 
          - Le o arquivo "lena128_24bits.bmp", aplica DCT-IDCT e imprime a imagem original e reconstruida

      - Bot�o Funcoes Ortogonais: (Nao est� finalizado, apenas apresenta os plots) 
          - Plota 16 fun��es
 
      - Bot�es de tamanho de bloco (4, 8, 16, 32):
	  - Parametriza tamanho de bloco
          - Altera o tamanho do bloco utilizado no c�lculo da DCT e IDCT do sinal 1D e da imagem
          - Altera o sinal e gr�fico em tempo real na janela aberta pelo bot�o aplicar
          - Altera a imagem na janela aberta pelo bot�o carregar imagem
 
 Foi implementada a fun�ao de hover e click nos bot�es para tornar mais agradav�l a intera��o