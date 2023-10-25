Documentação do Projeto - Conversor de Imagem PPM
Este documento fornece uma visão geral da implementação do projeto "Conversor de Imagem 
PPM", que inclui a leitura e gravação de imagens no formato PPM, bem como a conversão de 
imagens coloridas em imagens em tons de cinza.
Estrutura do Projeto
O projeto é dividido em três arquivos principais: main.c, image.c e image.h.
main.c
O arquivo main.c contém a função main, que é a função principal do programa. Ele permite ao 
usuário escolher entre carregar uma imagem PPM, convertê-la em tons de cinza e salvar a 
imagem resultante em um arquivo PPM. O arquivo main.c interage com as funções definidas 
no arquivo image.c por meio de chamadas de função.
image.c
O arquivo image.c contém a implementação das funções relacionadas à manipulação de 
imagens. Ele inclui funções para criar uma nova imagem, carregar uma imagem a partir de um 
arquivo PPM, escrever uma imagem em um arquivo PPM, converter uma imagem RGB em tons 
de cinza e liberar a memória alocada para uma imagem. Todas essas funções operam em 
estruturas do tipo Image, que é definida no arquivo image.h.
image.h
O arquivo image.h contém a definição da estrutura Image e as assinaturas das funções que 
estão implementadas no arquivo image.c. Esta estrutura é usada para representar uma 
imagem e contém informações sobre o tipo da imagem, as dimensões e os dados dos pixels.
Fluxo de Funcionamento
O programa segue o seguinte fluxo de funcionamento:
1. O usuário inicia o programa e é apresentado a um menu de opções.
2. O usuário escolhe entre as seguintes opções:
 Carregar uma imagem PPM a partir de um arquivo.
 Converter a imagem carregada em tons de cinza e salvá-la em um arquivo.
 Sair do programa.
3. Se o usuário escolher a opção de carregar uma imagem, o programa solicitará o 
caminho do arquivo PPM. O arquivo é então lido e armazenado em uma estrutura 
Image.
4. Se o usuário escolher a opção de conversão para tons de cinza, o programa verifica se 
uma imagem foi carregada. Se uma imagem estiver disponível, ela é convertida em 
tons de cinza e a imagem resultante é salva em um arquivo.
5. O programa continua a oferecer opções ao usuário até que a opção "Sair" seja 
escolhida
