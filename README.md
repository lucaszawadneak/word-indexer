# Indexer de palavras

## Motivação e funcionamento

Este trabalho foi desenvolvido a partir da seguinte especificação: [Clique aqui](ESPECIFICACAO.md)

Para o desenvolvimento do indexador de palavras, a estrutura de dados escolhida foi a **tabela hash**. A tabela hash é utilizada em diversas aplicações para garantir a eficiência na busca por elementos em **grandes coleções de dados**. Em vez de percorrer uma lista ou árvore inteira em busca de um elemento, ela mapeia o valor de uma chave para um índice específico na tabela, permitindo acesso direto ao elemento desejado. Além disso, as operações de inserção e remoção também são realizadas de forma mais rápida. A complexidade dessas operações depende do tamanho da tabela e da qualidade da função hash usada.

Em uma tabela hash ideal, onde a função hash distribui uniformemente as entradas, **cada operação tem complexidade O(1)** em média. Isso significa que o tempo para realizar uma operação é constante, independentemente do número de entradas na tabela.

No entanto, em situações com muitas colisões, o tempo para realizar uma operação pode aumentar, pois é necessário percorrer a lista ligada para encontrar a entrada desejada. Nesse caso, a complexidade pode se aproximar de O(n), onde n é o número de entradas na tabela.

Em comparação a outras estruturas como árvores e listas ligadas, a tabela hash oferece uma melhor performance, tornando-se uma opção mais vantajosa para a implementação do indexador de palavras. Como o volume de dados é grande, não seria possível criar o indexador com outras estruturas, uma vez que O(n) para arquivos de GBs de texto seria impossível de processar em um período de tempo realista.

## Rodando o Projeto

O projeto foi desenvolvido utilizando C++. Desse modo, para rodar a aplicação no Linux é primeiro preciso compilar o código. Para isso, é necessário [instalar o pacote](https://linuxconfig.org/how-to-install-g-the-c-compiler-on-ubuntu-18-04-bionic-beaver-linux) **g++**

Com o pacote instalado, é preciso compilar o código do projeto, utilizando o seguinte comando:

```
g++ indexer.cpp
```

Esse comando irá gerar o arquivo **a.out**. Para rodar o códio do projeto então utilize, de acordo com a [especificação](ESPECIFICACAO.md):

```
./a.out --freq N ARQUIVO

./a.out --freq-word PALAVRA ARQUIVO

./a.out --search TERMO ARQUIVO [ARQUIVO...]

```

Trabalho desenvolvido para composição de nota na matéria de Estrutura de Dados, pelo curso de Análise e Desenvolvimento de Sistemas da UFPR.

Curitiba, 2023

Leonardo Xavier da Silva Moraes
GRR20204488

Lucas Cassilha Zawadneak
GRR20200141
