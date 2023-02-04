#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// TODO: fazer função
// função hash que recebe palavra e devolve a posição na tabela hash
int hash_function(string word)
{
    int hash = 0;
    for (int i = 0; i < word.length(); i++)
    {
        hash += word[i];
    }
    return hash % 100;
}
