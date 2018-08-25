No panel do lado esquerdo da janela é possível fazer as seguintes tarefas
      - Botão Carregar:
      - Le o arquivo "samples.dct" e plota o gráfico
      - Utilizando os botões abaixo do gráfico(Senoidal,Dente de serra, ...)
        é possível gerar novas ondas. É necessário clicar o botão SALVAR na
        barra de botões para escrever no arquivo "samples.dct"
       - O gráfico se auto ajusta aos sinais gerados

       - Botão Salvar:
       - Escreve no arquivo "samples.dct" a onda gerada no panel carregar
 
       - Botão Aplicar:
          - Aplicar DCT e IDCT sobre o dado lido do arquivo
          - Plota no gráfico os valores originais, recontruidos e a diferença entre os anteriores
          - Utilizando os checkboxes é possível habilitar/desabilidar os sinais(originais, reconstruidos,
            diferenças) no gráfico.
          - O gráfico se auto ajusta ao habilitar/desabilitar algum sinal do gráfico

      - Botão Carregar Imagem: (Nao está finalizado, apenas apresenta a imagem original) 
          - Le o arquivo "lena128_24bits.bmp", aplica DCT-IDCT e imprime a imagem original e reconstruida

      - Botão Funcoes Ortogonais: (Nao está finalizado, apenas apresenta os plots) 
          - Plota 16 funções
 
      - Botões de tamanho de bloco (4, 8, 16, 32):
	  - Parametriza tamanho de bloco
          - Altera o tamanho do bloco utilizado no cálculo da DCT e IDCT do sinal 1D e da imagem
          - Altera o sinal e gráfico em tempo real na janela aberta pelo botão aplicar
          - Altera a imagem na janela aberta pelo botão carregar imagem
 
 Foi implementada a funçao de hover e click nos botões para tornar mais agradavél a interação