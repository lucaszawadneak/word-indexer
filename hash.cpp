#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// TODO: resolver o problema da colisão
// função hash que recebe palavra e devolve a posição na tabela hash
int hash_function(string word)
{
    int hash = 0;
    for (int i = 0; i < word.length(); i++)
    {
        // soma o valor da letra com o seu índice
        hash += word[i] * (i + 1);
    }
    return hash % 10000;
}
